//
// Created by nbollom on 26/05/16.
//

#include "defensiveattributes.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<Attribute> good_defensive_attributes = {
            {"Studded",    1},
            {"Banded",     2},
            {"Gilded",     2},
            {"Festooned",  3},
            {"Holy",       4},
            {"Cambric",    1},
            {"Fine",       4},
            {"Impressive", 5},
            {"Custom",     3}
    };

    static uniform_int_distribution<unsigned long> g_distribution(0, good_defensive_attributes.size() - 1);

    Attribute get_random_good_defensive_attribute(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = g_distribution(*engine);
        return good_defensive_attributes[value];
    }

    static const vector<Attribute> bad_defensive_attributes = {
            {"Holey",      -1},
            {"Patched",    -1},
            {"Threadbare", -2},
            {"Faded",      -1},
            {"Rusty",      -3},
            {"Motheaten",  -3},
            {"Mildewed",   -2},
            {"Torn",       -3},
            {"Dented",     -3},
            {"Cursed",     -5},
            {"Plastic",    -4},
            {"Cracked",    -4},
            {"Warped",     -3},
            {"Corroded",   -3}
    };

    static uniform_int_distribution<unsigned long> b_distribution(0, bad_defensive_attributes.size() - 1);

    Attribute get_random_bad_defensive_attribute(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = b_distribution(*engine);
        return bad_defensive_attributes[value];
    }

}
