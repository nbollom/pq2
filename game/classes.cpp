//
// Created by nbollom on 2/06/16.
//

#include "classes.h"
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

    const Class get_random_class(mt19937_64 *engine) {
        static uniform_int_distribution<unsigned long> distribution(0, classes.size() - 1);
        unsigned long value = distribution(*engine);
        return classes[value];
    }

//const list<Class> get_class_list() {
//    list<Class> classList(classes.begin(), classes.end());
//    return classList;
//}

    const vector<Class> get_class_list() {
        return classes;
    }

}
