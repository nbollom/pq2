//
// Created by nbollom on 30/05/16.
//

#include "commandline.h"
#include <iostream>

typedef list<shared_ptr<Option>>::iterator OI;
typedef list<shared_ptr<ValueOption>>::iterator VOI;

inline unsigned long max(const unsigned long &a, const unsigned long &b) {
    if (a > b) {
        return a;
    }
    return b;
}

inline std::string pad(const unsigned long length) {
    return std::string(length, ' ');
}

CommandLineProcessor::CommandLineProcessor(const string program_name, const string program_description, const string program_version)
        : name(program_name), description(program_description), version(program_version) {
    options.push_back(make_shared<Option>('h', "help", "Shows this help screen", false, "", false, ""));
    options.push_back(make_shared<Option>('v', "version", "prints the version", false, "", false, ""));
}

void CommandLineProcessor::AddOption(const char shortName, const string longName, const string description, const bool hasValue, const string valueDescription, string defaultValue) {
    shared_ptr<Option> option = make_shared<Option>(shortName, longName, description, hasValue, valueDescription, false, defaultValue);
    for (OI it = options.begin(); it != options.end(); ++it) {
        shared_ptr<Option> existingOption = *it;
        if (option->shortName == existingOption->shortName || option->longName == existingOption->longName) {
            throw OptionExistsException(option, existingOption);
        }
    }
    options.push_back(option);
}

void CommandLineProcessor::AddValueOnlyOption(const string name, const string description, string defaultValue) {
    shared_ptr<ValueOption> option = make_shared<ValueOption>(name, description, defaultValue);
    for (VOI it = values.begin(); it != values.end(); ++it) {
        shared_ptr<ValueOption> existingOption = *it;
        if (option->name == existingOption->name) {
            throw ValueOptionExistsException(option, existingOption);
        }
    }
    values.push_back(option);
}

bool CommandLineProcessor::Parse(int argc, const char *const *argv) {
    string executable = argv[0];
    bool parsingValueOptions = false;
    VOI currentValueOption = values.begin();
    for (int i = 1; i < argc; ++i) {
        string val = argv[i];
        if (!parsingValueOptions && val.front() == '-') {
            if (val.length() < 2) {
                throw InvalidArgumentException(val);
            }
            shared_ptr<Option> option;
            string option_str;
            if (val[1] == '-') { //long option
                option_str = val.substr(2);
                option = GetOptionByLongName(option_str);
            }
            else { // short option
                option_str = val.substr(1);
                option = GetOptionByShortName(option_str[0]);
            }
            if (option == nullptr) {
                throw UnknownArgumentException(option_str);
            }
            option->found = true;
            if (option->shortName == 'h') {
                std::cout << name << "(" << version << ")" << std::endl;
                std::cout << description << std::endl;
                options.sort([](const shared_ptr<Option> a, const shared_ptr<Option> b){
                    return a->shortName < b->shortName;
                });
                std::string usage_str;
                std::string value_usage_str;
                unsigned long longest_name = 0;
                for (const auto &op : options) {
                    if (op->hasValue) {
                        value_usage_str += " -";
                        value_usage_str += op->shortName;
                        value_usage_str += " <";
                        value_usage_str += op->longName;
                        value_usage_str += ">";
                    }
                    else {
                        usage_str += op->shortName;
                    }
                    longest_name = max(longest_name, op->longName.length());
                }
                std::cout << "Usage: " << executable << " [-" << usage_str << value_usage_str << "]" << std::endl << std::endl;
                for (const auto &op : options) {
                    std::cout << "\t-" << op->shortName << "\t--" << op->longName << pad(longest_name - op->longName.length()) << "\t" << op->description << std::endl;
                    if (op->hasValue) {
                        std::cout << "\t\t" << pad(longest_name + 2) << "\t" << op->valueDescription;
                        if (op->value.length() > 0) {
                            std::cout << " (Default: " << op->value << ")" <<  std::endl;
                        }
                        else {
                            std::cout <<  std::endl;
                        }
                    }
                }
                std::cout << std::endl;
                return false;
            }
            if (option->shortName == 'v') {
                std::cout << name << std::endl;
                std::cout << "Version: " << version << std::endl;
                return false;
            }
            if (option->hasValue) {
                if (++i < argc) { // not the end of the parameters yet
                    string optionValue = argv[i];
                    if (optionValue.front() == '-') {
                        throw MissingValueException(option_str, option);
                    }
                    else {
                        option->value = optionValue;
                    }
                }
                else {
                    throw MissingValueException(option_str, option);
                }
            }
        }
        else {
            parsingValueOptions = true;
            if (currentValueOption == values.end()) {
                throw UnknownArgumentException(val);
            }
            (*currentValueOption)->value = val;
            currentValueOption++;
        }
    }
    return true;
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
    for (VOI it = values.begin(); it != values.end(); ++it) {
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
    for (OI it = options.begin(); it != options.end(); ++it) {
        if ((*it)->shortName == shortName) {
            return *it;
        }
    }
    return nullptr;
}

shared_ptr<Option> CommandLineProcessor::GetOptionByLongName(string longName) {
    for (OI it = options.begin(); it != options.end(); ++it) {
        if ((*it)->longName == longName) {
            return *it;
        }
    }
    return nullptr;
}
