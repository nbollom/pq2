//
// Created by nbollom on 26/05/16.
//

#ifndef PQ2_DEFENSIVEATTRIBUTES_H
#define PQ2_DEFENSIVEATTRIBUTES_H

#include "types.h"
#include <random>
#include <memory>

namespace data {

    Attribute get_random_good_defensive_attribute(const std::shared_ptr<std::mt19937_64>& engine);

    Attribute get_random_bad_defensive_attribute(const std::shared_ptr<std::mt19937_64>& engine);

}

#endif //PQ2_DEFENSIVEATTRIBUTES_H
