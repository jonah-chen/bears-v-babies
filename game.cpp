#include "server.h"

#define REP(I) for (int i = 0; i < I; ++i) 
#define FORP for (int py = 0; py < 5; ++py)
Game::Game(unsigned long long seed)
{
    turn = 0; int_turn = 0;

    // set the game seed
    srand(seed);

    // each player starts with bear card
    FORP
    {
        Card c(BEAR);
        c.owner = py + 1;
        lut[c.id] = &c;
        hand[py].push_back(c);
    }

    // shuffle?
    
    // body parts
    REP(7)
    {
        deck.insert(Card(LAND));
        deck.insert(Card(SEA));
        deck.insert(Card(SKY));
    }

    REP(9)
        deck.insert(Card(C_TORSO));

    REP(3)
        deck.insert(Card(TORSO));
    
    REP(3)
        deck.insert(Card(M_BODY));

    REP(2)
        deck.insert(Card(AL_BODY));

    REP(7)
        deck.insert(Card(LEGS));
    
    REP(10)
        deck.insert(Card(ARM));
    
    // other cards
    REP(5)
        deck.insert(Card(TOOL));
    
    REP(2)
    {
        deck.insert(Card(LULLABY));
        deck.insert(Card(SWAP));
    }
    
    REP(3)
    {
        deck.insert(Card(MASK));
        deck.insert(Card(HAT));
        deck.insert(Card(DISMEMBER));
    }

    // babies
    REP(9)
    {
        deck.insert(Card(-LAND));
        deck.insert(Card(-SEA));
        deck.insert(Card(-SKY));
    }
    
    // add to LUT
    for (auto it = deck.begin(); it != deck.end(); ++it)
        lut[it->id] = &(*it);
    std::cout << *this;
    // players each draw to five cards
    //
    FORP
        for (int i = 1; i < 5;)
            if(draw(py)) ++i;

    REP(2)
    {
        Card c(WILD_PROVOKE);
        deck.insert(c);
        lut[c.id] = &c;        
    }
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os << "BABY INFO: L=" << game.land.size() << " S=" << game.sea.size() << " A=" << game.sky.size();
    os << "\nDUMPSTER INFO: size=" << game.dumpster.size() << "\n";
    for (auto it = game.dumpster.begin(); it != game.dumpster.end(); ++it)
        os << *it;
    os << "\nPLAYER INFO:\n";
    FORP
    {
        os << "p" << py << ": score=" << game.score[py].size() << ", strength: L=" << (int)game.calc_strength(py, LAND) << " S=" << (int)game.calc_strength(py, SEA) << " A=" << (int)game.calc_strength(py, SKY) << "\nhand:\n";
        for (auto it = game.hand[py].begin(); it != game.hand[py].end(); ++it)
            os << *it;
        os << "board:\n";
        for (auto it = game.board[py].begin(); it != game.board[py].end(); ++it)
            os << *it;
        os << "babies:\n";
        for (auto it = game.score[py].begin(); it != game.score[py].end(); ++it)
            os << *it;
    }
    os << "\nDECK INFO: remaining=" << game.deck.size() << "\n";
    for (auto it = game.deck.begin(); it != game.deck.end(); ++it)
        os << *it;
    return os;
}

bool Game::draw(unsigned char player)
{
    auto nci = deck.begin();
    deck.erase(nci);
    switch(nci->type)
    {
        case (unsigned char)-LAND:
            land.push_back(*nci);
            lut[nci->id] = &(land.back());
            return false;
        case (unsigned char)-SEA:
            sea.push_back(*nci);
            lut[nci->id] = &(sea.back());
            return false;
        case (unsigned char)-SKY:
            sky.push_back(*nci);
            lut[nci->id] = &(sky.back());
            return false;
        case WILD_PROVOKE:
            // do wild provoke
            return false;
        default:
            hand[player].push_back(*nci);
            hand[player].back().change_owner(player+1);
            lut[nci->id] = &(hand[player].back());
            return true;
    }
}

unsigned char Game::calc_strength(unsigned char player, unsigned char type) const
{
    unsigned char strength = 0, tmp;
    std::vector<const Card*> heads;
    for (auto it = board[player].begin(); it != board[player].end(); ++it)
    {
        if (it->type == type or it->type == BEAR)
            heads.push_back(&(*it));
    }
    
    for (const Card* head : heads)
    {
        tmp = head->type == type ? 2 : 3;
        unsigned int b_id = head->adj[DOWN];
        if (b_id == NONE)
        {
            strength += head->adj[UP] != NONE ? tmp*2 : tmp;
            continue;
        }
        
        const Card *body = lut.at(b_id);
        
        if ((body->type == C_TORSO or body->type == TORSO) and body->adj[DOWN] != NONE)
            tmp += 2;
        if (body->type == M_BODY or body->type == TORSO)
        {
            if (body->adj[LEFT] != NONE)
                tmp--;
            if (body->adj[RIGHT] != NONE)
                tmp--;
        }
        else
        {
            if (body->adj[LEFT] != NONE)
            {
                const Card *arm = lut.at(body->adj[LEFT]);
                if (!(arm->adj[LEFT] == NONE or arm->adj[RIGHT] == NONE))
                    tmp++;
            }
            if (body->adj[RIGHT] != NONE)
            {
                const Card *arm = lut.at(body->adj[RIGHT]);
                if (!(arm->adj[LEFT] == NONE or arm->adj[RIGHT] == NONE))
                    tmp++;
            }
        }

        strength += head->adj[UP] != NONE ? tmp*2 : tmp;
    }
    return strength;
}

unsigned char Game::play(unsigned char action, unsigned char type)
{
    if (action == PROVOKE)
    {
        if (type != LAND and type != SEA and type != SKY)
        {
            std::cout << "something went wrong\n";
            return 0;
        }

        unsigned char max_strength = 0;
        
        FORP
        {
            
        }
    }
}

unsigned char Game::play(unsigned char action, const Card& card)
{
    if (action == DUMPSTER_DIVE)
    {
        if (int_turn > 0)
        {
            std::cout << "you cannot dumpster dive this turn anymore\n";
            return 0;
        }
        
        auto found = dumpster.find(card);
        if (found==dumpster.end())
        {
            std::cout << "the card you dived for cannot be found in the dumpster\n";
            return 0;
        }

        // succesful dive
        hand[turn % 5].push_back(*found);
        dumpster.erase(found);
        return 19;
    }
}
