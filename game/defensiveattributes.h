//
// Created by nbollom on 26/05/16.
//

#ifndef PQ2_DEFENSIVEATTRIBUTES_H
#define PQ2_DEFENSIVEATTRIBUTES_H

#include "types.h"
#include <random>

namespace data {

    const Attribute get_random_good_defensive_attribute(std::random_device *engine);

    const Attribute get_random_bad_defensive_attribute(std::random_device *engine);

}

#endif //PQ2_DEFENSIVEATTRIBUTES_H
