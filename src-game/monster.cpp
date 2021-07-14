#include "server.hpp"

#define EXIST !=NID
#define NEXIST ==NID

bool Monster::add_part(const Card& card, const unsigned char dir)
{
    switch(card.type)
    {
        // adding a new head
        case LAND: case SEA: case SKY: case BEAR:
            if (head EXIST)
                return false;
            head = card.id;
            type = card.type;
            return true;

        // adding new body
        case C_TORSO: case TORSO: case M_BODY: case AL_BODY:
            if (head NEXIST or body EXIST)
                return false;
            body = card.id;
            body_type = card.type;
            return true;

        // adding new legs
        case LEGS:
            if (legs EXIST or (body_type!=TORSO and body_type!=C_TORSO))
                return false;
            legs = card.id;
            return true;
        
        // adding new arms
        case ARM:
            if (body_type!=C_TORSO and body_type!=AL_BODY)
                return false;
            if (dir==LEFT and larm NEXIST)
            {
                larm = card.id;
                return true;
            }
            if (dir==RIGHT and rarm NEXIST)
            {
                rarm = card.id;
                return true;
            }
        // adding new tool
        case TOOL:
            if (dir==LEFT and ltool NEXIST and (larm EXIST or body_type==TORSO or body_type==M_BODY))
            {
                ltool = card.id;
                return true;
            }
            if (dir==RIGHT and rtool NEXIST and (rarm EXIST or body_type==TORSO or body_type==M_BODY))
            {
                rtool = card.id;
                return true;
            }
            return false;
        case HAT:
            if (head NEXIST or hat EXIST)
                return false;
            hat = card.id;
            return true;
        case MASK:
            if (mask EXIST or head NEXIST)
                return false;
            mask = card.id;
            return true;
        default:
            return false;
    }
}

unsigned char Monster::strength() const
{
    if (head NEXIST)
        return 0;
    // head
    unsigned char strength = (type==BEAR) ? 3 : 2;
    // body
    if (body_type == TORSO or body_type == C_TORSO)
        strength += 1;
    if (body_type == AL_BODY or body_type == M_BODY)
        strength += 2;
    // legs
    if (legs EXIST)
        strength += 2;
    // arms
    if (larm EXIST)
        strength += 1;
    if (rarm EXIST)
        strength += 1;
    // tools
    if (ltool EXIST)
        strength -= 1;
    if (rtool EXIST)
        strength -= 1;
    // hat
    if (hat EXIST)
        strength *= 2;

    return strength;
}

void Monster::kill(std::unordered_map<unsigned int, Card>& lut, std::set<unsigned int>& dumpster) const
{
    // pointer hack
    unsigned int *m = (unsigned int *) this;
    for (int i = 0; i < 9; ++i)
    {
        if (m[i] EXIST)
        {
            lut.at(m[i]).owner = DUMPSTER;
            dumpster.insert(m[i]);
        }
    }
}
