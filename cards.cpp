// The game info that would be stored on the server

#include "server.hpp"
#include <cstdlib>
// creating a card
Card::Card(unsigned char type)
{
    this->type = type;
    id = rand();
    owner = DECK;
}

bool Card::change_owner(char new_owner)
{
    if (new_owner == 0 || new_owner >= 7 || new_owner < -7)
    {
        std::cout << "the owner " << (int)new_owner << " cannot own this card\n";
        return false;
    }
    owner = new_owner;
    return true;
}

