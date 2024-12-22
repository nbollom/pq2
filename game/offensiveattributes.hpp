//
// Created by nbollom on 25/05/16.
//

#pragma once

#include "types.hpp"
#include <random>
#include <memory>

namespace data {

    [[nodiscard]] Attribute get_random_good_offensive_attribute(const std::shared_ptr<std::mt19937_64>& engine);

    [[nodiscard]] Attribute get_random_bad_offensive_attribute(const std::shared_ptr<std::mt19937_64>& engine);

}
