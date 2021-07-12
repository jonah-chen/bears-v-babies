// The game info that would be stored on the server

#include "server.h"
#include <cstdlib>
// creating a card
Card::Card(unsigned char type)
{
    this->type = type;
    id = (unsigned int)rand();
    owner = DECK;
    adj[0] = adj[1] = adj[2] = adj[3] = 0;
    
    if (type == LAND or type == SEA or type == SKY or type == BEAR) // heads
    {
        att[UP] = 5; // heads have 5 stiches on top, you can't see them but they're there
        att[LEFT] = NONE;
        att[DOWN] = 3;
        att[RIGHT] = NONE;
    }
    
    else if (type == HAT)
    {
        att[UP] = NONE;
        att[LEFT] = NONE;
        att[RIGHT] = NONE;
        att[DOWN] = 5;
    }
    else if (type == TOOL)
    {
        att[UP] = NONE;
        att[LEFT] = NONE;
        att[RIGHT] = 1;
        att[DOWN] = NONE;
    }

    else if (type == ARM)
    {
        att[UP] = NONE;
        att[LEFT] = 1;
        att[RIGHT] = 2;
        att[DOWN] = NONE;
    }

    else if (type == LEGS)
    {
        att[UP] = 4;
        att[LEFT] = NONE;
        att[DOWN] = NONE;
        att[RIGHT] = NONE;
    }

    else if (type == AL_BODY)
    {
        att[UP] = 3;
        att[LEFT] = 2;
        att[RIGHT] = 2;
        att[DOWN] = NONE;
    }

    else if (type == M_BODY)
    {
        att[UP] = 3;
        att[LEFT] = 1;
        att[RIGHT] = 1;
        att[DOWN] = NONE;
    }

    else if (type == C_TORSO)
    {
        att[UP] = 3;
        att[LEFT] = 2;
        att[RIGHT] = 2;
        att[DOWN] = 4;
    }
    
    else if (type == TORSO)
    {
        att[UP] = 3;
        att[LEFT] = 1;
        att[RIGHT] = 1;
        att[DOWN] = 4;
    }

    else
        att[0] = att[1] = att[2] = att[3] = NONE;
}

unsigned char Card::rehash()
{
    id = (unsigned int) rand();
    return id;
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

bool Card::attach(Card* other)
{
    if (owner != other->owner or owner == DECK or owner == DUMPSTER or other->owner == DECK or other->owner == DUMPSTER)
    {
        std::cout << "the owners " << (int)other->owner << " and " << (int)owner << " are not compatiable\n";
        return false;
    }
    // attaching up to down
    if (attachable(UP,DOWN,*other))
    {
        adj[UP] = other->id;
        other->adj[DOWN] = id;
        return true;
    }
    // attaching down to up
    if (attachable(DOWN,UP,*other))
    {
        adj[DOWN] = other->id;
        other->adj[UP] = id;
        return true;
    }
    
    // sideways attachment (4 cases)
    if (attachable(RIGHT,LEFT,*other))
    {
        adj[RIGHT] = other->id;
        other->adj[LEFT] = id;
        return true;
    }

    if (attachable(LEFT,RIGHT,*other))
    {
        adj[LEFT] = other->id;
        other->adj[RIGHT] = id;
        return true;
    }

    if (attachable(LEFT,LEFT,*other))
    {
        adj[LEFT] = other->id;
        other->adj[LEFT] = id;
        return true;
    }

    if (attachable(RIGHT,RIGHT,*other))
    {
        adj[RIGHT] = other->id;
        other->adj[RIGHT] = id;
        return true;
    }
    
    // cannot attach
    std::cout << "the cards cannot be attached for other reasons\n";
    return false;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << "id:" << card.id << ", owner:" << (int)card.owner << ", type:" << (int)card.type << ", attachments: " << card.adj[0] << "," << card.adj[1] << "," << card.adj[2] << "," << card.adj[3] << " @" << &card << std::endl;
    return os;
}

int main()
{
    srand(time(0));
    Card c1(LEGS);
    Card c2(BEAR);
    Card c3(TORSO);
    std::cout << c1;
    std::cout << c2;
    c2.attach(&c3);
    std::cout << c3;
    std::cout << c2;
    c1.change_owner(1);
    c2.change_owner(3);
    c3.change_owner(3);
    c2.attach(&c3);
    std::cout << c1;
    std::cout << c2;
    std::cout << c3;
    
    Game g(time(0));
    std::cout << g;
}
