import pygame
import os

WIDTH = 1920
HEIGHT = 1080

pygame.init()
def coords(x,y):
    return (int(WIDTH*x), int(HEIGHT*y))
def inv_c(x,y=None):
    if y:
        return x/WIDTH, y/HEIGHT
    return x[0]/WIDTH, x[1]/HEIGHT


window = pygame.display.set_mode((WIDTH,HEIGHT))


BACKGROUND = pygame.transform.scale(
                pygame.image.load("../assets/bkgd.jpg"), 
                coords(1, 1)
                )




pygame.display.set_caption("bears-v-babies-client")
CHESS_PIECE = pygame.transform.scale(
                pygame.image.load("../assets/chess_king.jpg"), 
                (coords(0.15, 0.15))
                )




x = 0.5
y = 0

run = True
while run:
    pygame.time.delay(20) #50tps

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
    window.fill((0,0,0))
    window.blit(BACKGROUND, (0,0))
    window.blit(CHESS_PIECE, coords(x,y))
    if pygame.mouse.get_pressed()[0]:
        x, y = inv_c(pygame.mouse.get_pos())
    pygame.display.update()

pygame.quit()