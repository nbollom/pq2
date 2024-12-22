//
// Created by nbollom on 30/05/16.
//

#pragma once

#include <string>
#include <list>
#include <memory>
#include "commandlineoptions.hpp"

using namespace std;

class CommandLineProcessor {

private:
    const string name;
    const string description;
    const string version;
    list<shared_ptr<Option>> options;
    list<shared_ptr<ValueOption>> values;

    shared_ptr<Option> GetOptionByShortName(char shortName);
    shared_ptr<Option> GetOptionByLongName(const string& longName);

public:
    CommandLineProcessor(string program_name, string program_description, string program_version);
    void AddOption(char shortName, const string& longName, const string& description, bool hasValue, const string& valueDescription = "", const string& defaultValue = "");
    void AddValueOnlyOption(const string& name, const string& description, const string& defaultValue = "");
    [[nodiscard]] bool Parse(int argc, const char * const *argv);
    [[nodiscard]] bool IsSet(char shortName);
    [[nodiscard]] bool IsSet(const string &longName);
    [[nodiscard]] string GetOptionValue(char shortName);
    [[nodiscard]] string GetOptionValue(const string &longName);
    [[nodiscard]] string GetValueOnlyOptionValue(const string& name) const;
};
