#include "server.hpp"
#include <numeric>
unsigned char Game::provoke(unsigned char type)
{
    // error checking
    if (int_turn > 0 and int_turn < 20)
    {
        std::cout << "you cannot provoke this turn anymore\n";
        return 0;
    }

    if (type != LAND and type != SEA and type != SKY)
    {
        std::cout << "the type provoked does not exist\n";
        return 0;
    }

    unsigned char num_babies = babies[TYPE(type)].size();
    if (!num_babies)
    {
        std::cout << "cannot provoke 0 babies\n";
        return 0;
    }

    // preliminary
    unsigned char max_strength = 1, py_strength, b_py = 8;
    auto first_baby = bb_s[TYPE(type)].begin() + bb_p[TYPE(type)];
    unsigned char b_strength = std::accumulate(first_baby, first_baby+num_babies, 0); // baby army strength
    bb_p[TYPE(type)] += num_babies;

    for (int py = 0; py < 5; ++py)
    {
        // calculate the player's army strength for that type
        py_strength = 0;
        for (Monster m : board[py])
            if (m.type == BEAR or m.type == type)
                py_strength += m.strength();

        // if the player is too weak, then their army dies
        if (py_strength < b_strength and py_strength > 1)
        {
            if (py_strength > max_strength)
                max_strength = py_strength;
            std::vector<Monster> crippled;
            for (auto it = board[py].begin(); it != board[py].end(); ++it)
            {
                if (it->type == BEAR or it->type == type)
                    it->kill(lut, dumpster);
                else
                    crippled.push_back(*it);
            }
            board[py] = std::move(crippled);
        }
            // if the player is stronger than all other players
        else if (py_strength > max_strength or (py_strength == max_strength and b_py == 8))
        {
            max_strength = py_strength;
            b_py = py;
        }
            // two players tie
        else if (py_strength == max_strength)
            b_py = 9;
    }
    if (max_strength == 1)
    {
        std::cout << "can't provoke no monsters\n";
        return 0;
    }
    // award points
    if (b_py < 8)
    {
        for (unsigned int b : babies[TYPE(type)])
            lut.at(b).owner = b_py + 1;
        score[b_py].insert(score[b_py].end(), babies[TYPE(type)].begin(), babies[TYPE(type)].end());
    }
    // everyone dies, babies discarded
    for (unsigned int b : babies[TYPE(type)])
    {
        lut.at(b).owner = DUMPSTER;
        dumpster.insert(b);
    }

    babies[TYPE(type)].clear();
    return 19;
}