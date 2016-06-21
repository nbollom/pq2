//
// Created by nbollom on 1/06/16.
//

#include "shields.h"
#include <vector>

using namespace std;

namespace data {

    static const vector<Item> shields = {
            {"Parasol",         0},
            {"Pie Plate",       1},
            {"Garbage Can Lid", 2},
            {"Buckler",         3},
            {"Plexiglass",      4},
            {"Fender",          4},
            {"Round Shield",    5},
            {"Carapace",        5},
            {"Scutum",          6},
            {"Propugner",       6},
            {"Kite Shield",     7},
            {"Pavise",          8},
            {"Tower Shield",    9},
            {"Baroque Shield",  11},
            {"Aegis",           12},
            {"Magnetic Field",  18}
    };

    static uniform_int_distribution<unsigned long> distribution(0, shields.size() - 1);

    const Item get_random_shield(mt19937_64 *engine) {
        unsigned long value = distribution(*engine);
        return shields[value];
    }

}
