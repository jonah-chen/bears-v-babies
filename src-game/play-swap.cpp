#include "server.hpp"

unsigned char Game::play_swap(unsigned int swap, unsigned int head1, unsigned int head2)
{
    if (head1 == head2)
    {
        std::cout << "swapping a head with itself is not supported\n";
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

    // discard the card. if the card is not own by the active player return 0
    if (!discard(swap))
    {
        std::cout << "you do not own this card";
        return 0;
    }

    std::vector<Monster>::iterator _head1;
    // find the owner of the two cards, then swap the heads and head types
    for (auto it = board[-(h1.owner)-1].begin(); it != board[-(h1.owner)-1].end(); ++it)
    {
        if (it->head == head1)
        {
            it->type = lut.at(head2).type;
            it->head = head2;
            _head1 = it;
            break;
        }
    }

    for (auto it = board[-(h2.owner)-1].begin(); it != board[-(h2.owner)-1].end(); ++it)
    {
        if (it->head == head2)
        {
            it->type = lut.at(head1).type;
            it->head = head1;
            // if needed, swap masks
            if (_head1->mask==NID and it->mask!=NID)
            {
                _head1->mask = it->mask;
                lut.at(_head1->mask).owner = h1.owner;
                it->mask = NID;
            }
            else if (_head1->mask!=NID and it->mask==NID)
            {
                it->mask = _head1->mask;
                lut.at(it->mask).owner = h2.owner;
                _head1->mask = NID;
            }
            break;
        }
    }

    // swap the owners
    h1.owner += h2.owner;
    h2.owner = h1.owner - h2.owner;
    h1.owner -= h2.owner;

    return 1;
}