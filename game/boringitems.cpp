//
// Created by nbollom on 1/06/16.
//

#include "boringitems.h"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> boring_items = {
            "nail",
            "lunchpail",
            "sock",
            "I.O.U.",
            "cookie",
            "pint",
            "toothpick",
            "writ",
            "newspaper",
            "letter",
            "plank",
            "hat",
            "egg",
            "coin",
            "needle",
            "bucket",
            "ladder",
            "chicken",
            "twig",
            "dirtclod",
            "counterpane",
            "vest",
            "teratoma",
            "bunny",
            "rock",
            "pole",
            "carrot",
            "canoe",
            "inkwell",
            "hoe",
            "bandage",
            "trowel",
            "towel",
            "planter box",
            "anvil",
            "axle",
            "tuppence",
            "casket",
            "nosegay",
            "trinket",
            "credenza",
            "writ"
    };

    static uniform_int_distribution<unsigned long> distribution(0, boring_items.size() - 1);

    const string get_random_boring_item(std::shared_ptr<std::mt19937_64> engine) {
        unsigned long value = distribution(*engine);
        return boring_items[value];
    }

}
