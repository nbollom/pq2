//
// Created by nbollom on 1/06/16.
//

#pragma once

#include <random>
#include <memory>
#include "types.hpp"

namespace data {

    [[nodiscard]] Item get_random_shield(const std::shared_ptr<std::mt19937_64>& engine);

}
