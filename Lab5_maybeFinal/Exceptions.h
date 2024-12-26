#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

// Ієрархія винятків
class InputError : public std::exception {
protected:
    std::string message;
public:
    explicit InputError(const std::string& msg);        // explicit - запобігання неявному перетворенню типів
    const char* what() const noexcept override;         // what() - використовується для отримання повідомлення про помилку у вигляді рядка C-стилю (const char*)
    // noexcept - специфікатор, який вказує, що функція не може викидати винятки
};

class NotNumberError : public InputError {
public:
    explicit NotNumberError(const std::string& msg);
    const char* what() const noexcept override;
};

class NotAddressFormatError : public InputError {
public:
    explicit NotAddressFormatError(const std::string& msg);
    const char* what() const noexcept override;
};

class WrongNumberError : public InputError {
public:
    explicit WrongNumberError(const std::string& msg);
    const char* what() const noexcept override;
};

class FileError : public std::exception {
protected:
    std::string message;
public:
    explicit FileError(const std::string& msg);
    const char* what() const noexcept override;
};

class NotFoundFileError : public FileError {
public:
    explicit NotFoundFileError(const std::string& msg);
    const char* what() const noexcept override;
};

class FileContentError : public FileError {
public:
    explicit FileContentError(const std::string& msg);
    const char* what() const noexcept override;
};

// Функція для логування винятків
void log_exception(const std::exception& exception);

#endif // EXCEPTIONS_H
