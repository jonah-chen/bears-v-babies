#include "server.hpp"

unsigned char Game::play_part(unsigned int body_part, unsigned int head, const unsigned char dir)
{
    // find the right head
    for (auto it = board[CUR_PLAYER_ZERO_INDEX].begin(); it != board[CUR_PLAYER_ZERO_INDEX].end(); ++it)
    {
        if (it->head == head)
        {
            if (it->add_part(lut.at(body_part), dir))
            {
                lut.at(body_part).owner = PLAY(CUR_PLAYER);
                REMOVE(body_part);
                return 1;
            }
            std::cout << "the body part is not compatible with the select head\n";
            return 0;
        }
    }
    std::cout << "the head " << head << "cannot be found\n";
    return 0;
}
