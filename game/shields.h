//
// Created by nbollom on 1/06/16.
//

#ifndef PQ2_SHIELDS_H
#define PQ2_SHIELDS_H

#include <random>
#include <memory>
#include "types.h"

namespace data {

    Item get_random_shield(const std::shared_ptr<std::mt19937_64>& engine);

}

#endif //PQ2_SHIELDS_H
