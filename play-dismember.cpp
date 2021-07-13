#include "server.hpp"
unsigned char Game::play_dismember(unsigned int dismember, unsigned int target)
{
    // the card is played and discarded
    if (!discard(dismember))
    {
        std::cout << "you do not own this card";
        return 0;
    }

    // check the target is valid
    if (lut.at(target).owner < -5 or lut.at(target).owner >= 0)
        return 0;

    for (int i = 0; i < 5; ++i)
    {
        for (auto it = board[i].begin(); it != board[i].end(); ++it)
        {
            // pointer hack
            unsigned int* m = (unsigned int*) &(*it);
            for (int j = 0; j < 8; ++j)
            {
                if (lut.at(m[j]).owner == DUMPSTER)
                {
                    m[j] = NID;
                    return 1;
                }
            }
        }
    }
}
