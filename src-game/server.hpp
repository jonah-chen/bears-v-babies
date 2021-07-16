// The game info that is stored on the server
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

// directions
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

// types or monster cards
#define LAND 17
#define SEA 19
#define SKY 23
#define BEAR 29

// other cards
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
#define PLAY(PLAYER) (-(PLAYER))

// a location that is less than 0 can be visible to all players
#define TYPE(X) ((X==LAND)?0:((X==SEA)?1:(X==SKY)?2:3))
#define RTYPE(X) ((X==0)?LAND:((X==1)?SEA:(X==2)?SKY:NONE))

// invalid IDs
#define NID RAND_MAX

// different actions player can take
#define DRAW 1
#define PLAY_CARD 2
#define PROVOKE 200
#define DUMPSTER_DIVE 240

struct Card
{
    unsigned char type, number;
    unsigned int id;
    char owner;

    Card(unsigned char type, unsigned char number);
    bool change_owner(char new_owner);
    inline bool operator==(const Card& other) { return this->id == other.id; }
    inline bool operator==(unsigned int id) { return this->id == id; }
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend inline bool operator< (const Card& left, const Card& right) { return left.id < right.id; }
};

struct Monster
{
    unsigned int head, body, larm, rarm, ltool, rtool, legs, hat, mask;
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
        mask(NID),
        type(NONE),
        body_type(NONE) {}
    
    // add part to the monster. must be called by the server
    bool add_part(const Card& card, const unsigned char dir=LEFT);
    // get the strength
    [[nodiscard]] unsigned char strength() const;
    // kills the monster by removing all parts to the dumpster
    void kill(std::unordered_map<unsigned int, Card>& lut, std::set<unsigned int>& dumpster) const;

    friend std::ostream& operator<<(std::ostream& os, const Monster& monster);
    
};

//template <unsigned char NUM_PLAYERS=5>
class Game
{
    static constexpr unsigned char baby_strengths[9] {2,1,0,2,2,3,1,1,3};

    std::unordered_map<unsigned int, Card> lut; // lookup table is the only placer where the cards are stored on the server

    std::vector<Monster> board[5];
    std::set<unsigned int> deck, dumpster;
    std::vector<unsigned int> hand[5], score[5], babies[3];
    unsigned char turn, int_turn, pwds[5];
    bool ready;

    bool discard(unsigned int id);

    // player actions
    inline unsigned char draw(void) { return draw(turn % 5) == 255 ? 255 : 1; }

    unsigned char provoke(unsigned char type);

    unsigned char dumpster_dive(unsigned int target);

    unsigned char play_head(unsigned int head, unsigned int mask=NID);
    unsigned char play_part(unsigned int body_part, unsigned int head, const unsigned char dir=LEFT);
    unsigned char play_lullaby(unsigned int lullaby, unsigned char type);
    unsigned char play_swap(unsigned int swap, unsigned int head1, unsigned int head2);
    unsigned char play_dismember(unsigned int dismember, unsigned int target);


public:
    /* Game constructed with a seed for the RNG
     */
    Game(unsigned long long seed);

    /* Draws a card from the deck.
     * Return values:
     * 0 - the card went into player's hand
     * 1 - baby card was drawn and automatically placed into the middle
     * 2 - wild provoke was drawn and further actions are required
     */
    unsigned char draw(unsigned char player);

    /* One turn 
     */
    unsigned char _play(unsigned char input[16]);
    int play(unsigned char input[16]);

    // getters
    inline unsigned char get_turn(void) { return turn; }
    inline unsigned char get_int_turn(void) { return int_turn; }
    Card& query (unsigned int id);
    std::vector<unsigned int> fetch_public(void);
    std::vector<unsigned int> fetch_private(char player);
    int connect(void);

    // io
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
