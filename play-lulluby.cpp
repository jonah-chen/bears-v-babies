#include "server.hpp"
unsigned char Game::play_lullaby(unsigned int lullaby, unsigned char type)
{
    // discard lullaby card
    if (!discard(lullaby))
    {
        std::cout << "you do not own this card";
        return 0;
    }

    unsigned char _ty = TYPE(type);
    if (_ty == 3)
    {
        std::cout << "you cannot lullaby the type " << (int)type << "\n";
        return 0;
    }
    unsigned char num_babies = babies[_ty].size();
    unsigned int tmp;

    if (!num_babies)
    {
        std::cout << "cannot lullaby 0 babies\n";
        return 0;
    }

    bb_p[_ty] += (num_babies + 1) / 2; // advance the counter by half the babies rounding up

    // pop_back and insert to the dumpster
    for (int _ = 0; _ < (num_babies + 1) / 2; ++_)
    {
        tmp = babies[_ty].back();
        dumpster.insert(tmp);
        babies[_ty].pop_back();
        lut.at(tmp).owner = DUMPSTER;
    }

    return 1;
}