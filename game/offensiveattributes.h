//
// Created by nbollom on 25/05/16.
//

#ifndef PQ2_OFFENSIVEATTRIBUTES_H
#define PQ2_OFFENSIVEATTRIBUTES_H

#include "types.h"
#include <random>

namespace data {

    const Attribute get_random_good_offensive_attribute(std::random_device *engine);

    const Attribute get_random_bad_offensive_attribute(std::random_device *engine);

}

#endif //PQ2_OFFENSIVEATTRIBUTES_H
