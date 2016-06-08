//
// Created by nbollom on 1/06/16.
//

#ifndef PQ2_SHIELDS_H
#define PQ2_SHIELDS_H

#include <string>
#include <random>
#include "types.h"

namespace data {

    const Item get_random_shield(std::mt19937_64 *engine);

}

#endif //PQ2_SHIELDS_H
