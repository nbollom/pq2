//
// Created by nbollom on 1/06/16.
//

#include "weapons.h"
#include <vector>

using namespace std;

namespace data {

    static const vector<Item> weapons = {
            {"Stick",         0},
            {"Broken Bottle", 1},
            {"Shiv",          1},
            {"Sprig",         1},
            {"Oxgoad",        1},
            {"Eelspear",      2},
            {"Bowie Knife",   2},
            {"Claw Hammer",   2},
            {"Handpeen",      2},
            {"Andiron",       3},
            {"Hatchet",       3},
            {"Tomahawk",      3},
            {"Hackbarm",      3},
            {"Crowbar",       4},
            {"Mace",          4},
            {"Battleadze",    4},
            {"Leafmace",      5},
            {"Shortsword",    5},
            {"Longiron",      5},
            {"Poachard",      5},
            {"Baselard",      5},
            {"Whinyard",      6},
            {"Blunderbuss",   6},
            {"Longsword",     6},
            {"Crankbow",      6},
            {"Blibo",         7},
            {"Broadsword",    7},
            {"Kreen",         7},
            {"Morning Star",  8},
            {"Pole-adze",     8},
            {"Spontoon",      8},
            {"Bastard Sword", 9},
            {"Peen-arm",      9},
            {"Culverin",      10},
            {"Lance",         10},
            {"Halberd",       11},
            {"Poleax",        12},
            {"Bandyclef",     15}
    };

    static uniform_int_distribution<unsigned long> distribution(0, weapons.size() - 1);

    Item get_random_weapon(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return weapons[value];
    }

}
