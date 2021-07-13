#include "server.hpp"
#include <algorithm>
#include <random>
#define REP(I) for (int i = 0; i < (I); ++i)
#define FORP for (int py = 0; py < 5; ++py)

Game::Game(unsigned long long seed) : turn(), int_turn()
{

    // set the game seed
    srand(seed);

    FORP
        pwds[py] = rand();

    // each player starts with bear card
    FORP
    {
        Card c(BEAR);
        c.owner = py + 1;
        lut.insert({c.id,c}); // bear cards are added to the LUT
        hand[py].push_back(c.id);
    }
    
    auto shuffle = [this](unsigned char type)
    {
        Card tmp(type);
        lut.insert({tmp.id, tmp});
        deck.insert(tmp.id);
    };
    
    // body parts
    REP(7)
    {
        shuffle(LAND);
        shuffle(SEA);
        shuffle(SKY);
    }

    REP(9)
        shuffle(C_TORSO);

    REP(3)
        shuffle(TORSO);
    
    REP(3)
        shuffle(M_BODY);

    REP(2)
        shuffle(AL_BODY);

    REP(7)
        shuffle(LEGS);
    
    REP(10)
        shuffle(ARM);
    
    // other cards
    REP(5)
        shuffle(TOOL);
    
    REP(2)
    {
        shuffle(LULLABY);
        shuffle(SWAP);
    }
    
    REP(3)
    {
        shuffle(MASK);
        shuffle(HAT);
        shuffle(DISMEMBER);
    }

    // babies
    REP(9)
    {
        shuffle(-LAND);
        shuffle(-SEA);
        shuffle(-SKY);
    }
    
    // players each draw to five cards
    FORP
        for (int i = 1; i < 5;)
            if(!draw(py)) ++i;
    
    // add wild provokes
    REP(2)
        shuffle(WILD_PROVOKE);

    // generate baby strengths
    REP(3)
    {
        bb_s[i] = std::vector<unsigned char>{0,1,1,1,2,2,2,3,3};
        std::shuffle(bb_s[i].begin(), bb_s[i].end(), std::mt19937(std::random_device()()));
    }
}

unsigned char Game::draw(unsigned char player)
{
    if (player > 4)
    {
        std::cout << "invalid player cannot draw cards";
        return 0;
    }
    auto nci = deck.begin();
    deck.erase(nci);
    unsigned int id = *nci;
    unsigned char ty = lut.at(id).type;
    
    if (ty == WILD_PROVOKE)
    {
        // do wild provoke
        return 2;
    }
    
    else if (TYPE((unsigned char)-ty) == 3) // not a baby, so draw into hand
    {
        hand[player].push_back(id);
        lut.at(id).change_owner(player+1);
        return 0;
    }
    else // baby card, place in middle
    {
        babies[TYPE((unsigned char)-ty)].push_back(id);
        lut.at(id).change_owner(MIDDLE);
        return 1;
    }
}

bool Game::discard(unsigned int id)
{
    if (lut.at(id).owner != (turn % 5) + 1)
        return false;
    hand[turn%5].erase(std::remove(hand[turn%5].begin(),hand[turn%5].end(),id),hand[turn%5].end());
    lut.at(id).owner = DUMPSTER;
    dumpster.insert(id);
    return true;
}