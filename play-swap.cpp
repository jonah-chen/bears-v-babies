#include "server.hpp"
unsigned char Game::play_swap(unsigned int swap, unsigned int head1, unsigned int head2)
{
    // discard the card. if the card is not own by the active player return 0
    if (!discard(swap))
    {
        std::cout << "you do not own this card";
        return 0;
    }
    // ensure the cards are actually heads
    Card& h1 = lut.at(head1);
    Card& h2 = lut.at(head2);

    if ((h1.type != BEAR and h1.type != SKY and h1.type != LAND and h1.type != SEA) or (h2.type != BEAR and h2.type != SKY and h2.type != LAND and h2.type == SEA))
    {
        std::cout << "you can only swap two heads\n";
        return 0;
    }

    // find the owner of the two cards, then swap the heads
    for (auto it = board[h1.owner-1].begin(); it != board[h1.owner-1].end(); ++it)
    {
        if (it->head == head1)
        {
            it->head = head2;
            break;
        }
    }

    for (auto it = board[h2.owner-1].begin(); it != board[h2.owner-1].end(); ++it)
    {
        if (it->head == head2)
        {
            it->head = head1;
            break;
        }
    }

    // swap the owners
    h1.owner += h2.owner;
    h2.owner = h1.owner - h2.owner;
    h1.owner -= h2.owner;

    return 1;
}