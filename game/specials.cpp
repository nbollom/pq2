//
// Created by nbollom on 1/06/16.
//

#include "specials.h"
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

    const string get_random_special(mt19937_64 *engine) {
        static uniform_int_distribution<unsigned long> distribution(0, specials.size() - 1);
        unsigned long value = distribution(*engine);
        return specials[value];
    }

}
