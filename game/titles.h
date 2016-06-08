//
// Created by nbollom on 2/06/16.
//

#ifndef PQ2_TITLES_H
#define PQ2_TITLES_H

#include <string>
#include <random>

namespace data {

    const std::string get_random_title(std::mt19937_64 *engine);

    const std::string get_random_impressive_title(std::mt19937_64 *engine);

}

#endif //PQ2_TITLES_H
