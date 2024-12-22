//
// Created by nbollom on 1/06/16.
//

#pragma once

#include <string>
#include <random>
#include <memory>
#include "types.hpp"

namespace data {

    [[nodiscard]] Monster get_random_monster(const std::shared_ptr<std::mt19937_64>& engine);

}
