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
        
        logging.info(f"Game started at {hex(self.ptr)} with seed {seed}.")
        
        # Start server
        self.connection_key = randint(0, 0xffffffffffffffffffffffffffffffff)
        self.addr = (socket.gethostbyname(socket.gethostname()), port)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(self.addr)

        logging.info(f"Server started at {self.addr}.")

        # Print the code
        print("Connect to the server with the following code")
        print(self.get_code())
        
        self.start()
        
    def __del__(self):
        logging.info("Game Ended")
        end_game(self.ptr)

    def start(self):
        self.server.listen()
        while 1:
            conn, addr = self.server.accept()
            pwd = connect(self.ptr)
            conn.send(pwd)
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
        
        (0x11) signifies the ID of a card.
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
    """


    def handle_client(self, conn, addr):
        while 1:
            msg = conn.recv(16)
            if msg:
                # Termination message
                if (msg == (b'\xff'*16)):
                    break
                # query request
                if (msg[0] == b'\x20'):
                    # send back the card details
                    card_number, card_type, card_owner = peek(self.ptr, int.from_bytes(msg[1:5],"big"))
                    conn.send(b'\x11' + bytes([card_number, card_type]))
                    
                ret = play_turn(self.ptr, msg)
                p, t = ret % 256, ret // 256
        conn.close()
    
    def broadcast(self, conn, addr):
        pass

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
    logging.basicConfig(format='%(asctime)s.%(msecs)03d %(message)s', datefmt='%Y-%m-%d,%H:%M:%S', level=logging.DEBUG)
    g = Game()
