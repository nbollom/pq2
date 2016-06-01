//
// Created by nbollom on 1/06/16.
//

#ifndef PQ2_ARMORS_H
#define PQ2_ARMORS_H

#include <string>
#include <random>
#include "types.h"

namespace data {

    const Item get_random_armor(std::random_device *engine);

}

#endif //PQ2_ARMORS_H
