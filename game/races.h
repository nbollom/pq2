//
// Created by nbollom on 2/06/16.
//

#ifndef PQ2_RACES_H
#define PQ2_RACES_H

#include <string>
#include <random>
#include "types.h"

namespace data {

    const Race get_random_race(std::random_device *engine);

//const std::list<Race> get_race_list();
    const std::vector<Race> get_race_list();

}

#endif //PQ2_RACES_H
