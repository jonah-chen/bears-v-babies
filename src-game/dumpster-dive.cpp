#include "server.hpp"
unsigned char Game::dumpster_dive(unsigned int target)
{
    if (int_turn > 0)
    {
        std::cout << "you cannot dumpster dive this turn anymore\n";
        return 0;
    }

    auto found = dumpster.find(target);
    if (found==dumpster.end())
    {
        std::cout << "the card you dived for cannot be found in the dumpster\n";
        return 0;
    }

    // dumpster diving babies
    switch (lut.at(target).type)
    {
        case (unsigned char)-LAND: case (unsigned char)-SEA: case (unsigned char)-SKY:
            babies[TYPE((unsigned char)-lut.at(target).type)].push_back(*found);
            dumpster.erase(found);
            lut.at(*found).owner = MIDDLE;
            return 19;

        default:
            hand[turn % 5].push_back(*found);
            dumpster.erase(found);
            lut.at(*found).owner = (turn % 5) + 1;
            return 19;
    }
}