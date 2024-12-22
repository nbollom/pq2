//
// Created by nbollom on 8/11/18.
//

#include <array>
#include "romannumerals.hpp"

std::array<std::pair<uint64_t, std::string>, 13> roman_numerals = {
        std::make_pair(1000, "M"),
        std::make_pair(900, "CM"),
        std::make_pair(500, "D"),
        std::make_pair(400, "CD"),
        std::make_pair(100, "C"),
        std::make_pair(90, "XC"),
        std::make_pair(50, "L"),
        std::make_pair(40, "XL"),
        std::make_pair(10, "X"),
        std::make_pair(9, "IX"),
        std::make_pair(5, "V"),
        std::make_pair(4, "IV"),
        std::make_pair(1, "I")
};

std::string GetRomanNumerals(uint64_t value) {
    std::string numerals;
    for(const auto& numeral: roman_numerals) {
        while (value >= numeral.first) {
            numerals += numeral.second;
            value -= numeral.first;
        }
    }
    return numerals;
}


