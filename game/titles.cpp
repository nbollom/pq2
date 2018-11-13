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

    static uniform_int_distribution<unsigned long> t_distribution(0, titles.size() - 1);

    const string get_random_title(std::shared_ptr<std::mt19937_64> engine) {
        unsigned long value = t_distribution(*engine);
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

    static uniform_int_distribution<unsigned long> it_distribution(0, impressive_titles.size() - 1);

    const string get_random_impressive_title(std::shared_ptr<std::mt19937_64> engine) {
        unsigned long value = it_distribution(*engine);
        return impressive_titles[value];
    }

}
