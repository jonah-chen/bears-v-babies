#include "server.hpp"
unsigned char Game::play_head(unsigned int head, unsigned int mask)
{
    // does NOT verify that the card is actually a head
    // verification must be done before the method is called

    // headless monsters get priority
    for (auto it = board[turn%5].begin(); it != board[turn%5].end(); ++it)
    {
        if (it->head == NID)
        {
            it->head = head;
            lut.at(head).owner = PLAY((turn % 5) + 1);
            hand[turn%5].erase(std::remove(hand[turn%5].begin(),hand[turn%5].end(),head),hand[turn%5].end());

            if (mask != NID)
            {
                if (!it->add_part(lut.at(mask)))
                    return 0;
                lut.at(mask).owner = PLAY((turn % 5) + 1);
                hand[turn%5].erase(std::remove(hand[turn%5].begin(),hand[turn%5].end(),mask),hand[turn%5].end());
            }
            return 1;
        }
    }
    
    Monster m;
    if (!m.add_part(lut.at(head)))
        return 0;
    // if (mask == NID)
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