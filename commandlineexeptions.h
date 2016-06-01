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
    const string _message;

public:
    CommandLineException(const string message);
    const char *what();
};

class BaseOptionExistsException : public CommandLineException {

public:
    BaseOptionExistsException();
    virtual string GetConflictMessage() = 0;
};

class OptionExistsException : public BaseOptionExistsException {

private:
    shared_ptr<Option> _option;
    shared_ptr<Option> _conflict;

public:
    OptionExistsException(shared_ptr<Option> option, shared_ptr<Option> conflict);
    string GetConflictMessage() override;
};

class ValueOptionExistsException : public BaseOptionExistsException {

private:
    shared_ptr<ValueOption> _option;
    shared_ptr<ValueOption> _conflict;

public:
    ValueOptionExistsException(shared_ptr<ValueOption> option, shared_ptr<ValueOption> conflict);
    string GetConflictMessage() override;
};

class ParseException : public CommandLineException {

public:
    ParseException();
    virtual string GetExceptionMessage() = 0;
};

class InvalidArgumentException : public ParseException {

private:
    string _value;

public:
    InvalidArgumentException(string value);
    string GetExceptionMessage() override;
};

class UnknownArgumentException : public ParseException {
private:
    string _value;

public:
    UnknownArgumentException(string value);
    string GetExceptionMessage() override;
};

class MissingValueException : public ParseException {
private:
    string _value;
    shared_ptr<Option> _option;

public:
    MissingValueException(string value, shared_ptr<Option> option);
    string GetExceptionMessage() override;
};

#endif //PQ2_COMMANDLINEEXEPTIONS_H
