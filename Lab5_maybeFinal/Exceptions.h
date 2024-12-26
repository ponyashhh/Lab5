#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>

// �������� �������
class InputError : public std::exception {
protected:
    std::string message;
public:
    explicit InputError(const std::string& msg);        // explicit - ���������� �������� ������������ ����
    const char* what() const noexcept override;         // what() - ��������������� ��� ��������� ����������� ��� ������� � ������ ����� C-����� (const char*)
    // noexcept - ������������, ���� �����, �� ������� �� ���� �������� �������
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

// ������� ��� ��������� �������
void log_exception(const std::exception& exception);

#endif // EXCEPTIONS_H
