//
// Created by nbollom on 30/05/16.
//

#include "commandline.h"
#include "commandlineexeptions.h"
#include <iostream>
#include <utility>

inline unsigned long max(const unsigned long &a, const unsigned long &b) {
    if (a > b) {
        return a;
    }
    return b;
}

inline std::string pad(const unsigned long length) {
    return std::string(length, ' ');
}

CommandLineProcessor::CommandLineProcessor(string program_name, string program_description, string program_version)
        : name(std::move(program_name)), description(std::move(program_description)), version(std::move(program_version)) {
    options.push_back(make_shared<Option>('h', "help", "Shows this help screen", false, "", false, ""));
    options.push_back(make_shared<Option>('v', "version", "prints the version", false, "", false, ""));
}

void CommandLineProcessor::AddOption(const char shortName, const string& longName, const string& description, const bool hasValue, const string& valueDescription, const string& defaultValue) {
    const auto option = make_shared<Option>(shortName, longName, description, hasValue, valueDescription, false, defaultValue);
    for (const auto& existingOption : options) {
        if (option->shortName == existingOption->shortName || option->longName == existingOption->longName) {
            throw OptionExistsException(option, existingOption);
        }
    }
    options.push_back(option);
}

void CommandLineProcessor::AddValueOnlyOption(const string& name, const string& description, const string& defaultValue) {
    const auto option = make_shared<ValueOption>(name, description, defaultValue);
    for (const auto& existingOption : values) {
        if (option->name == existingOption->name) {
            throw ValueOptionExistsException(option, existingOption);
        }
    }
    values.push_back(option);
}

bool CommandLineProcessor::Parse(const int argc, const char *const *argv) {
    const string executable = argv[0];
    bool parsingValueOptions = false;
    auto currentValueOption = values.begin();
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
                std::cout << name << "(" << version << ")\n";
                std::cout << description << "\n";
                options.sort([](const shared_ptr<Option>& a, const shared_ptr<Option>& b){
                    return a->shortName < b->shortName;
                });
                std::string usage_str;
                std::string option_usage_str;
                unsigned long longest_name = 0;
                for (const auto &op : options) {
                    if (op->hasValue) {
                        option_usage_str += " -";
                        option_usage_str += op->shortName;
                        option_usage_str += " <";
                        option_usage_str += op->longName;
                        option_usage_str += ">";
                    }
                    else {
                        usage_str += op->shortName;
                    }
                    longest_name = max(longest_name, op->longName.length());
                }
                std::string value_usage_str;
                for (const auto &op: values) {
                    if (!value_usage_str.empty()) {
                        value_usage_str += " ";
                    }
                    value_usage_str += "[" + op->name + "]";
                }
                std::cout << "Usage: " << executable << " [-" << usage_str << option_usage_str << "] " + value_usage_str + "\n\n";
                for (const auto &op : options) {
                    std::cout << "\t-" << op->shortName << "\t--" << op->longName << pad(longest_name - op->longName.length()) << "\t" << op->description << "\n";
                    if (op->hasValue) {
                        std::cout << "\t\t" << pad(longest_name + 2) << "\t" << op->valueDescription;
                        if (!op->value.empty()) {
                            std::cout << " (Default: " << op->value << ")\n";
                        }
                        else {
                            std::cout << "\n";
                        }
                    }
                }
                std::cout << "\n";
                for (const auto &op : values) {
                    std::cout << "\t" << op->name << "\t\t" << op->description << "\n";
                }
                std::cout << "\n";
                return false;
            }
            if (option->shortName == 'v') {
                std::cout << name << "\n";
                std::cout << "Version: " << version << "\n";
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
            ++currentValueOption;
        }
    }
    return true;
}

bool CommandLineProcessor::IsSet(const char shortName) {
    const auto option = GetOptionByShortName(shortName);
    if (option == nullptr) {
        return false;
    }
    return option->found;
}

bool CommandLineProcessor::IsSet(const string &longName) {
    const auto option = GetOptionByLongName(longName);
    if (option == nullptr) {
        return false;
    }
    return option->found;
}

string CommandLineProcessor::GetOptionValue(const char shortName) {
    const auto option = GetOptionByShortName(shortName);
    if (option == nullptr) {
        return "";
    }
    return option->value;
}

string CommandLineProcessor::GetOptionValue(const string &longName) {
    const auto option = GetOptionByLongName(longName);
    if (option == nullptr) {
        return "";
    }
    return option->value;
}

string CommandLineProcessor::GetValueOnlyOptionValue(const string& name) const {
    shared_ptr<ValueOption> option = nullptr;
    for (const auto & value : values) {
        if (value->name == name) {
            option = value;
            break;
        }
    }
    if (option == nullptr) {
        return "";
    }
    return option->value;
}

shared_ptr<Option> CommandLineProcessor::GetOptionByShortName(const char shortName) {
    for (auto &option : options) {
        if (option->shortName == shortName) {
            return option;
        }
    }
    return nullptr;
}

shared_ptr<Option> CommandLineProcessor::GetOptionByLongName(const string& longName) {
    for (auto &option : options) {
        if (option->longName == longName) {
            return option;
        }
    }
    return nullptr;
}
