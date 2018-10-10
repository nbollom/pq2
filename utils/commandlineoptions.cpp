//
// Created by nbollom on 31/05/16.
//

#include "commandlineoptions.h"

Option::Option(const char shortName, const string longName, const string description, const bool hasValue, const string valueDescription, bool found, string value) :
        shortName(shortName), longName(longName), description(description), hasValue(hasValue), valueDescription(valueDescription), found(found), value(value) {
}

ValueOption::ValueOption(const string name, const string description, string value) : name(name), description(description), value(value) {
}
