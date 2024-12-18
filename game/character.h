//
// Created by nbollom on 3/06/16.
//

#ifndef PQ2_CHARACTER_H
#define PQ2_CHARACTER_H

#include <string>
#include <array>
#include <vector>
#include <deque>

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

    uint64_t MAX_HP;
    uint64_t MAX_MP;

    uint64_t Gold;

    std::vector<data::Stack> Spells;
    std::array<std::string, 11> Equipment;
    std::vector<data::Stack> Inventory;
    std::vector<std::string> Plot;
    std::vector<data::Quest> Quests;

    std::deque<data::QueueItem> Queue;

    data::CurrentActionType CurrentAction;
    std::string CurrentActionLabel;
    data::Monster CurrentMonster;
    uint64_t CurrentProgress;
    uint64_t MaxProgress;
    uint64_t CurrentPlotProgress;
    uint64_t CurrentQuestProgress;
    uint64_t MaxQuestProgress;

};

#endif //PQ2_CHARACTER_H
