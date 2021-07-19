import os

# surpress pygame promo message
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1'

import argparse
import pygame
import sys

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
    WIDTH = width
    HEIGHT = width * 9/16

# Some Constants

CARD_SIZE = (0.12,0.23)
CARD_SIZE_S = (0.09,0.175)
X_FIT = 8
Y_FIT = 4


MAIN_BOARD_POS = ((0.2,0.28),(0.8,0.72))
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
parser.add_argument("--tps", help="Ticks per second of the client. Defaults to 10. DEBUG OPTION DO NOT CHANGE UNLESS YOU KNOW EXACTLY WHAT YOU ARE DOING!", type=int)
args = parser.parse_args()
if args.width:
    set_res(args.width)
    print(f"width set to {args.width}")
if args.tps:
    TPS = args.tps
    print(f"speed set to {TPS}tps")

# Initialize pygame
pygame.init()
window = pygame.display.set_mode(coords(1,1))
pygame.display.set_caption("Bears versus Babies Client version 0.0.2")
font = pygame.font.SysFont("comicsans", 32, True)
bigfont = pygame.font.SysFont("comicsans", 96, True)
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
                pygame.image.load(os.path.join("assets", "back.png")),
                coords(CARD_SIZE))

CARD_BACK_S = pygame.transform.scale(
                pygame.image.load(os.path.join("assets", "back.png")),
                coords(CARD_SIZE_S))

BABY_SPACE = 0.017

TURN_INDICATOR_POS = [
    (0.5, 0.95),
    (0.95, 0.5),
    (0.67, 0.05),
    (0.33, 0.05),
    (0.05, 0.5)
]

PLY_INDICATOR_X0 = 0.85
PLY_INDICATOR_Y = 0.97

# create card sprites
class Card(pygame.sprite.Sprite):
    def __init__(self, card_id, card, pos):
        """Initializes with the card (number,type) and RELATIVE position pos"""
        super().__init__()
        self.id = card_id
        self.image = CARDS[card[1]][card[0]]
        self.rect = self.image.get_rect(topleft=coords(pos))

    def click(self, player):
        player.playcard(self.id)
    
    def select1(self, player):
        player.t1 = self.id
    
    def select2(self, player):
        player.t2 = self.id


