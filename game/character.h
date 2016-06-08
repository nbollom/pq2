//
// Created by nbollom on 3/06/16.
//

#ifndef PQ2_CHARACTER_H
#define PQ2_CHARACTER_H

#include <string>
#include <list>

#include "types.h"

class Character {

public:
    std::string Name;

    Race CharacterRace;
    Class CharacterClass;

    uint64_t STR;
    uint64_t CON;
    uint64_t DEX;
    uint64_t INT;
    uint64_t WIS;
    uint64_t CHA;

    uint64_t Gold;

    std::list<Stack> Spells;
    std::list<Stack> Inventory;

};

#endif //PQ2_CHARACTER_H
