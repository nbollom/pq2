//
// Created by nbollom on 19/12/24.
//

#pragma once

#include <string>

struct Character;

std::string serialise(const Character& character);
void deserialize(const std::string& value, Character &character);
