import os

# surpress pygame promo message
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1'

import argparse
import pygame

from client import Player
from threading import Thread

# Default Resolution
WIDTH = 1920
HEIGHT = 1080
TPS = 10
 
# Some helper functions and variables
def coords(x,y=None):
    if y is None:
        return (int(WIDTH*x[0]),int(HEIGHT*x[1]))
    return (int(WIDTH*x),int(HEIGHT*y))
def inv_c(x,y=None):
    if y is None:
        return x[0]/WIDTH,x[1]/HEIGHT
    return x/WIDTH,y/HEIGHT
def rect_c(pos,main_pos=((0,0),(1,1))):
    """
    pos is (topleft, botright) relative
    return absolute (left,top,width,height)"""
    return (
            int(WIDTH*(main_pos[0][0]+(main_pos[1][0]-main_pos[0][0])*pos[0][0])), # left
            int(HEIGHT*(main_pos[0][1]+(main_pos[1][1]-main_pos[0][1])*pos[0][1])), # top
            int(WIDTH*(main_pos[1][0]-main_pos[0][0])*(pos[1][0]-pos[0][0])), # width 
            int(HEIGHT*(main_pos[1][1]-main_pos[0][1])*(pos[1][1]-pos[0][1])) # height
            )
    
def set_res(width):
    global WIDTH, HEIGHT
    WIDTH = WIDTH
    HEIGHT = WIDTH * 9/16

# Some Constants

CARD_SIZE = (0.15,0.15)

MAIN_BOARD_POS = ((0.25,0.25),(0.75,0.75))
PLAYER_HAND_POS = (((MAIN_BOARD_POS[0][0]+1)/2,MAIN_BOARD_POS[1][1]),(1,1))
PLAYER_BOARD_POS = ((MAIN_BOARD_POS[0][0],MAIN_BOARD_POS[1][1]),((MAIN_BOARD_POS[0][0]+1)/2,1))
WEST_POS = ((0,MAIN_BOARD_POS[0][1]),(MAIN_BOARD_POS[0][0],1))
EAST_POS =  ((MAIN_BOARD_POS[1][0],0),(1,MAIN_BOARD_POS[1][1]))
NORTH_POS = ((MAIN_BOARD_POS[1][0]/2,0),(MAIN_BOARD_POS[1][0],MAIN_BOARD_POS[0][1]))
SOUTH_POS = ((0,0),(MAIN_BOARD_POS[1][0]/2, MAIN_BOARD_POS[0][1]))


DRAW_PILE1 = ((0.716, 0.676), (0.975, 0.954))
DRAW_PILE2 = ((0.716, 0.359), (0.975, 0.637))
DRAW_PILE3 = ((0.716, 0.047), (0.975, 0.325))

DISCARD_PILE = ((0,0),(0.1827,1))

LAND_BABY_ARMY = ((0.205,0.189),(0.351,0.684))
SEA_BABY_ARMY  = ((0.375,0.189),(0.521,0.684))
SKY_BABY_ARMY  = ((0.544,0.189),(0.690,0.684))

# Parse the arguments
parser = argparse.ArgumentParser()
parser.add_argument("game_code", type=str)
parser.add_argument("--width", help="Custom width of the window. Defaults to 1920 pixels.", type=int)
args = parser.parse_args()
if args.width:
    set_res(args.width)
    print(f"width set to {args.width}")

# Initialize pygame
pygame.init()
window = pygame.display.set_mode(coords(1,1))
pygame.display.set_caption("Bears versus Babies Client version 0.0.1")
clock = pygame.time.Clock()

# Create "hitboxes"

HB_DRAW = [
            pygame.Rect(rect_c(DRAW_PILE1, MAIN_BOARD_POS)),
            pygame.Rect(rect_c(DRAW_PILE2, MAIN_BOARD_POS)),
            pygame.Rect(rect_c(DRAW_PILE3, MAIN_BOARD_POS))
          ]
HB_DUMPSTER_DIVE = pygame.Rect(rect_c(DISCARD_PILE, MAIN_BOARD_POS))
HB_PROVOKE = [
                pygame.Rect(rect_c(LAND_BABY_ARMY, MAIN_BOARD_POS)), 
                pygame.Rect(rect_c(SEA_BABY_ARMY, MAIN_BOARD_POS)),
                pygame.Rect(rect_c(SKY_BABY_ARMY, MAIN_BOARD_POS))
             ]




# Import resources
BACKGROUND = pygame.transform.scale(
                pygame.image.load(os.path.join("assets", "bkgd.jpg")), 
                coords(1,1))


GAME_BOARD = pygame.transform.scale(
                pygame.image.load(os.path.join("assets", "gmbd.png")),
                coords(MAIN_BOARD_POS[1][0]-MAIN_BOARD_POS[0][0],MAIN_BOARD_POS[1][1]-MAIN_BOARD_POS[0][1]))


def load_card(folder,number,ext=".png"):
    return [pygame.transform.scale(
            pygame.image.load(os.path.join("assets", folder, str(i)+ext)), coords(CARD_SIZE)) for i in range(number)]

CARDS = {
    1:  load_card('TOOL', 5),
    2:  load_card('LULLABY', 2), 
    3:  load_card('HAT', 3),
    4:  load_card('MASK', 3), 
    5:  load_card('SWAP', 2),
    6:  load_card('DISMEMBER', 3),
    7:  load_card('WILD_PROVOKE', 2),
    8:  load_card('C_TORSO', 9),
    9:  load_card('TORSO', 3),
    10: load_card('M_BODY', 3),
    11: load_card('AL_BODY', 2),
    12: load_card('LEGS', 7),
    13: load_card('ARM', 10),
    17: load_card('LAND', 7), 
    19: load_card('SEA', 7),
    23: load_card('SKY', 7),
    29: load_card('BEAR', 5),
    233: load_card('sKY', 9),
    237: load_card('sEA', 9),
    239: load_card('lAND', 9)
}

CARD_BACK = pygame.transform.scale(
                pygame.image.load(os.path.join("assets", "back.jpg")),
                coords(0.15,0.15))

# procedurally generate code for importing the images for each card


# Initialize the client and connect to server
player = Player(args.game_code)

# Start the GUI
running = True
left_button_pressed = False
while running:
    clock.tick(TPS)
    
    # event checking
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
    
    # render
    window.fill((0,0,0))    
    window.blit(BACKGROUND, (0,0))
    window.blit(GAME_BOARD, coords(MAIN_BOARD_POS[0]))

    # check for user actions
    if pygame.mouse.get_pressed()[0]:
        if not left_button_pressed:
            # do collision detection
            left_button_pressed = True
            pos = pygame.mouse.get_pos()
            
            for r in HB_DRAW:
                if r.collidepoint(pos):
                    player.drawBTN()

            if HB_DUMPSTER_DIVE.collidepoint(pos):
                print("dumpster_dive")
                # have the player select the card before sending information to the server.

            for r in range(3):
                if HB_PROVOKE[r].collidepoint(pos):
                    player.provokeBTN(r)

    else:
        left_button_pressed = False
    
    
    # update display at the end of each loop
    pygame.display.update()

# call the destructor and sends the disconnect message to the server
del player
pygame.quit()
