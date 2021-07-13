#include "server.hpp"
unsigned char Game::play_head(unsigned int head)
{
    // does NOT verify that the card is actually a head
    // verification must be done before the method is called
    Monster m;
    if (m.add_part(lut.at(head)))
    {
        lut.at(head).owner = PLAY((turn % 5) + 1);
        board[turn % 5].push_back(m);
        return 1;
    }
    return 0;
}