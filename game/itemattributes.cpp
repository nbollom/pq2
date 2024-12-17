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

    static uniform_int_distribution<unsigned long> distribution(0, item_attributes.size() - 1);

    string get_random_item_attribute(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return item_attributes[value];
    }

}
