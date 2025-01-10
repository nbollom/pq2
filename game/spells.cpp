//
// Created by nbollom on 25/05/16.
//

#include "spells.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> spells = {
            "Slime Finger",
            "Rabbit Punch",
            "Hastiness",
            "Good Move",
            "Sadness",
            "Seasick",
            "Gyp",
            "Shoelaces",
            "Innoculate",
            "Cone of Annoyance",
            "Magnetic Orb",
            "Invisible Hands",
            "Revolting Cloud",
            "Aqueous Humor",
            "Spectral Miasma",
            "Clever Fellow",
            "Lockjaw",
            "History Lesson",
            "Hydrophobia",
            "Big Sister",
            "Cone of Paste",
            "Mulligan",
            "Nestor's Bright Idea",
            "Holy Batpole",
            "Tumor (Benign)",
            "Braingate",
            "Nonplus",
            "Animate Nightstand",
            "Eye of the Troglodyte",
            "Curse Name",
            "Dropsy",
            "Vitreous Humor",
            "Roger's Grand Illusion",
            "Covet",
            "Astral Miasma",
            "Spectral Oyster",
            "Acrid Hands",
            "Angioplasty",
            "Grognor's Big Day Off",
            "Tumor (Malignant)",
            "Animate Tunic",
            "Ursine Armor",
            "Holy Roller",
            "Tonsilectomy",
            "Curse Family",
            "Infinite Confusion"
    };

    std::vector<std::string> get_spells() {
        return spells;
    }

}
