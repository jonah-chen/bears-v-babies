#include "server.hpp"
unsigned char Game::play_head(unsigned int head, unsigned int mask)
{
    // does NOT verify that the card is actually a head
    // verification must be done before the method is called
    Monster m;
    if (!m.add_part(lut.at(head)))
        return 0;
    if (mask == NID)
        lut.at(head).owner = PLAY((turn % 5) + 1);

    hand[turn%5].erase(std::remove(hand[turn%5].begin(),hand[turn%5].end(),head),hand[turn%5].end());

    if (mask != NID)
    {
        if (!m.add_part(lut.at(mask)))
            return 0;
        lut.at(mask).owner = PLAY((turn % 5) + 1);
        hand[turn%5].erase(std::remove(hand[turn%5].begin(),hand[turn%5].end(),mask),hand[turn%5].end());
    }

    board[turn % 5].push_back(m);
    return 1;
}