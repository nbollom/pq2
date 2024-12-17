//
// Created by nbollom on 31/05/16.
//

#include "commandlineoptions.h"

#include <utility>

Option::Option(const char shortName, string longName, string description, const bool hasValue, string valueDescription, const bool found, string value) :
        shortName(shortName), longName(std::move(longName)), description(std::move(description)), hasValue(hasValue), valueDescription(std::move(valueDescription)), found(found), value(std::move(value)) {
}

ValueOption::ValueOption(string name, string description, string value) : name(std::move(name)), description(std::move(description)), value(std::move(value)) {
}
