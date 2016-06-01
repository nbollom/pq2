//
// Created by nbollom on 30/05/16.
//

#include "commandline.h"

typedef list<shared_ptr<Option>>::iterator OI;
typedef list<shared_ptr<ValueOption>>::iterator VOI;

CommandLineProcessor::CommandLineProcessor(const string name, const string description, const string version)
        : _name(name), _description(description), _version(version) {
    _options.push_back(make_shared<Option>('h', "help", "Shows this help screen", false, "", false, ""));
    _options.push_back(make_shared<Option>('v', "version", "prints the version", false, "", false, ""));
}

void CommandLineProcessor::AddOption(const char shortName, const string longName, const string description, const bool hasValue, const string valueDescription, string defaultValue) {
    shared_ptr<Option> option = make_shared<Option>(shortName, longName, description, hasValue, valueDescription, false, defaultValue);
    for (OI it = _options.begin(); it != _options.end(); ++it) {
        shared_ptr<Option> existingOption = *it;
        if (option->shortName == existingOption->shortName || option->longName == existingOption->longName) {
            throw new OptionExistsException(option, existingOption);
        }
    }
    _options.push_back(option);
}

void CommandLineProcessor::AddValueOnlyOption(const string name, const string description, string defaultValue) {
    shared_ptr<ValueOption> option = make_shared<ValueOption>(name, description, defaultValue);
    for (VOI it = _values.begin(); it != _values.end(); ++it) {
        shared_ptr<ValueOption> existingOption = *it;
        if (option->name == existingOption->name) {
            throw new ValueOptionExistsException(option, existingOption);
        }
    }
    _values.push_back(option);
}

void CommandLineProcessor::Parse(int argc, const char *const *argv) {
    string executable = argv[0];
    bool parsingValueOptions = false;
    VOI currentValueOption = _values.begin();
    for (int i = 1; i < argc; ++i) {
        string val = argv[i];
        if (!parsingValueOptions && val.front() == '-') {
            if (val.length() < 2) {
                throw new InvalidArgumentException(val);
            }
            shared_ptr<Option> option;
            string name;
            if (val[1] == '-') { //long option
                name = val.substr(2);
                option = GetOptionByLongName(name);
            }
            else { // short option
                name = val.substr(1);
                option = GetOptionByShortName(name[0]);
            }
            if (option == nullptr) {
                throw new UnknownArgumentException(name);
            }
            option->found = true;
            if (option->hasValue) {
                if (++i < argc) { // not the end of the parameters yet
                    string optionValue = argv[i];
                    if (optionValue.front() == '-') {
                        throw new MissingValueException(name, option);
                    }
                    else {
                        option->value = optionValue;
                    }
                }
                else {
                    throw new MissingValueException(name, option);
                }
            }
        }
        else {
            parsingValueOptions = true;
            if (currentValueOption == _values.end()) {
                throw new UnknownArgumentException(val);
            }
            (*currentValueOption)->value = val;
            currentValueOption++;
        }
    }
}

bool CommandLineProcessor::IsSet(char shortName) {
    auto option = GetOptionByShortName(shortName);
    if (option == nullptr) {
        return false;
    }
    return option->found;
}

bool CommandLineProcessor::IsSet(string longName) {
    auto option = GetOptionByLongName(longName);
    if (option == nullptr) {
        return false;
    }
    return option->found;
}

string CommandLineProcessor::GetOptionValue(char shortName) {
    auto option = GetOptionByShortName(shortName);
    if (option == nullptr) {
        return "";
    }
    return option->value;
}

string CommandLineProcessor::GetOptionValue(string longName) {
    auto option = GetOptionByLongName(longName);
    if (option == nullptr) {
        return "";
    }
    return option->value;
}

string CommandLineProcessor::GetValueOnlyOptionValue(string name) {
    shared_ptr<ValueOption> option = nullptr;
    for (VOI it = _values.begin(); it != _values.end(); ++it) {
        if ((*it)->name == name) {
            option = *it;
            break;
        }
    }
    if (option == nullptr) {
        return "";
    }
    return option->value;
}

shared_ptr<Option> CommandLineProcessor::GetOptionByShortName(char shortName) {
    for (OI it = _options.begin(); it != _options.end(); ++it) {
        if ((*it)->shortName == shortName) {
            return *it;
        }
    }
    return nullptr;
}

shared_ptr<Option> CommandLineProcessor::GetOptionByLongName(string longName) {
    for (OI it = _options.begin(); it != _options.end(); ++it) {
        if ((*it)->longName == longName) {
            return *it;
        }
    }
    return nullptr;
}
