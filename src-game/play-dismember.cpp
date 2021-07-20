#include "server.hpp"
unsigned char Game::play_dismember(unsigned int dismember, unsigned int target)
{
    // the card is played and discarded
    if (lut.at(dismember).owner != (turn % 5) + 1)
    {
        std::cout << "you do not own this card\n";
        return 0;
    }

    // check the target is valid
    if (lut.at(target).owner < -5 or lut.at(target).owner >= 0)
    {
        std::cout << "the target card is not owned by a player\n";
        return 0;
    }

    lut.at(target).owner = DUMPSTER;
    for (int i = 0; i < 5; ++i) // iterate through all five players
    {
        for (auto it = board[i].begin(); it != board[i].end(); ++it) // iterate over all monsters owned by a given player
        {
            // pointer hack
            unsigned int* m = (unsigned int*) &(*it);
            for (int j = 0; j < 9; ++j) // iterate over all potential cards making up the monster
            {
                if (m[j] != NID and lut.at(m[j]).owner == DUMPSTER)
                {
                    // check the card is an edge card
                    if (
                        j > 3 or
                        (j == 0 and it->hat==NID) or
                        (j == 2 and it->ltool==NID) or
                        (j == 3 and it->rtool==NID)
                        )
                    {
                        // remove the part from the monster
                        m[j] = NID;

                        if (j == 0) // if the head gets chopped off, the monster is disabled and the mask is chopped off too
                        {
                            it->type = NONE;
                            if (it->mask!=NID) // oops almost had a major bug here
                            {
                                dumpster.insert(it->mask);
                                lut.at(it->mask).owner = DUMPSTER;
                                it->mask = NID;
                            }
                        }
                        discard(dismember); // discard the dismember card
                        dumpster.insert(target); // move the target to dumpster
                        // check if the monster is fully dead. if not return

                        for (j = 0; j < 9; ++j)
                            if (m[j] != NID)
                                return 1;

                        // if the monster has no parts remaining, free up the space
                        board[i].erase(it);
                        return 1;
                    }
                }
            }
        }
    }
    std::cout << "the target card cannot be found\n";
    return 0;
}