def get_dumpster_sprite(dumpster_bidict, page=0):
    disp_cards = pygame.sprite.Group()
    _count = 0
    
    ipp = X_FIT*Y_FIT-1

    for _id, card in dumpster_bidict.items():
        if _count >= ipp*page and type(card) is tuple:
            count = _count % ipp
            xpos = (count % X_FIT) / X_FIT
            ypos = (count // X_FIT) / Y_FIT
            if count < ipp*(page+1):
                spt = Card(_id,card,(xpos,ypos))
                disp_cards.add(spt)
            elif count == ipp*(page+1):
                disp_cards.add(Card(-1,CARD_BACK,(xpos,ypos)))
                break
        _count += 1

    return disp_cards


# Initialize the client and connect to server
player = Player(args.game_code)

# Start the GUI
running = True
left_button_pressed = False
selected_card = None # This is the card that is selected on the previous frame.

mode = 0

while running:
    clock.tick(TPS)
    
    # event checking for safe quit/disconnect
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            # call the destructor and sends the disconnect message to the server
            running = False
            break
        if event.type == pygame.KEYDOWN:
            # pressing escape will return to normal mode
            if event.key == pygame.K_ESCAPE:
                mode = 0
    if not running:
        break
    
    # acquire mouse position
    pos = pygame.mouse.get_pos()

    # render
    if mode == 0: # normal mode
        window.fill((0,0,0))
        window.blit(BACKGROUND, (0,0))
        window.blit(GAME_BOARD, coords(MAIN_BOARD_POS[0]))

        # startx is determined by the hand area

        # cardspace is determined by hand area too
        startx = PLAYER_HAND_POS[0][0]
        card_space = 0.05
        card_counter = 0
        
        # render cards in hand and make hitboxes
        hand_cards = []
        for _id, card in player.hand_info.items():
            if type(card) is tuple: # the tuple will be card number, card type
                spt = Card(_id,card,(startx+card_space*card_counter,PLAYER_HAND_POS[0][1]))
                hand_cards.append(spt)
                window.blit(spt.image, spt.rect) 
                card_counter += 1
        # select the main card to display on top
        
        # if the selected card doesn't exist or if the mouse is no longer over it, update it
        # otherwise do nothing for this step
        
        if selected_card is not None and not selected_card.rect.collidepoint(pos):
            selected_card = None
        if selected_card is None:
            for card in hand_cards[::-1]:
                if card.rect.collidepoint(pos):
                    # this card is the card selected. 
                    # draw a red rectangle around it and render it on top, including the hitbox.
                    selected_card = card
                    break
        # display on top
        if selected_card is not None:
            pygame.draw.rect(window, (255,255,255), selected_card.rect, width=0)
            pygame.draw.rect(window, (255,0,0), selected_card.rect, width=3)
            window.blit(selected_card.image, selected_card.rect)

        card_counter = 0
        
        for card in list(player.dumpster_info.values()):
            _pos = rect_c(((0.04,0.02*card_counter),(1,1)),MAIN_BOARD_POS)
            try:
                window.blit(pygame.transform.scale(CARDS[card[1]][card[0]], coords(CARD_SIZE_S)), (_pos[0], _pos[1]))
            except TypeError:
                print("Something really bad happened with", _pos)
            card_counter += 1
            if card_counter > 32:
                break
        
        # render babies
        for i in range(player.land_count):
            _loc = rect_c(LAND_BABY_ARMY, MAIN_BOARD_POS)
            window.blit(CARD_BACK_S, (_loc[0],_loc[1]+i*WIDTH*BABY_SPACE))
        for i in range(player.sea_count):
            _loc = rect_c(SEA_BABY_ARMY, MAIN_BOARD_POS)
            window.blit(CARD_BACK_S, (_loc[0],_loc[1]+i*WIDTH*BABY_SPACE))
        for i in range(player.sky_count):
            _loc = rect_c(SKY_BABY_ARMY, MAIN_BOARD_POS)
            window.blit(CARD_BACK_S, (_loc[0],_loc[1]+i*WIDTH*BABY_SPACE))
        
        # render score
        score_text = bigfont.render(str(len(player.score_info)), 1, (255,0,0))
        window.blit(score_text, (0,0))

        # check for user actions
        if pygame.mouse.get_pressed()[0]:
            if not left_button_pressed:
                # do collision detection
                left_button_pressed = True
                
                for r in HB_DRAW:
                    if r.collidepoint(pos):
                        player.drawBTN()

                if HB_DUMPSTER_DIVE.collidepoint(pos):
                    mode = 1 # The board will now switch to the dumpster diving menu

                for r in range(3):
                    if HB_PROVOKE[r].collidepoint(pos):
                        player.provokeBTN(r)

                if selected_card is not None:
                    selected_card.click(player)
                    selected_card = None
                
        else:
            left_button_pressed = False


        # render turn and ply indicators on the very top
        turn_ind = TURN_INDICATOR_POS[(player.turn + 5 - player.player_no + 1) % 5]
        pygame.draw.circle(window, (18,220,150), coords(turn_ind), int(0.04*HEIGHT))

        for x in range(7):
            pygame.draw.circle(window, (224,192,0), coords(PLY_INDICATOR_X0+x*0.01, PLY_INDICATOR_Y), int(0.005*WIDTH), width=2*int(x >= player.ply))

    elif mode > 0: # dumpster dive mode
        window.fill((224,0,64)) 
        # render all dumpster cards

        dumpster_cards = get_dumpster_sprite(player.dumpster_info, page=mode-1)
        dumpster_cards.draw(window)
        
        if pygame.mouse.get_pressed()[0]:
            if not left_button_pressed:
                left_button_pressed = True
                
                something_pressed = False
                for card in dumpster_cards:
                    if card.rect.collidepoint(pos):
                        something_pressed = True 
                        if card.id < 0:
                            mode += 1 # player selected next page
                        else:
                            player.dumpster_dive(card.id)
                            mode = 0
                        break
                # if player doesn't collide with anything but still left clicked, exit the dumpster dive menu
                if not something_pressed:
                    mode = 0

        else:
            left_button_pressed = False
    
    else: # peek mode.
        pass

    # update display at the end of each loop
    pygame.display.update()

pygame.quit()
player.disconnect()
sys.exit() 
