//
// Created by nbollom on 2/01/25.
//

#include "plural.hpp"

#define NPOS std::string::npos

std::string Plural(std::string s) {
    const size_t size = s.size();
    if (size > 1 && s.substr(size - 1) == "y") {
        return s.replace(size - 1, NPOS, "ies");
    }
    if (size > 2 && s.substr(size - 2) == "us") {
        return s.replace(size - 2, NPOS, "i");
    }
    if ((size > 2 && s.substr(size - 2) == "ch") || (size > 1 && (s.substr(size - 1) == "x" || s.substr(size - 1) == "s"))) {
        return s + "es";
    }
    if (size > 1 && s.substr(size - 1) == "f") {
        return s.replace(size - 1, NPOS, "ves");
    }
    if (size > 3 && (s.substr(size - 3) == "man" || s.substr(size - 3) == "Man")) {
        return s.replace(size - 2, NPOS, "en");
    }
    return s + "s";
}