//
// Created by nbollom on 12/11/18.
//

#pragma once

#include <string>
#include <memory>
#include <random>

[[nodiscard]] std::string GenerateRandomName(const std::shared_ptr<std::mt19937_64>& engine);
