#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


//�� ����� � � �� ���� InputError ������� �� ������� �� �� ��������� InputError - �������� ��������
// ��������� InputError
InputError::InputError(const std::string& msg) : message(msg) {}
const char* InputError::what() const noexcept {
    //�������� ����� ���������� �������� �� �� �� ������� ���� ������ ��������� �� ��, ���� �� ����� �� ����������
    return message.c_str();      // c_str() � �� ����� ����� std::string, ���� ������� �������� �� ����� � ������ C (����� const char*)
}
//�������� ��������
// ��������� NotNumberError
NotNumberError::NotNumberError(const std::string& msg)
    : InputError("NotNumberError: " + msg) {}
const char* NotNumberError::what() const noexcept {
    return message.c_str();
}
//�������� ��������
// ��������� NotAddressFormatError
NotAddressFormatError::NotAddressFormatError(const std::string& msg)
    : InputError("NotAddressFormatError: " + msg) {}
const char* NotAddressFormatError::what() const noexcept {
    return message.c_str();
}
//�������� ��������
// ��������� WrongNumberError
WrongNumberError::WrongNumberError(const std::string& msg)
    : InputError("WrongNumberError: " + msg) {}
const char* WrongNumberError::what() const noexcept {
    return message.c_str();
}
//�������� ��������
// ��������� FileError
FileError::FileError(const std::string& msg) : message(msg) {}
const char* FileError::what() const noexcept {
    return message.c_str();
}
//�������� ��������
// ��������� NotFoundFileError
NotFoundFileError::NotFoundFileError(const std::string& msg)
    : FileError("NotFoundFileError: " + msg) {}
const char* NotFoundFileError::what() const noexcept {
    return message.c_str();
}
//�������� ��������
// ��������� FileContentError
FileContentError::FileContentError(const std::string& msg)
    : FileError("FileContentError: " + msg) {}
const char* FileContentError::what() const noexcept {
    return message.c_str();
}
//�������� ��������
// ��������� �������
void log_exception(const std::exception& exception) {
    //�������� ��������
    // ��������� ���� �� ����� exception_log.txt � ������� ��������
    std::string log_file_path = fs::current_path().string() + "/exception_log.txt";

    std::ofstream file(log_file_path, std::ios::app);
    if (file.is_open()) {
        file << "Caught exception: " << exception.what() << "\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open log file for writing.\n";
    }
}
