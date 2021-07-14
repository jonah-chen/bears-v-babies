#include <cstring>
#include <fstream>
#include "server.hpp"

int main()
{
    std::ios_base::sync_with_stdio(false);

    Game g(4001);
    std::cout << g.query(230230722) << std::endl;
    unsigned int id, type, dir, t, c1, c2;
    unsigned char input[16];
    while (1)
    {
        std::ofstream file;
        file.open("state.txt");
        file << g;
        file.close();

        std::cout << "input the action (draw 1, play 2, provoke 200, dumpster dive 240)\n";
        std::cin >> id;
        if (id == PLAY_CARD or id == DUMPSTER_DIVE)
        {
            std::cout << "input the id of the main card\n";
            std::cin >> t;
        }
        if (id == PLAY_CARD)
        {
            std::cout << "if the direction is right, please input 1. otherwise input 0.\n";
            std::cin >> dir;
            std::cout << "input the id of the secondary target\n";
            std::cin >> c1;
            std::cout << "input the id of the secondary target(2)\n";
            std::cin >> c2;
        }
        if (id == PROVOKE or id == PLAY_CARD)
        {
            std::cout << "input the type if applicable (land 17, sea 19, sky 23), or zero if not\n";
            std::cin >> type;
        }
        input[0] = id;
        input[1] = type;
        input[2] = dir ? RIGHT : LEFT;
        input[3] = 46;
        std::memcpy(input+4, &t, 4);
        std::memcpy(input+8, &c1, 4);
        std::memcpy(input+12, &c2, 4);
        int output = g.play(input);
        std::cout << "Player" << ((output >> 8) % 5) + 1<< std::endl;
        std::cout << "Turn#" << (output % 0x100) << std::endl;
    }
}
