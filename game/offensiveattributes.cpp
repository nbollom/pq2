//
// Created by nbollom on 25/05/16.
//

#include "offensiveattributes.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<Attribute> good_offensive_attributes = {
            {"Polished",  1},
            {"Serrated",  1},
            {"Heavy",     1},
            {"Pronged",   2},
            {"Steely",    2},
            {"Vicious",   3},
            {"Venomed",   4},
            {"Stabbity",  4},
            {"Dancing",   5},
            {"Invisible", 6},
            {"Vorpal",    7}
    };

    static uniform_int_distribution<unsigned long> g_distribution(0, good_offensive_attributes.size() - 1);

    Attribute get_random_good_offensive_attribute(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = g_distribution(*engine);
        return good_offensive_attributes[value];
    }

    static const vector<Attribute> bad_offensive_attributes = {
            {"Dull",       -2},
            {"Tarnished",  -1},
            {"Rusty",      -3},
            {"Padded",     -5},
            {"Bent",       -4},
            {"Mini",       -4},
            {"Rubber",     -6},
            {"Nerf",       -7},
            {"Unbalanced", -2}
    };

    static uniform_int_distribution<unsigned long> b_distribution(0, bad_offensive_attributes.size() - 1);

    Attribute get_random_bad_offensive_attribute(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = b_distribution(*engine);
        return bad_offensive_attributes[value];
    }

}
