#include "server.hpp"
#include <random>
#define REP(I) for (int i = 0; i < (I); ++i)
#define FORP for (int py = 0; py < NUM_PLAYERS; ++py)

Game::Game(unsigned long long seed, unsigned char NUM_PLAYERS) : NUM_PLAYERS(NUM_PLAYERS), turn(), int_turn()
{
    // check if the number of players are valid
    if (NUM_PLAYERS > 5 or NUM_PLAYERS < 2)
    {
        std::cout << "It is not allowed to make a game with " << NUM_PLAYERS << " players.\n";
        throw "";
    }

    // set the game seed
    srand(seed);

    // set passwords to all 0, signifying nobody is connected yet
    FORP
        pwds[py] = 0;

    ready = false; // game is not ready yet

    // each player starts with bear card
    FORP
    {
        Card c(BEAR, py);
        c.owner = py + 1;
        lut.insert({c.id,c}); // bear cards are added to the LUT
        hand[py].push_back(c.id);
    }
    
    auto shuffle = [&](unsigned char type, unsigned char number)
    {
        Card tmp(type, number);
        lut.insert({tmp.id, tmp});
        deck.insert(tmp.id);
    };

    // body parts
    REP(7)
    {
        shuffle(LAND, i);
        shuffle(SEA, i);
        shuffle(SKY, i);
    }

    REP(9)
        shuffle(C_TORSO, i);

    REP(3)
        shuffle(TORSO, i);

    REP(3)
        shuffle(M_BODY, i);

    REP(2)
        shuffle(AL_BODY, i);

    REP(7)
        shuffle(LEGS, i);

    REP(10)
        shuffle(ARM, i);

    // other cards
    REP(5)
        shuffle(TOOL, i);

    REP(2)
    {
        shuffle(LULLABY, i);
        shuffle(SWAP, i);
    }

    REP(3)
    {
        shuffle(MASK, i);
        shuffle(HAT, i);
        shuffle(DISMEMBER, i);
    }

    // babies
    REP(9)
    {
        shuffle(-LAND, i);
        shuffle(-SEA, i);
        shuffle(-SKY, i);
    }

    // players each draw to five cards
    FORP
        for (int i = 1; i < 5;)
            if(!draw(py)) ++i;

    // add wild provokes
    REP(2)
        shuffle(WILD_PROVOKE, i);
}

unsigned char Game::draw(unsigned char player)
{
    if (player >= NUM_PLAYERS)
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
        lut.at(id).owner = DUMPSTER;
        dumpster.insert(id);
        return 255;
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
    if (lut.at(id).owner != CUR_PLAYER)
        return false;
    REMOVE(id);
    lut.at(id).owner = DUMPSTER;
    dumpster.insert(id);
    return true;
}
