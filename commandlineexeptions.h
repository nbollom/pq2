//
// Created by nbollom on 30/05/16.
//

#ifndef PQ2_COMMANDLINEEXEPTIONS_H
#define PQ2_COMMANDLINEEXEPTIONS_H

#include <exception>
#include <string>
#include <memory>
#include "commandlineoptions.h"

using namespace std;

class CommandLineException : public exception {

private:
    const string message;

public:
    CommandLineException(const string exception_message);
    const char *what();
};

class BaseOptionExistsException : public CommandLineException {

public:
    BaseOptionExistsException();
    virtual string GetConflictMessage() = 0;
};

class OptionExistsException : public BaseOptionExistsException {

private:
    shared_ptr<Option> option;
    shared_ptr<Option> conflict;

public:
    OptionExistsException(shared_ptr<Option> current_option, shared_ptr<Option> conflict_option);
    string GetConflictMessage() override;
};

class ValueOptionExistsException : public BaseOptionExistsException {

private:
    shared_ptr<ValueOption> option;
    shared_ptr<ValueOption> conflict;

public:
    ValueOptionExistsException(shared_ptr<ValueOption> current_option, shared_ptr<ValueOption> conflict_option);
    string GetConflictMessage() override;
};

class ParseException : public CommandLineException {

public:
    ParseException();
    virtual string GetExceptionMessage() = 0;
};

class InvalidArgumentException : public ParseException {

private:
    string value;

public:
    InvalidArgumentException(string argument_value);
    string GetExceptionMessage() override;
};

class UnknownArgumentException : public ParseException {
private:
    string value;

public:
    UnknownArgumentException(string argument_value);
    string GetExceptionMessage() override;
};

class MissingValueException : public ParseException {
private:
    string value;
    shared_ptr<Option> option;

public:
    MissingValueException(string argument_value, shared_ptr<Option> current_option);
    string GetExceptionMessage() override;
};

#endif //PQ2_COMMANDLINEEXEPTIONS_H
