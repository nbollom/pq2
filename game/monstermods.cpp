//
// Created by nbollom on 16/10/18.
//

#include "monstermods.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> monster_mods = {
            "-4 fœtal %s",
            "-4 dying %s",
            "-3 crippled %s",
            "-3 baby %s",
            "-2 adolescent %s",
            "-2 very sick %s",
            "-1 lesser %s",
            "-1 undernourished %s",
            "+1 greater %s",
            "+1 %s Elder",
            "+2 war %s",
            "+2 Battle-%s",
            "+3 Were-%s",
            "+3 undead %s",
            "+4 giant %s",
            "+4 %s Rex"
    };

    static uniform_int_distribution<unsigned long> distribution(0, monster_mods.size() - 1);

    string get_random_monster_mod(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return monster_mods[value];
    }

}
