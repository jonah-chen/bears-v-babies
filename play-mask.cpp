#include "server.hpp"
unsigned char Game::play_mask(unsigned int mask, unsigned int head)
{
    play_head(head);
    lut.at(head).owner = (turn % 5) + 1;
    lut.at(mask).owner = PLAY((turn % 5) + 1);
    return 1;
}