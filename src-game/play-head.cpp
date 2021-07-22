#include "server.hpp"

unsigned char Game::play_head(unsigned int head, unsigned int mask)
{
    // does NOT verify that the card is actually a head
    // verification must be done before the method is called

    // headless monsters get priority
    for (auto it = board[CUR_PLAYER_ZERO_INDEX].begin(); it != board[CUR_PLAYER_ZERO_INDEX].end(); ++it)
    {
        if (it->head == NID)
        {
            it->head = head;
            lut.at(head).owner = PLAY(CUR_PLAYER);
            REMOVE(head);

            if (mask != NID)
            {
                if (!it->add_part(lut.at(mask)))
                    return 0;
                lut.at(mask).owner = PLAY(CUR_PLAYER);
                REMOVE(mask);
            }
            return 1;
        }
    }
    
    Monster m;
    if (!m.add_part(lut.at(head)))
        return 0;
    // if (mask == NID)
        lut.at(head).owner = PLAY(CUR_PLAYER);

    REMOVE(head);

    if (mask != NID)
    {
        if (!m.add_part(lut.at(mask)))
            return 0;
        lut.at(mask).owner = PLAY(CUR_PLAYER);
        REMOVE(mask);
    }

    board[CUR_PLAYER_ZERO_INDEX].push_back(m);
    return 1;
}