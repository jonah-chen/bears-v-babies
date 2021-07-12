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
#define DUMPSTER -7
#define PLAY(PLAYER) (-PLAYER)
// a location that is less than 0 can be visible to all players


// actions
#define DUMPSTER_DIVE 43
#define PROVOKE 44

#define ATTACH 5
#define PLACE_HEAD 6
#define DRAW 7

class Card
{
    unsigned char type, att[4];
    unsigned int id, adj[4];
    char owner;
    inline bool attachable(unsigned char dir, unsigned char other_dir, const Card& other) { return att[dir] == other.att[other_dir] and !adj[dir] and !other.adj[other_dir]; }
    friend class Game;
public:
    Card(unsigned char type);
    unsigned char rehash(void);
    bool change_owner(char new_owner);
    bool attach (Card* other);
    inline bool operator==(const Card& other) { return this->id == other.id; }
    inline bool operator==(unsigned int id) { return this->id == id; }
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend inline bool operator< (const Card& left, const Card& right) { return left.id < right.id; }
};

class Game
{
    std::set<Card> deck, dumpster;
    std::vector<Card> hand[5], board[5], score[5], land, sea, sky;
    std::unordered_map<int,const Card*> lut;
    
    unsigned char turn, int_turn;

    unsigned char calc_strength(unsigned char, unsigned char) const;
public:
    Game(unsigned long long seed);
    // player 0 starts the game
    unsigned char play(unsigned char action); // 0 return value means failure
    unsigned char play(unsigned char action, unsigned char type);
    unsigned char play(unsigned char action, const Card& card);
    unsigned char play(unsigned char action, const Card& card, const Card& card2);
    bool draw(unsigned char player);
    
    
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
