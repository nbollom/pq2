//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_OFFENSIVEATTRIBUTES_H
#define PQ2_OFFENSIVEATTRIBUTES_H

#include "types.h"
#include <random>
#include <memory>

namespace data {

    Attribute get_random_good_offensive_attribute(const std::shared_ptr<std::mt19937_64>& engine);

    Attribute get_random_bad_offensive_attribute(const std::shared_ptr<std::mt19937_64>& engine);

}

#endif //PQ2_OFFENSIVEATTRIBUTES_H
