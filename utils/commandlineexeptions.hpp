//
// Created by nbollom on 30/05/16.
//

#pragma once

#include <exception>
#include <string>
#include <memory>
#include "commandlineoptions.hpp"

using namespace std;

class CommandLineException : public exception {

private:
    const string message;

public:
    explicit CommandLineException(string exception_message);
    [[nodiscard]] const char *what() const noexcept override;
};

class BaseOptionExistsException : public CommandLineException {

public:
    BaseOptionExistsException();
    virtual string GetConflictMessage() = 0;
};

class OptionExistsException final : public BaseOptionExistsException {

private:
    shared_ptr<Option> option;
    shared_ptr<Option> conflict;

public:
    OptionExistsException(shared_ptr<Option> current_option, shared_ptr<Option> conflict_option);
    [[nodiscard]] string GetConflictMessage() override;
};

class ValueOptionExistsException final : public BaseOptionExistsException {

private:
    shared_ptr<ValueOption> option;
    shared_ptr<ValueOption> conflict;

public:
    ValueOptionExistsException(shared_ptr<ValueOption> current_option, shared_ptr<ValueOption> conflict_option);
    [[nodiscard]] string GetConflictMessage() override;
};

class ParseException : public CommandLineException {

public:
    ParseException();
    virtual string GetExceptionMessage() = 0;
};

class InvalidArgumentException final : public ParseException {

private:
    string value;

public:
    explicit InvalidArgumentException(string argument_value);
    [[nodiscard]] string GetExceptionMessage() override;
};

class UnknownArgumentException final : public ParseException {
private:
    string value;

public:
    explicit UnknownArgumentException(string argument_value);
    [[nodiscard]] string GetExceptionMessage() override;
};

class MissingValueException final : public ParseException {
private:
    string value;
    shared_ptr<Option> option;

public:
    MissingValueException(string argument_value, shared_ptr<Option> current_option);
    [[nodiscard]] string GetExceptionMessage() override;
};
