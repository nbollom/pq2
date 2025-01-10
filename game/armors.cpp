//
// Created by nbollom on 1/06/16.
//

#include "armors.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<Item> armors = {
            {"Lace",         1},
            {"Macrame",      2},
            {"Burlap",       3},
            {"Canvas",       4},
            {"Flannel",      5},
            {"Chamois",      6},
            {"Pleathers",    7},
            {"Leathers",     8},
            {"Bearskin",     9},
            {"Ringmail",     10},
            {"Scale Mail",   12},
            {"Chainmail",    14},
            {"Splint Mail",  15},
            {"Platemail",    16},
            {"ABS",          17},
            {"Kevlar",       18},
            {"Titanium",     19},
            {"Mithril Mail", 20},
            {"Diamond Mail", 25},
            {"Plasma",       30}
    };

    static uniform_int_distribution<unsigned long> distribution(0, armors.size() - 1);

    Item get_random_armor(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return armors[value];
    }

}
