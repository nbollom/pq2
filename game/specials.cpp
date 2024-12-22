//
// Created by nbollom on 1/06/16.
//

#include "specials.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> specials = {
            "Diadem",
            "Festoon",
            "Gemstone",
            "Phial",
            "Tiara",
            "Scabbard",
            "Arrow",
            "Lens",
            "Lamp",
            "Hymnal",
            "Fleece",
            "Laurel",
            "Brooch",
            "Gimlet",
            "Cobble",
            "Albatross",
            "Brazier",
            "Bandolier",
            "Tome",
            "Garnet",
            "Amethyst",
            "Candelabra",
            "Corset",
            "Sphere",
            "Sceptre",
            "Ankh",
            "Talisman",
            "Orb",
            "Gammel",
            "Ornament",
            "Brocade",
            "Galoon",
            "Bijou",
            "Spangle",
            "Gimcrack",
            "Hood",
            "Vulpeculum"
    };

    static uniform_int_distribution<unsigned long> distribution(0, specials.size() - 1);

    string get_random_special(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return specials[value];
    }

}
