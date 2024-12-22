//
// Created by nbollom on 1/06/16.
//

#pragma once

#include <string>
#include <random>
#include <memory>

namespace data {

    [[nodiscard]] std::string get_random_item_of(const std::shared_ptr<std::mt19937_64>& engine);

}
