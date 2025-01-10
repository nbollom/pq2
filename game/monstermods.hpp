//
// Created by nbollom on 16/10/18.
//

#pragma once

#include <string>
#include <random>
#include <memory>

namespace data {

    [[nodiscard]] std::string get_random_monster_mod(const std::shared_ptr<std::mt19937_64>& engine);

}
