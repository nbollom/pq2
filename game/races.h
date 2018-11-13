//
// Created by nbollom on 2/06/16.
//

#ifndef PQ2_RACES_H
#define PQ2_RACES_H

#include <string>
#include <random>
#include <memory>
#include "types.h"

namespace data {

    const Race get_random_race(std::shared_ptr<std::mt19937_64> engine);

    const std::vector<Race> get_race_list();

}

#endif //PQ2_RACES_H
