#include "server.hpp"
unsigned char Game::play_part(unsigned int body_part, unsigned int head, const unsigned char dir)
{
    // find the right head
    for (auto it = board[turn % 5].begin(); it != board[turn % 5].end(); ++it)
    {
        if (it->head == head)
        {
            if (it->add_part(lut.at(body_part), dir))
            {
                lut.at(body_part).owner = PLAY((turn % 5) + 1);
                hand[turn%5].erase(std::remove(hand[turn%5].begin(),hand[turn%5].end(),body_part),hand[turn%5].end());
                return 1;
            }
            std::cout << "the body part is not compatible with the select head\n";
            return 0;
        }
    }
    std::cout << "the head " << head << "cannot be found\n";
    return 0;
}
