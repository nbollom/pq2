//
// Created by nbollom on 1/06/16.
//

#ifndef PQ2_ARMORS_H
#define PQ2_ARMORS_H

#include <string>
#include <random>
#include <memory>
#include "types.h"

namespace data {

    const Item get_random_armor(std::shared_ptr<std::mt19937_64> engine);

}

#endif //PQ2_ARMORS_H
