//
// Created by nbollom on 2/06/16.
//

#ifndef PQ2_RACES_H
#define PQ2_RACES_H

#include <random>
#include <memory>
#include "types.h"

namespace data {

    Race get_random_race(const std::shared_ptr<std::mt19937_64>& engine);

    std::vector<Race> get_race_list();

}

#endif //PQ2_RACES_H
