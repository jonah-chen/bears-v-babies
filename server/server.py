# Game
from bearsvbabies import *

# Networking
import socket
from requests import get
from threading import Thread
from random import randint
from utils import *
from time import sleep

# Logging
import logging

# parsing arguments
import argparse


def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except Exception:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP


class Game:
    def __init__(self, seed=None, port=25500, public=True, public_port=None):
        # Start new game from seed
        if not seed:
            seed = randint(0, 0xffffffffffffffffffffffffffffffff)
        self.ptr = new_game(seed, 5)
        
        logging.info(f"Game started at {hex(self.ptr)} with seed {hex(seed)}.")
        
        # Start server
        self.connection_key = randint(0, 0xffffffffffffffffffffffffffffffff)
        if public: # find public ipv4
            local_ip = get_ip()
            self.addr = (local_ip, port)
            self.public_ip = get('https://api.ipify.org').text
        else: # running offline
            self.addr = (socket.gethostbyname(socket.gethostname()), port)
            self.public_ip = self.addr[0]
        
        self.public_port = public_port if public_port else port # if public and private port is the same

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(self.addr)

        logging.info(f"Server started at {self.addr}.")

        # Print the code
        print("Connect to the server with the following code")
        print(self.get_code())
        
        self.connections = []
        self.user_map = {} # ZERO INDEXED!!!
        self.recycle = []

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
        s += str(int.from_bytes(msg[4:8], "little")) + "."
        s += str(int.from_bytes(msg[8:12], "little")) + "."
        s += str(int.from_bytes(msg[12:16], "little")) + "."

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
        if int.from_bytes(msg,"little") != self.connection_key:
            logging.warning(f"Incorrect connection key of {int.from_bytes(msg,'little')} recieved from {addr}. The client is forcefully disconnected by the server security.")
            conn.close()
            return
        
        # Client verified. Establish connection.
        pwd = connect(self.ptr)
        if not pwd and self.recycle:
            pwd = self.recycle.pop()
        if pwd:
            conn.send(bytes([pwd % 256, (pwd >> 8)]))
            # fifth user has connected. game is about to start so broadcast public info
            if len(self.connections) == 4:
                self.connections.append(conn)
                self.broadcast(0)
            else:
                self.connections.append(conn)

            self.user_map[conn] = (pwd >> 8)
            logging.info(f"connection established with {addr}")
            priv_data = fetch_private(self.ptr, 1+self.user_map[conn])
            logging.info(f"sent {len(priv_data)} private cards to player {self.user_map[conn]+1}")
            for card in priv_data:
                conn.send(b'\x12' + card.to_bytes(4,"little"))
        else:
            logging.warning(f"connection with {addr} cannot be established because game is full")
            conn.close()
            return

        while 1:
            msg = conn.recv(16)
            logging.info(f"recieved {msg} from {addr}")            
            if not conn in self.connections:
                logging.error(f"Connection at {addr} not in the connections list. This means the connection is missing or kicked by the server.")
                conn.close()
                return
            if msg:
                # Termination message
                if (msg == (b'\xff'*16)):
                    logging.warning(f"{addr} disconnected voluntarily")
                    self.connections.remove(conn)
                    self.recycle.append(pwd)
                    conn.close()
                    return
                
                # query request
                if (msg[0] == 0x20):
                    # send back the card details
                    if int.from_bytes(msg[4:8],"little") == 0:
                        raise ValueError(f"cannot fetch the card of nonexistent head of headless monster @{hex(msg[1])}.")
                    card_number, card_type, card_owner = peek(self.ptr, int.from_bytes(msg[4:8],"little"))

                    # determine the lead bit of the return message
                    if msg[1] >= 0x40 and msg[1] < 0x80:
                        lead = msg[1] + 0x80
                    elif msg[1] >= 0x80 and msg[1] < 0xc0:
                        lead = msg[1] + 0x40
                    else:
                        lead = 0x25

                    conn.send(bytes([lead, card_number, card_type, card_owner+128, msg[2]])) # send back msg[2] as it may be used as identifier sometimes                
                     
                # playing cards/performing in-game level actions
                else:
                    logging.info(Game.decrypt_16(msg))
                    # broadcast public data
                    output = play_turn(self.ptr, msg)
                    if output >= 0:
                        self.broadcast(output)
                        if msg[0] == 200: # provoke
                            self.broadcast_private()
                        else:
                            # send private data
                            priv_data = fetch_private(self.ptr, 1+self.user_map[conn])
                            logging.info(f"sent {len(priv_data)} private cards to player {self.user_map[conn]+1}")
                            for card in priv_data:
                                conn.send(b'\x12' + card.to_bytes(4,"little"))
                    else:
                        logging.warning(f"invalid input to play_turn is sent to the server but not executed. error code {output}.")
                        if msg[0] == 2:
                            conn.send(b'\x12' + msg[4:8])
                            logging.warning(f"invalid card played. the card info sent back to the owner.")
                    # ALL debug info if logging level is debug
                    if logging.getLogger(__name__).isEnabledFor(logging.DEBUG):
                        debug(self.ptr)


    def broadcast(self, turn_info=None):
        
        if len(self.connections) < 0:
            logging.warning(f"Cannot broadcast because only {len(self.connections)}/5 players are connected.")

        # Send current turn info
        if turn_info > 0:
            for conn in self.connections:
                conn.send(b'\x3a' + bytes([turn_info % 256, (turn_info >> 8), 0, 0]))
        else:
            logging.error("something died")
        # Send baby info
        baby_info = fetch_babies(self.ptr)
        for conn in self.connections:
            conn.send(b'\x34' + bytes([baby_info % 256, (baby_info >> 8) % 256, (baby_info >> 16) % 256, 0]))

        # Send public card info
        dumpster_info = fetch_dumpster(self.ptr)
        for card in dumpster_info:
            for conn in self.connections:
                try:
                    conn.send(b'\x11' + card.to_bytes(4, "little"))
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
                    conn.send(bytes([m_counter if ind else h_counter]) + monster[ind].to_bytes(4,"little"))    
            m_counter += 1
            h_counter += 1
        logging.info(f"broadcasted {len(monster_info)} monsters")
                
        # log the debug info


    def broadcast_private(self):
        logging.info("broadcast private is called")
        for conn, zero_ind_no in self.user_map.items():
            priv_data = fetch_private(self.ptr, 1+zero_ind_no)
            logging.debug(f"sent {len(priv_data)} private cards to player {zero_ind_no+1}")
            for card in priv_data:
                conn.send(b'\x12' + card.to_bytes(4,"little"))


    def get_code(self):
        """Encode the server IP, port, and connection message into a single code"""
        # This is just a naive approach. Exposes the server IP in plain text.

        # ip consists of 4 bytes or 32 bits
        # connection message is 16 bytes or 128 bits
        # port is 2 bytes or 16 bits
        priv_ip = list(map(lambda x: int(x), self.addr[0].split('.')))
        ip = list(map(lambda x: int(x), self.public_ip.split('.')))
        logging.info(f"Private IP is {priv_ip}, Public IP is {ip}.")
        if priv_ip != ip:
            logging.warning(f"You must forward private port {self.addr[1]} to public port {self.public_port}.")
        return convert_62_f((self.connection_key << 16) + 
                            (self.public_port << 152) + 
                            (ip[0] << 8) + 
                            (ip[1] << 144) + 
                            (ip[2]) + 
                            (ip[3] << 168))



if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", "-p", default=25510, help="private port, defaults to 25510.")
    parser.add_argument("--PORT", "-P", default=25510, help="public port, defaults to 25510.")
    parser.add_argument("-log", "--log", default="warning", help="provide logging level. defaults to warning.")
    options = parser.parse_args()
    levels = {
        'critical': logging.CRITICAL,
        'error': logging.ERROR,
        'warn': logging.WARNING,
        'warning': logging.WARNING,
        'info': logging.INFO,
        'debug': logging.DEBUG
    }
    level = levels.get(options.log.lower())
    if level is None:
        raise ValueError(
            f"log level given: {options.log}"
            f" -- must be one of: {' | '.join(levels.keys())}")

    logging.basicConfig(format='%(asctime)s.%(msecs)03d %(message)s', datefmt='%Y-%m-%d,%H:%M:%S', level=level)

    if options.port == 'offline':
        g = Game(public=False, port=int(options.PORT))
    else:
        try:
            g = Game(port=int(options.port), public_port=int(options.PORT))
        except OSError:
            logging.warning("trying again on port 25500")
            g = Game()
