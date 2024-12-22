//
// Created by nbollom on 30/05/16.
//

#pragma once

#include <string>

using namespace std;

class Option {

public:
    const char shortName;
    const string longName;
    const string description;
    const bool hasValue;
    const string valueDescription;
    bool found;
    string value;

    Option(char shortName, string  longName, string  description, bool hasValue, string  valueDescription, bool found, string value);
};

class ValueOption {

public:
    const string name;
    const string description;
    string value;

    ValueOption(string name, string  description, string value);
};
