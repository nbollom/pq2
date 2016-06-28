//
// Created by nbollom on 30/05/16.
//

#ifndef PQ2_COMMANDLINE_H
#define PQ2_COMMANDLINE_H

#include <string>
#include <list>
#include <memory>
#include "commandlineexeptions.h"
#include "commandlineoptions.h"

using namespace std;

class CommandLineProcessor {

private:
    const string name;
    const string description;
    const string version;
    list<shared_ptr<Option>> options;
    list<shared_ptr<ValueOption>> values;

    shared_ptr<Option> GetOptionByShortName(char shortName);
    shared_ptr<Option> GetOptionByLongName(string longName);

public:
    CommandLineProcessor(const string program_name, const string program_description, const string program_version);
    void AddOption(const char shortName, const string longName, const string description, const bool hasValue, const string valueDesc = "", string defaultValue = "");
    void AddValueOnlyOption(const string name, const string description, string defaultValue = "");
    void Parse(int argc, const char * const *argv);
    bool IsSet(char shortName);
    bool IsSet(string longName);
    string GetOptionValue(char shortName);
    string GetOptionValue(string longName);
    string GetValueOnlyOptionValue(string name);
};

#endif //PQ2_COMMANDLINE_H
