//
// Created by nbollom on 12/11/18.
//

#ifndef PQ2_NAMEGENERATOR_H
#define PQ2_NAMEGENERATOR_H

#include <string>
#include <memory>
#include <random>

std::string GenerateRandomName(const std::shared_ptr<std::mt19937_64>& engine);

#endif //PQ2_NAMEGENERATOR_H
