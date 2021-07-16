import socket
from threading import Thread

import argparse

class Player:
    def __init__(self, game_code):
        self.addr, self.connect_code = None, None 
        self.addr = (server_ip, port)
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect(self.addr)
        self.pwd = client.recv(1)
        if not pwd:
            self.client.send((b'\xff')*16)
            raise Exception("The game is full. Please try connecting later")
        
        self.info = {} # set of all IDs that the client knows about
        self.download = Thread(target=self.listening)
        self.download.start()
        
    def __del__(self):
        self.client.send((b'\xff')*16)   
    

    def listening(self):
        """Listening listens to five byte packets from the server"""     
        while 1:
            msg = self.client.recv(5)
            print(msg)

    def talking(self):
        """Talking sends sixteen byte packets to the server"""
        while 1:
            pass

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("game_code", type=str)
    args = parser.parse_args()
    player = Player(args.game_code)
