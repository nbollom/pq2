//
// Created by nbollom on 2/06/16.
//

#include "classes.hpp"
#include <vector>

using namespace std;

namespace data {

    static const vector<Class> classes = {
            {"Ur-Paladin",       {"WIS", "CON"}},
            {"Voodoo Princess",  {"INT", "CHA"}},
            {"Robot Monk",       {"STR"}},
            {"Mu-Fu Monk",       {"DEX"}},
            {"Mage Illusioner",  {"INT", "MP Max"}},
            {"Shiv-Knight",      {"DEX"}},
            {"Inner Mason",      {"CON"}},
            {"Fighter/Organist", {"CHA", "STR"}},
            {"Puma Burgular",    {"DEX"}},
            {"Runeloremaster",   {"WIS"}},
            {"Hunter Strangler", {"DEX", "INT"}},
            {"Battle-Felon",     {"STR"}},
            {"Tickle-Mimic",     {"WIS", "INT"}},
            {"Slow Poisoner",    {"CON"}},
            {"Bastard Lunatic",  {"CON"}},
            {"Jungle Clown",     {"DEX", "CHA"}},
            {"Birdrider",        {"WIS"}},
            {"Vermineer",        {"INT"}}
    };

    static uniform_int_distribution<unsigned long> distribution(0, classes.size() - 1);

    Class get_random_class(const std::shared_ptr<std::mt19937_64>& engine) {
        const unsigned long value = distribution(*engine);
        return classes[value];
    }

    vector<Class> get_class_list() {
        return classes;
    }

}
