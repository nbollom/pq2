//
// Created by nbollom on 3/06/16.
//

#ifndef PQ2_CHARACTER_H
#define PQ2_CHARACTER_H

#include <string>
#include <list>
#include <array>

#include "types.h"

struct Character {

    std::string Name;

    data::Race CharacterRace;
    data::Class CharacterClass;

    uint64_t Level;
    uint64_t Experience;

    uint64_t STR;
    uint64_t CON;
    uint64_t DEX;
    uint64_t INT;
    uint64_t WIS;
    uint64_t CHA;

    uint64_t MAXHP;
    uint64_t MAXMP;

    uint64_t Gold;

    std::list<data::Stack> Spells;
    std::array<data::Item, 11> Equipment;
    std::list<data::Stack> Inventory;
    std::list<std::string> Plot;
    std::list<std::string> Quests;

    std::string CurrentAction;
    uint64_t CurrentProgress;

};

#endif //PQ2_CHARACTER_H
