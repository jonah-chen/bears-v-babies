#include "server.hpp"

// The first byte (0) shall signify the action to be taken
#define DRAW 1
#define PLAY_CARD 2
#define PROVOKE 200
#define DUMPSTER_DIVE 240

// the next byte (1) shall signify a type, if it exists

// the next byte (2) shall signify a direction, if it exists and only required for direction RIGHT

// the next byte (3) is the player ID, given to each player

// the next four bytes (4) shall signify the primary target

// the next eight bytes (8,12) shall signify two secondary targets

unsigned char Game::play(unsigned char input[16])
{
    if (input[3] != pwds[turn % 5])
    {
        std::cout << "the passward is incorrect\n";
        return 0;
    }

    // interpret the three potential cards
    unsigned int target = *(unsigned int*)(input+4);
    unsigned int h1 = *(unsigned int*)(input+8);
    unsigned int h2 = *(unsigned int*)(input+12);

    switch(input[0])
    {
        case DRAW:
            return draw();
        case PLAY_CARD:
            if (lut.find(target)==lut.end())
            {
                std::cout << "the primary target is not a valid card in the game\n";
                return 0;
            }
            switch(lut.at(target).type)
            {
                case BEAR: case SKY: case SEA: case LAND:
                    return play_head(target);
                case LULLABY:
                    return play_lullaby(target, input[1]);
                case SWAP:
                    if (lut.find(h1)==lut.end() or lut.find(h2)==lut.end())
                    {
                        std::cout << "one(+) of the two heads is not a valid card in the game.\n";
                        return 0;
                    }
                    return play_swap(target, h1, h2);
                case DISMEMBER:
                    if (lut.find(h1)==lut.end())
                    {
                        std::cout << "the card you are trying to chop off does not exist.\n";
                        return 0;
                    }
                    return play_dismember(target, h1);
                case MASK:
                    if (lut.find(h1)==lut.end())
                    {
                        std::cout << "the card you are trying to mask does not exist.\n";
                        return 0;
                    }
                    return play_mask(target, h1);
                default: // the default case is playing as body part
                    if (lut.find(h1)==lut.end())
                    {
                        std::cout << "the body attachment does not exist.\n";
                        return 0;
                    }
                    if (lut.at(h1).type != BEAR and lut.at(h1).type != SEA and lut.at(h1).type != LAND and lut.at(h1).type != SKY)
                    {
                        std::cout << "the head the body tried to attach to is not a valid head card\n";
                    }
                    return play_part(target, h1, input[2]==RIGHT ? RIGHT : LEFT);
            }
        case PROVOKE:
            return provoke(input[1]);
        case DUMPSTER_DIVE:
            if (lut.find(target)==lut.end())
            {
                std::cout << "the primary target is not a valid card in the game\n";
                return 0;
            }
            return dumpster_dive(target);
        default:
            return 0;
    }
}