//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_SPELLS_H
#define PQ2_SPELLS_H

#include <string>
#include <random>

namespace data {

    const std::string get_random_spell(std::mt19937_64 *engine);

}

#endif //PQ2_SPELLS_H
