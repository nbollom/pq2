//
// Created by nbollom on 1/06/16.
//

#include "itemofs.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> item_ofs = {
            "Foreboding",
            "Foreshadowing",
            "Nervousness",
            "Happiness",
            "Torpor",
            "Danger",
            "Craft",
            "Silence",
            "Invisibility",
            "Rapidity",
            "Pleasure",
            "Practicality",
            "Hurting",
            "Joy",
            "Petulance",
            "Intrusion",
            "Chaos",
            "Suffering",
            "Extroversion",
            "Frenzy",
            "Solitude",
            "Punctuality",
            "Efficiency",
            "Comfort",
            "Patience",
            "Internment",
            "Incarceration",
            "Misapprehension",
            "Loyalty",
            "Envy",
            "Acrimony",
            "Worry",
            "Fear",
            "Awe",
            "Guile",
            "Prurience",
            "Fortune",
            "Perspicacity",
            "Domination",
            "Submission",
            "Fealty",
            "Hunger",
            "Despair",
            "Cruelty",
            "Grob",
            "Dignard",
            "Ra",
            "the Bone",
            "Diamonique",
            "Electrum",
            "Hydragyrum"
    };

    static uniform_int_distribution<unsigned long> distribution(0, item_ofs.size() - 1);

    string get_random_item_of(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return item_ofs[value];
    }

}
