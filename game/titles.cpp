//
// Created by nbollom on 2/06/16.
//

#include "titles.h"
#include <vector>

using namespace std;

namespace data {

    static const vector<string> titles = {
            "Mr.",
            "Mrs.",
            "Sir",
            "Sgt.",
            "Ms.",
            "Captain",
            "Chief",
            "Admiral",
            "Saint"
    };

    const string get_random_title(random_device *engine) {
        static uniform_int_distribution<unsigned long> distribution(0, titles.size() - 1);
        unsigned long value = distribution(*engine);
        return titles[value];
    }

    static const vector<string> impressive_titles = {
            "King",
            "Queen",
            "Lord",
            "Lady",
            "Viceroy",
            "Mayor",
            "Prince",
            "Princess",
            "Chief",
            "Boss",
            "Archbishop"
    };

    const string get_random_impressive_title(random_device *engine) {
        static uniform_int_distribution<unsigned long> distribution(0, impressive_titles.size() - 1);
        unsigned long value = distribution(*engine);
        return impressive_titles[value];
    }

}
