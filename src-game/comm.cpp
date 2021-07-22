/* This file includes the functions required for the server to communicate with the client.
 */

#include "server.hpp"

/* COMMUNICATION PROTOCAL (CLIENT->SERVER)
 * The first byte (0) shall signify the action to be taken
 * the next byte (1) shall signify a type, if it exists
 * the next byte (2) shall signify a direction, if it exists and only required for direction RIGHT
 * the next byte (3) is the player ID, given to each player
 * the next four bytes (4) shall signify the primary target
 * the next eight bytes (8,12) shall signify two secondary targets
 */
unsigned char Game::_play(unsigned char input[16])
{
    if (!ready)
    {
        std::cout << "you cannot play until all players are connected\n";
        return 0;
    }

    if (input[3] != pwds[CUR_PLAYER_ZERO_INDEX])
    {
        std::cout << "the password is incorrect\n";
        return 0;
    }

    if (int_turn > 20 and input[0] != PROVOKE)
    {
        std::cout << "you must provoke after drawing a \"WILD PROVOKE\"\n";
        return 0;
    }

    // interpret the three potential cards
    unsigned int target = *(unsigned int*)(input+4);
    unsigned int h1 = *(unsigned int*)(input+8);
    unsigned int h2 = *(unsigned int*)(input+12);
    unsigned char tmp;

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
        if (lut.at(target).owner != CUR_PLAYER)
        {
            std::cout << "you cannot play a card that you don't own\n";
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
            return play_head(h1, target);
        default: // the default case is playing as body part
            if (lut.find(h1)==lut.end())
            {
                std::cout << "the body attachment does not exist.\n";
                return 0;
            }
            if (lut.at(h1).type != BEAR and lut.at(h1).type != SEA and lut.at(h1).type != LAND and lut.at(h1).type != SKY)
            {
                std::cout << "the head the body tried to attach to is not a valid head card\n";
                return 0;
            }
            return play_part(target, h1, input[2]==RIGHT ? RIGHT : LEFT);
        }
    case PROVOKE:
        tmp = provoke(input[1]);
        return int_turn > 20 ? 19 : tmp;
    case DUMPSTER_DIVE:
        if (lut.find(target)==lut.end())
        {
            std::cout << "the primary target " << target << " is not a valid card in the game\n";
            return 0;
        }
        return dumpster_dive(target);
    default:
        return 0;
    }
}

int Game::play(unsigned char input[16])
{
    unsigned char p_turn = (NUM_PLAYERS==2) ? 4 : ((NUM_PLAYERS==3) ? 3 : 2);
    unsigned char output = _play(input);
    switch (output)
    {
    case 255:
        int_turn -= 18;
        return (int)(int_turn + ((unsigned int)turn << 8));
    case 0:
        return -500;
    default:
        int_turn += output;
        // find how many turns a player has
        for (Monster m : board[CUR_PLAYER_ZERO_INDEX])
        {
            if (m.ltool != NID)
                p_turn++;
            if (m.rtool != NID)
                p_turn++;
        }

        if (int_turn >= p_turn and int_turn < 20)
        {
            turn++;
            int_turn = 0;
        }
        return (int)(int_turn + ((unsigned int)turn << 8));
    }
}

Card& Game::query (unsigned int id)
{
    if (lut.find(id) != lut.end())
        return lut.at(id);
    std::cout << "your card at " << id << " is not in the game\n";
    throw "";
}

std::vector<std::vector<unsigned int>> Game::fetch_public()
{
    std::vector<std::vector<unsigned int>> monsters_list;
    for (int py = 0; py < NUM_PLAYERS; ++py)
    {
        for (Monster m : board[py])
        {
            std::vector<unsigned int> monster_vec;
            unsigned int* mp = (unsigned int*)&m;
            monster_vec.push_back(*mp==NID ? 0 : *mp); // add the head first always
            for (int i = 1; i < 9; ++i)
                if (mp[i] != NID)
                    monster_vec.push_back(mp[i]);
            monsters_list.push_back(monster_vec);
        }
    }
    return monsters_list;
}

std::vector<unsigned int> Game::fetch_private(char player)
{
    std::vector<unsigned int> private_cards;
    for (auto it = lut.begin(); it != lut.end(); ++it)
        if (it->second.owner == player)
            private_cards.push_back(it->first);
    return private_cards;
}

int Game::connect()
{
    unsigned char pass = 0;
    while (!pass)
        pass = rand();

    unsigned char order[5];
    for (int py = 0; py < NUM_PLAYERS; ++py)
        order[py] = py;
    std::random_shuffle(order, order+NUM_PLAYERS);

    for (int _i = 0; _i < NUM_PLAYERS; ++_i)
    {
        if (!pwds[order[_i]])
        {
            pwds[order[_i]] = pass;
            for (int k = 0; k < NUM_PLAYERS; ++k)
                if (!pwds[k])
                    return pass + (order[_i] << 8);
            ready = true;
            return pass + (order[_i] << 8);
        }
    }
    return 0;
}
