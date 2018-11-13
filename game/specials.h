//
// Created by nbollom on 1/06/16.
//

#ifndef PQ2_SPECIALS_H
#define PQ2_SPECIALS_H

#include <string>
#include <random>
#include <memory>

namespace data {

    const std::string get_random_special(std::shared_ptr<std::mt19937_64> engine);

}

#endif //PQ2_SPECIALS_H
