//
// Created by nbollom on 2/06/16.
//

#pragma once

#include <random>
#include <memory>
#include "types.hpp"

namespace data {

    [[nodiscard]] Class get_random_class(const std::shared_ptr<std::mt19937_64>& engine);

    [[nodiscard]] std::vector<Class> get_class_list();

}
