// The game info that is stored on the server
//

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
// cards

// directions
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

// types
#define LAND 17
#define SEA 19
#define SKY 23
#define BEAR 29

#define NONE 0
#define TOOL 1
#define LULLABY 2
#define HAT 3
#define MASK 4
#define SWAP 5
#define DISMEMBER 6
#define WILD_PROVOKE 7
#define C_TORSO 8
#define TORSO 9
#define M_BODY 10
#define AL_BODY 11
#define LEGS 12
#define ARM 13

// locations
#define DECK 0
#define MIDDLE -6
#define DUMPSTER -7
#define PLAY(PLAYER) (-PLAYER)
// a location that is less than 0 can be visible to all players


// actions
#define DUMPSTER_DIVE 43
#define PROVOKE 44

#define ATTACH 5
#define PLACE_HEAD 6
#define DRAW 7


#define TYPE(X) (X==LAND)?0:((X==SEA)?1:(X==SKY)?2:3)
#define RTYPE(X) (X==0)?LAND:((X==1)?SEA:(X==2)?SKY:NONE)

#define NID RAND_MAX
class Card
{
    unsigned char type;
    unsigned int id;
    char owner;
    friend class Game;
    friend struct Monster;
public:
    Card(unsigned char type);
    bool change_owner(char new_owner);
    inline bool operator==(const Card& other) { return this->id == other.id; }
    inline bool operator==(unsigned int id) { return this->id == id; }
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend inline bool operator< (const Card& left, const Card& right) { return left.id < right.id; }
};

struct Monster
{
    unsigned int head, body, larm, rarm, ltool, rtool, legs, hat;
    unsigned char type, body_type;
    // every monster must have a head
    Monster(void) :
        head(NID), 
        body(NID), 
        larm(NID), 
        rarm(NID),
        ltool(NID),
        rtool(NID),
        legs(NID),
        hat(NID),
        type(NONE),
        body_type(NONE) {}
    
    // add part to the monster. must be called by the server
    bool add_part(const Card& card, const unsigned char dir=LEFT);
    // get the strength
    unsigned char strength() const;
    // kills the monster by removing all parts to the dumpster
    void kill(std::unordered_map<unsigned int, Card>* lut) const;

    friend std::ostream& operator<<(std::ostream& os, const Monster& monster);
    
};

class Game
{
    std::unordered_map<unsigned int, Card> lut; // lookup table is the only placerwhere the cards are stored on the server
    
    std::set<unsigned int> deck, dumpster;
    std::vector<unsigned int> hand[5], score[5], babies[3];
    std::vector<Monster> board[5];
    std::vector<unsigned char> bb_s[3]; 
    unsigned char turn, int_turn, bb_p[3];    
public:
    /* Game constructed with a seed for the RNG
     */
    Game(unsigned long long seed);
    
    /* One turn 
     */
    // player 0 starts the game
    unsigned char play(unsigned char action); // 0 return value means failure
    unsigned char play(unsigned char action, unsigned char type);
    unsigned char play(unsigned char action, unsigned int id);
    unsigned char play(unsigned char action, unsigned int id, unsigned int id2);
    
    /* Draws a card from the deck. 
     * Return values:
     * 0 - the card went into player's hand
     * 1 - baby card was drawn and automatically placed into the middle
     * 2 - wild provoke was drawn and further actions are required
     */
    unsigned char draw(unsigned char player); 
    
    
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
