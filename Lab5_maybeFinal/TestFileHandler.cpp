#include "TestFileHandler.h"
#include "FileHandler.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>  // Для коректної обробки виключень

void TestFileHandler::test_load_addresses_valid_file() {
    try {
        std::ofstream file("addresses1.txt");
        if (!file.is_open()) {
            std::cerr << "Test failed: Unable to open file for writing.\n";
            return;
        }
        file << "Private: Kyiv Khreshchatyk 10\n";
        file << "Appartment: Lviv Shevchenka 5 12\n";
        file.close();

        FileHandler file_handler("addresses1.txt");
        auto addresses = file_handler.LoadAddresses();

        if (addresses.size() != 2) {
            std::cerr << "Test failed: Incorrect number of addresses loaded.\n";
            return;
        }

        if (addresses[0]->GetType() != "Private" || addresses[1]->GetType() != "Appartment") {
            std::cerr << "Test failed: Incorrect address types.\n";
            return;
        }

        std::cout << "Test passed: Valid file loading.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed due to exception: " << e.what() << "\n";
    }
}

void TestFileHandler::test_load_addresses_file_not_found() {
    try {
        FileHandler file_handler("non_existent_file.txt");
        file_handler.LoadAddresses();
        std::cout << "Test failed: No exception thrown for non-existent file.\n";
    }
    catch (const NotFoundFileError&) {
        std::cout << "Test passed: Exception thrown for non-existent file.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed due to exception: " << e.what() << "\n";
    }
}

void TestFileHandler::test_load_addresses_invalid_format() {
    try {
        std::ofstream file("addresses1.txt");
        if (!file.is_open()) {
            std::cerr << "Test failed: Unable to open file for writing.\n";
            return;
        }
        file << "Private: Kyiv Khreshchatyk 10\n";
        file << "InvalidLineWithoutColon\n";
        file.close();

        FileHandler file_handler("addresses1.txt");
        file_handler.LoadAddresses();
        std::cout << "Test failed: No exception thrown for invalid format.\n";
    }
    catch (const FileContentError&) {
        std::cout << "Test passed: Exception thrown for invalid format.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed due to exception: " << e.what() << "\n";
    }
}

void TestFileHandler::test_load_addresses_invalid_number() {
    try {
        std::ofstream file("addresses1.txt");
        if (!file.is_open()) {
            std::cerr << "Test failed: Unable to open file for writing.\n";
            return;
        }
        file << "Private: Kyiv Khreshchatyk ABC\n";  // Некоректне число
        file.close();

        FileHandler file_handler("addresses1.txt");
        file_handler.LoadAddresses();
        std::cout << "Test failed: No exception thrown for invalid number.\n";
    }
    catch (const FileContentError&) {
        std::cout << "Test passed: Exception thrown for invalid number.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed due to exception: " << e.what() << "\n";
    }
}

// Очищення файлу перед тестуванням
void clearFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc); // Очищаємо файл
    if (!file) {
        std::cerr << "Error clearing file: " << filename << std::endl;
    }
}

void TestFileHandler::test_save_address() {
    // Очищаємо файл перед тестом
    clearFile("addresses1.txt");
    try {
        PrivateHouse address("Kyiv", "Khreshchatyk", 10);
        FileHandler file_handler("addresses1.txt");

        file_handler.SaveAddress(address);

        std::ifstream file("addresses1.txt");
        std::string line;
        std::getline(file, line);
        if (line != "Private: Kyiv Khreshchatyk 10") {
            std::cout << "Test failed: Address not saved correctly.\n";
        }
        else {
            std::cout << "Test passed: Address saved correctly.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed due to exception: " << e.what() << "\n";
    }
}

void TestFileHandler::test_load_addresses_boundary_values() {
    try {
        // Тест для граничних значень номера будинку 
        std::ofstream file("addresses1.txt");
        if (!file.is_open()) {
            std::cerr << "Test failed: Unable to open file for writing.\n";
            return;
        }
        file << "Private: Kyiv Khreshchatyk " << std::numeric_limits<int>::min() << "\n"; // Мінімальне значення int (-2147483648)
        file << "Private: Lviv Shevchenka " << std::numeric_limits<int>::max() << "\n"; // Максимальне значення int (2147483647)
        file << "Private: Odesa Pushkina 0\n"; // Нульове значення
        file.close();

        FileHandler file_handler("addresses1.txt");
        auto addresses = file_handler.LoadAddresses();

        if (addresses.size() != 3) {
            std::cerr << "Test failed: Incorrect number of addresses loaded.\n";
            return;
        }

        // Перевірка, чи правильно завантажились дані
        if (addresses[0]->GetType() != "Private" || addresses[1]->GetType() != "Private" || addresses[2]->GetType() != "Private") {
            std::cerr << "Test failed: Incorrect address types.\n";
            return;
        }

        std::cout << "Test passed: Boundary values loaded correctly.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed due to exception: " << e.what() << "\n";
    }
}

// Функція для запуску всіх тестів
void TestFileHandler::run_all_tests() {
    test_load_addresses_valid_file();
    test_load_addresses_file_not_found();
    test_load_addresses_invalid_format();
    test_load_addresses_invalid_number();
    test_save_address();
    test_load_addresses_boundary_values();
}
