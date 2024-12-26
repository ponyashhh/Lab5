#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


//ой блять а я по назві InputError напевно не зрозумів що це реалізація InputError - прибрати коментарі
// Реалізація InputError
InputError::InputError(const std::string& msg) : message(msg) {}
const char* InputError::what() const noexcept {
    //нормальні среди разработки покажуть що це за функція якщо просто навестись на неї, тому не треба це пояснювати
    return message.c_str();      // c_str() — це метод класу std::string, який повертає вказівник на рядок у форматі C (тобто const char*)
}
//аналоічно коментар
// Реалізація NotNumberError
NotNumberError::NotNumberError(const std::string& msg)
    : InputError("NotNumberError: " + msg) {}
const char* NotNumberError::what() const noexcept {
    return message.c_str();
}
//аналоічно коментар
// Реалізація NotAddressFormatError
NotAddressFormatError::NotAddressFormatError(const std::string& msg)
    : InputError("NotAddressFormatError: " + msg) {}
const char* NotAddressFormatError::what() const noexcept {
    return message.c_str();
}
//аналоічно коментар
// Реалізація WrongNumberError
WrongNumberError::WrongNumberError(const std::string& msg)
    : InputError("WrongNumberError: " + msg) {}
const char* WrongNumberError::what() const noexcept {
    return message.c_str();
}
//аналоічно коментар
// Реалізація FileError
FileError::FileError(const std::string& msg) : message(msg) {}
const char* FileError::what() const noexcept {
    return message.c_str();
}
//аналоічно коментар
// Реалізація NotFoundFileError
NotFoundFileError::NotFoundFileError(const std::string& msg)
    : FileError("NotFoundFileError: " + msg) {}
const char* NotFoundFileError::what() const noexcept {
    return message.c_str();
}
//аналоічно коментар
// Реалізація FileContentError
FileContentError::FileContentError(const std::string& msg)
    : FileError("FileContentError: " + msg) {}
const char* FileContentError::what() const noexcept {
    return message.c_str();
}
//аналоічно коментар
// Логування винятків
void log_exception(const std::exception& exception) {
    //аналоічно коментар
    // Створюємо шлях до файлу exception_log.txt у поточній директорії
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
