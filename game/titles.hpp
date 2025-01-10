//
// Created by nbollom on 2/06/16.
//

#pragma once

#include <string>
#include <random>
#include <memory>

namespace data {

    [[nodiscard]] std::string get_random_title(const std::shared_ptr<std::mt19937_64>& engine, bool low = false);

    [[nodiscard]] std::string get_random_impressive_title(const std::shared_ptr<std::mt19937_64>& engine);

}
