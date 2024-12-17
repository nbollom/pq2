//
// Created by nbollom on 16/10/18.
//

#ifndef PQ2_MONSTERMODS_H
#define PQ2_MONSTERMODS_H

#include <string>
#include <random>
#include <memory>

namespace data {

    std::string get_random_monster_mod(const std::shared_ptr<std::mt19937_64>& engine);

}

#endif //PQ2_MONSTERMODS_H
