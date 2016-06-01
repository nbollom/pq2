//
// Created by nbollom on 1/06/16.
//

#include "itemattributes.h"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> item_attributes = {
            "Golden",
            "Gilded",
            "Spectral",
            "Astral",
            "Garlanded",
            "Precious",
            "Crafted",
            "Dual",
            "Filigreed",
            "Cruciate",
            "Arcane",
            "Blessed",
            "Reverential",
            "Lucky",
            "Enchanted",
            "Gleaming",
            "Grandiose",
            "Sacred",
            "Legendary",
            "Mythic",
            "Crystalline",
            "Austere",
            "Ostentatious",
            "One True",
            "Proverbial",
            "Fearsome",
            "Deadly",
            "Benevolent",
            "Unearthly",
            "Magnificent",
            "Iron",
            "Ormolu",
            "Puissant"
    };

    const string get_random_item_attribute(random_device *engine) {
        static uniform_int_distribution<unsigned long> distribution(0, item_attributes.size() - 1);
        unsigned long value = distribution(*engine);
        return item_attributes[value];
    }

}
