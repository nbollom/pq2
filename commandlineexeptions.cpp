//
// Created by nbollom on 30/05/16.
//

#include "commandlineexeptions.h"

CommandLineException::CommandLineException(const string message) : exception(), _message(message) { };

const char* CommandLineException::what() {
    return _message.c_str();
}

BaseOptionExistsException::BaseOptionExistsException() : CommandLineException("Option already exists") { }

OptionExistsException::OptionExistsException(shared_ptr<Option> option, shared_ptr<Option> conflict) : BaseOptionExistsException(), _option(option), _conflict(conflict) { };

string OptionExistsException::GetConflictMessage() {
    string message = "Conflicting value: ";
    if (_option->shortName == _conflict->shortName) {
        message.append(string(1, _option->shortName));
    }
    else {
        message.append(_option->longName);
    }
    message.append("\nOriginal description: ");
    message.append(_conflict->description);
    message.append("\nNew description: ");
    message.append(_option->description);
    message.append("\n");
    return message;
}

ValueOptionExistsException::ValueOptionExistsException(shared_ptr<ValueOption> option, shared_ptr<ValueOption> conflict) : BaseOptionExistsException(), _option(option), _conflict(conflict) { };

string ValueOptionExistsException::GetConflictMessage() {
    string message = "Conflicting value: ";
    message.append(_option->name);
    message.append("\nOriginal description: ");
    message.append(_conflict->description);
    message.append("\nNew description: ");
    message.append(_option->description);
    message.append("\n");
    return message;
}

ParseException::ParseException() : CommandLineException("Error parsing command line") { }

InvalidArgumentException::InvalidArgumentException(string value) : ParseException(), _value(value) { }

string InvalidArgumentException::GetExceptionMessage() {
    string message = "Invalid argument ";
    message.append(_value);
    return message;
}

UnknownArgumentException::UnknownArgumentException(string value) : ParseException(), _value(value) { }

string UnknownArgumentException::GetExceptionMessage() {
    string message = "Unknown argument ";
    message.append(_value);
    return message;
}

MissingValueException::MissingValueException(string value, shared_ptr<Option> option) : ParseException(), _value(value), _option(option) { }

string MissingValueException::GetExceptionMessage() {
    string message = "Missing value for argument ";
    message.append(_value);
    message.append("\n");
    message.append(_option->valueDescription);
    return message;
}

