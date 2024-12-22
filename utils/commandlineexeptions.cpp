//
// Created by nbollom on 30/05/16.
//

#include "commandlineexeptions.hpp"

#include <utility>

CommandLineException::CommandLineException(string exception_message) : message(std::move(exception_message)) { };

const char* CommandLineException::what() const noexcept {
    return message.c_str();
}

BaseOptionExistsException::BaseOptionExistsException() : CommandLineException("Option already exists") { }

OptionExistsException::OptionExistsException(shared_ptr<Option> current_option, shared_ptr<Option> conflict_option) : option(std::move(current_option)), conflict(std::move(conflict_option)) { };

string OptionExistsException::GetConflictMessage() {
    string message = "Conflicting value: ";
    if (option->shortName == conflict->shortName) {
        message.append(string(1, option->shortName));
    }
    else {
        message.append(option->longName);
    }
    message.append("\nOriginal description: ");
    message.append(conflict->description);
    message.append("\nNew description: ");
    message.append(option->description);
    message.append("\n");
    return message;
}

ValueOptionExistsException::ValueOptionExistsException(shared_ptr<ValueOption> current_option, shared_ptr<ValueOption> conflict_option) : option(std::move(current_option)), conflict(std::move(conflict_option)) { };

string ValueOptionExistsException::GetConflictMessage() {
    string message = "Conflicting value: ";
    message.append(option->name);
    message.append("\nOriginal description: ");
    message.append(conflict->description);
    message.append("\nNew description: ");
    message.append(option->description);
    message.append("\n");
    return message;
}

ParseException::ParseException() : CommandLineException("Error parsing command line") { }

InvalidArgumentException::InvalidArgumentException(string argument_value) : value(std::move(argument_value)) { }

string InvalidArgumentException::GetExceptionMessage() {
    string message = "Invalid argument ";
    message.append(value);
    return message;
}

UnknownArgumentException::UnknownArgumentException(string argument_value) : value(std::move(argument_value)) { }

string UnknownArgumentException::GetExceptionMessage() {
    string message = "Unknown argument ";
    message.append(value);
    return message;
}

MissingValueException::MissingValueException(string argument_value, shared_ptr<Option> current_option) : value(std::move(argument_value)), option(std::move(current_option)) { }

string MissingValueException::GetExceptionMessage() {
    string message = "Missing value for argument ";
    message.append(value);
    message.append("\n");
    message.append(option->valueDescription);
    return message;
}

