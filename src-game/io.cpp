#include "server.hpp"
#include <iomanip>
#define REP(I) for (int i = 0; i < (I); ++i)
#define FORP for (int py = 0; py < 5; ++py)

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << "id:" << card.id << ", owner:" << (int)card.owner << ", type:" << (int)card.type << ", no:" << (int)card.number << " @" << &card << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Monster& monster)
{
    os << "MONSTER: type=" << (int)monster.type << " strength=" << (int)monster.strength();
    os << "\n|head     |body     |larm     |rarm     |ltool    |rtool    |legs     |hat      |mask     |\n";
    unsigned int* m = (unsigned int*)&monster;
    for(int i = 0; i < 9; ++i)
    {
        if (m[i] == NID)
            os << "     X    ";
        else
            os << std::setw(10) << m[i];
    }
    os << "\n";
    return os;
}


std::ostream& operator<<(std::ostream& os, const Game& game)
{
    // preperation
    constexpr char ts[3] {'L','S','A'};
    auto calc_strength = [&](unsigned char player, unsigned char type) -> int
    {
        unsigned char py_strength = 0;
        for (Monster m : game.board[player])
            if (m.type == BEAR or m.type == type)
                py_strength += m.strength();
        return (int)py_strength;
    };

    // visible info
    os << "BABY INFO: ";
    REP(3)
        os << ts[i] << "=" << game.babies[i].size() << " ";
    os << "\nDUMPSTER INFO: size=" << game.dumpster.size() << "\n";
    for (unsigned int id : game.dumpster)
        os << game.lut.at(id);

    // (some)invisible info

    os << "\nPLAYER INFO:\n";
    FORP
    {
        os << "p" << py << ": score=" << game.score[py].size() << ", strength:";
        REP(3)
        os << " " << ts[i] << "=" << calc_strength(py, RTYPE(i));
        os << "\nhand:\n";
        for (unsigned int id : game.hand[py])
            os << game.lut.at(id);
        os << "board:\n";
        for (auto it = game.board[py].begin(); it != game.board[py].end(); ++it)
            os << *it;
        os << "babies:\n";
        for (unsigned int id : game.score[py])
            os << game.lut.at(id);
    }

    os << "\nDECK INFO: remaining=" << game.deck.size() << "\n";
    for (unsigned int id : game.deck)
        os << game.lut.at(id);
    return os;
}
