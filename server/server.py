# Game
from bearsvbabies import *
from time import time_ns

# Networking
import socket
from threading import Thread
from random import randint
from utils import *

# Logging
import logging

class Game:
    def __init__(self, seed=None, port=25510, verbose=1):
        self.verbose = verbose
        # Start new game from seed
        if not seed:
            seed = time_ns()
        self.ptr = new_game(seed)
        
        logging.info(f"Game started at {hex(self.ptr)} with seed {hex(seed)}.")
        
        # Start server
        self.connection_key = randint(0, 0xffffffffffffffffffffffffffffffff)
        self.addr = (socket.gethostbyname(socket.gethostname()), port)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(self.addr)

        logging.info(f"Server started at {self.addr}.")

        # Print the code
        print("Connect to the server with the following code")
        print(self.get_code())
        
        self.connections = []
        self.user_map = {} # ZERO INDEXED!!!

        self.start()


    def __del__(self):
        logging.info("Game Ended")
        end_game(self.ptr)


    def start(self):
        self.server.listen()
        while 1:
            conn, addr = self.server.accept()
            thread = Thread(target=self.handle_client, args=(conn, addr))
            thread.start()
    

    @staticmethod
    def decrypt_16(msg):
        s = ""
        # if an action is taken
        try:
            s += "Action: " + ACTIONS[msg[0]] + "."
        except KeyError:
            s += "No Action."
        # type
        try:
            s += "Type: " + CARD_TYPES[msg[1]] + "."
        except KeyError:
            s += "No Type."
        # Direction
        if msg[2] == 3:
            s += "R."
        else:
            s += "L."
        # ids
        s += str(int.from_bytes(msg[4:8], "big")) + "."
        s += str(int.from_bytes(msg[8:12], "big")) + "."
        s += str(int.from_bytes(msg[12:16], "big")) + "."

        return s


    """
Server messages: Fixed width (5 bytes)
    byte 0:
        The zeroth byte describes the nature of the message.
        
        (0x11) signifies the ID of a card in the dumpster.
                bytes 1-5 will be the id of the card.
        (0x12) signifies the id of a card in player's hand.
                bytes 1-5 will be the id of the card.
        (0x25) the description of a card. 
                byte 1 will be the card number (for rendering the image).
                byte 2 will be the card type.
                byte 3 will be the card owner.
        (0x34) # of baby information.
                byte 1 will be land.
                byte 2 will be sea.
                byte 3 will be air.
        (0x3a) turn information.
                byte 1 will be the overall turn number for the game.
                byte 2 will be the "mini"-turn number.
        (0x40 to 0x7f) signifies the ID of the card on the board, with each specific ID corresponding to an individual monster.
                bytes 1-5 will be the id of ONE of the cards EXCLUDING HEADS.
        (0x80 to 0xbf) signifies the ID of a card on the board, with each ID corresponding to an individual head 0x40 greater than the other parts.
                bytes 1-5 will be the id of the HEAD.
        (0xc0 to 0xff) signifies the info of a card that is a part of the monster. 
                byte 1 will be the card number
                byte 2 will be the card type
                byte 3 will be the card owner
                byte 4 will be something else
    """


    def handle_client(self, conn, addr):
        # recieve the key
        msg = conn.recv(16)
        if int.from_bytes(msg,"big") != self.connection_key:
            logging.warning(f"Incorrect connection key of {int.from_bytes(msg,'big')} recieved from {addr}. The client is forcefully disconnected by the server security.")
            conn.close()
            return
        
        # Client verified. Establish connection.
        pwd = connect(self.ptr)
        if pwd:
            conn.send(bytes([pwd % 256, (pwd >> 8)]))
            self.connections.append(conn)
            self.user_map[addr] = (pwd >> 8)
            logging.info(f"connection established with {addr}")
            priv_data = fetch_private(self.ptr, 1+self.user_map[addr])
            logging.info(f"sent {len(priv_data)} private cards to player {self.user_map[addr]+1}")
            for card in priv_data:
                conn.send(b'\x12' + card.to_bytes(4,"big"))
            

        else:
            logging.warning(f"connection with {addr} cannot be established because game is full")
            conn.close()
            return

        while 1:
            msg = conn.recv(16)
            
            if not conn in self.connections:
                logging.error(f"Connection at {addr} not in the connections list.")
                conn.close()
                return
            if msg:
                # Termination message
                if (msg == (b'\xff'*16)):
                    logging.warning(f"{addr} disconnected voluntarily")
                    break
                
                # query request
                if (msg[0] == b'\x20'):
                    # send back the card details
                    card_number, card_type, card_owner = peek(self.ptr, int.from_bytes(msg[4:8],"big"))
                    
                    # determine the lead bit of the return message
                    if msg[1] >= 0x40 and msg[1] < 0x80:
                        lead = msg[1] + 0x80
                    elif msg[1] >= 0x80 and msg[1] < 0xc0:
                        lead = msg[1] + 0x40
                    else:
                        lead = 0x25

                    conn.send(bytes([lead, card_number, card_type, card_owner+128, 0]))                  
                     
                # playing cards/performing in-game level actions
                else:
                    logging.info(Game.decrypt_16(msg))
                    # broadcast public data
                    self.broadcast(play_turn(self.ptr, msg))
                    # send private data
                    priv_data = fetch_private(self.ptr, 1+self.user_map[addr])
                    logging.info(f"sent {len(priv_data)} private cards to player {self.user_map[addr]+1}")
                    for card in priv_data:
                        conn.send(b'\x12' + card.to_bytes(4,"big"))

                    # ALL debug info if logging level is debug
                    if logging.getLogger(__name__).isEnabledFor(logging.DEBUG):
                        debug(self.ptr)
                    
        self.connections.remove(conn)
        conn.close()


    def broadcast(self, turn_info=None):
        # Send public card info
        dumpster_info = fetch_dumpster(self.ptr)
        for card in dumpster_info:
            for conn in self.connections:
                try:
                    conn.send(b'\x11' + card.to_bytes(4, "big"))
                except BrokenPipeError:
                    # Client has disconnected
                    logging.error("A client has unexpectedly disconnected")
                    self.connections.remove(conn)
        logging.info(f"broadcasted {len(dumpster_info)} dumpster cards")
        
        monster_info = fetch_public(self.ptr)
        m_counter, h_counter = 0x40, 0x80
        for monster in monster_info:
            for ind in range(len(monster)):
                for conn in self.connections:
                    conn.send(bytes([m_counter if ind else h_counter]) + monster[ind].to_bytes(4,"big"))    
            m_counter += 1
            h_counter += 1
        logging.info(f"broadcasted {len(monster_info)} monsters")

        # Send current turn info
        if turn_info:
            for conn in self.connections:
                conn.send(b'\x3a' + bytes([turn_info % 256, turn_info // 256, 0, 0]))
        
        # Send baby info
        baby_info = fetch_babies(self.ptr)
        for conn in self.connections:
            conn.send(b'\x34' + bytes([baby_info % 256, (baby_info >> 8) % 256, (baby_info >> 16) % 256, 0]))
                
        # log the debug info


    def get_code(self):
        """Encode the server IP, port, and connection message into a single code"""
        # This is just a naive approach. Exposes the server IP in plain text.

        # ip consists of 4 bytes or 32 bits
        # connection message is 16 bytes or 128 bits
        # port is 2 bytes or 16 bits
        ip = list(map(lambda x: int(x), self.addr[0].split('.')))
        logging.debug(f"IP is {ip}")
        return convert_62_f((self.connection_key << 16) + 
                            (self.addr[1] << 152) + 
                            (ip[0] << 8) + 
                            (ip[1] << 144) + 
                            (ip[2]) + 
                            (ip[3] << 168))
    


if __name__ == '__main__':
    logging.basicConfig(format='%(asctime)s.%(msecs)03d %(message)s', datefmt='%Y-%m-%d,%H:%M:%S', level=logging.INFO)
    g = Game()
