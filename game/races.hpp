//
// Created by nbollom on 2/06/16.
//

#pragma once

#include <random>
#include <memory>
#include "types.hpp"

namespace data {

    [[nodiscard]] Race get_random_race(const std::shared_ptr<std::mt19937_64>& engine);

    [[nodiscard]] std::vector<Race> get_race_list();

}
