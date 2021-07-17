import socket
from threading import Thread

from utils import convert_62_r
import argparse

# GUI
import sys

# The player class controls the player interaction with the server.
class Player:
    def __init__(self, game_code):
        game_num = convert_62_r(game_code)
        server_ip = f'{(game_num >> 8) % 256}.{(game_num >> 144) % 256}.{game_num % 256}.{game_num >> 168}'
        port = (game_num >> 152) % 65536
        self.connect_code = ((game_num >> 16) % (1 << 128)).to_bytes(16, "big")
        self.addr = (server_ip, port)
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect(self.addr)
        self.client.send(self.connect_code)
        f_msg = self.client.recv(2)
        self.pwd = f_msg[0]
        self.player_no = f_msg[1] + 1
        if not self.pwd:
            print("The game is full. Please try connecting later")
            sys.exit()

        # card info that the player knows about
        self.dumpster_info = set()
        self.monster_info = {} # map from the head to monster
        self.head_map = {} # map from id to head
        self.hand_info = set()

        # baby counts to display in the middle
        self.land_count = 0
        self.sea_count = 0
        self.sky_count = 0
        
        # turn and ply count to display on the side
        self.turn = 0
        self.ply = 0

        
        # start the listening thread
        self.ear = Thread(target=self.listening)
        self.ear.start()

        # talking thread?????

    def __del__(self):
        self.client.send((b'\xff')*16)   
    

    def listening(self):
        """Listening always listens to five byte packets from the server"""     
        while 1:
            msg = self.client.recv(5)
            print(msg)
            if not msg:
                print("Connection to the server is lost.")
                sys.exit()
            if   msg[0] == 0x11:
                self.dumpster_info.add(int.from_bytes(msg[1:5],"big"))
            elif msg[0] == 0x12:
                self.hand_info.add(int.from_bytes(msg[1:5],"big"))
            elif msg[0] == 0x25:
                # need to do some rendering stuff to the screen
                pass
            elif msg[0] == 0x34:
                self.land_count = msg[1]
                self.sea_count = msg[2]
                self.sky_count = msg[3]
            elif msg[0] == 0x3a:
                self.turn = msg[4]
                self.ply = msg[3]
            elif msg[0] >= 0x40 and msg[0] < 0x80:
                self.monster_info[msg[0]].add(int.from_bytes(msg[1:5],"big"))
            elif msg[0] >= 0x80 and msg[0] < 0xc0:
                self.monster_info[msg[0]] = {int.from_bytes(msg[1:5],"big")}
            elif msg[0] >= 0xc0:
                # need to do some rendering monsters to the screen
                pass
            
    def drawBTN(self):
        self.client.send(bytes([1, 0, 0, self.pwd]) + (b'\x00'*12))
    
    
    def provokeBTN(self, ty):
        if ty == 'land' or ty == 0:
            self.client.send(bytes([200, 17, 1, self.pwd]) + (b'\x00'*12))
            return
        if ty == 'sea' or ty == 1:
            self.client.send(bytes([200, 19, 1, self.pwd]) + (b'\x00'*12))
            return
        if ty == 'sky' or ty == 2:
            self.client.send(bytes([200, 23, 1, self.pwd]) + (b'\x00'*12))
            return 
        
        raise ValueError("The provoked type must be either 'land', 'sea', or 'sky'")

    
    def playcard(self, card, target1=0, target2=0):
        self.client.send(bytes([2, 0, 1, self.pwd]) + card.to_bytes(4,"big") + target1.to_bytes(4,"big") + target2.to_bytes(4,"big"))
    
    
    def dumpster_dive(self, target):
        self.client.send(bytes([240, 0, 1, self.pwd]) + target.to_bytes(4,"big") + (b'\x00'*8))




if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("game_code", type=str)
    args = parser.parse_args()
    player = Player(args.game_code)
    print(player.player_no)
    while 1:
        input()
        player.drawBTN()
