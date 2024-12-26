#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
//напевно по назві Exceptions не зрозуміло що це для винятків і нам потрібен коментар для пояснення цього
#include "Exceptions.h"  // Для використання винятків
#include <filesystem>

FileHandler::FileHandler(const std::string& filename) : filename(filename) {}

std::vector<std::shared_ptr<Address>> FileHandler::LoadAddresses() {
    std::vector<std::shared_ptr<Address>> addresses;

    // Перевірка існування файлу
    if (!std::filesystem::exists(filename)) {
        throw NotFoundFileError("File not found: " + filename);
    }

    std::ifstream file;

    // Спроба відкрити файл
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    // Парсинг файлу з обробкою можливих помилок
    try {
        addresses = _parseFile(file);
    }
    catch (const FileContentError& e) {
        throw; // Перевиконуємо помилку, щоб вона була оброблена на вищому рівні
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Unexpected error reading file: " + std::string(e.what()));
    }

    return addresses;
}


std::vector<std::shared_ptr<Address>> FileHandler::_parseFile(std::ifstream& file) {
    std::vector<std::shared_ptr<Address>> addresses;
    std::string line;
    int line_number = 0;

    while (std::getline(file, line)) {
        line_number++;

        // Видаляємо зайві пробіли з початку та кінця рядка
        line = line.substr(line.find_first_not_of(" "), line.find_last_not_of(" ") + 1);

        // Розділяємо рядок на дві частини за допомогою ":"
        size_t colon_pos = line.find(":");
        if (colon_pos == std::string::npos) {
            throw FileContentError("Line " + std::to_string(line_number) + ": Incorrect format (missing ':' separator)");
        }

        std::string address_type = line.substr(0, colon_pos);
        std::string address_data = line.substr(colon_pos + 1);

        // Очищаємо пробіли навколо даних
        address_type = address_type.substr(address_type.find_first_not_of(" "), address_type.find_last_not_of(" ") + 1);
        address_data = address_data.substr(address_data.find_first_not_of(" "), address_data.find_last_not_of(" ") + 1);

        std::istringstream data_stream(address_data);
        std::vector<std::string> tokens;
        std::string token;

        // Розбиваємо дані на складові
        while (data_stream >> token) {
            tokens.push_back(token);
        }

        // Перевірка для PrivateHouse або Appartment
        try {
            if (address_type == "Private" && tokens.size() == 3) {
                std::string city = tokens[0];
                std::string street = tokens[1];

                // Перевірка, чи номер є валідним цілим числом
                try {
                    int building_number = std::stoi(tokens[2]);
                    addresses.push_back(std::make_shared<PrivateHouse>(city, street, building_number));
                }
                catch (const std::invalid_argument&) {
                    throw FileContentError("Line " + std::to_string(line_number) + ": Building number is not a valid integer.");
                }
                catch (const std::out_of_range&) {
                    throw FileContentError("Line " + std::to_string(line_number) + ": Building number is out of range.");
                }
            }
            else if (address_type == "Appartment" && tokens.size() == 4) {
                std::string city = tokens[0];
                std::string street = tokens[1];

                // Перевірка на валідність чисел для будинку і квартири
                try {
                    int building_number = std::stoi(tokens[2]);
                    int appartment_number = std::stoi(tokens[3]);
                    addresses.push_back(std::make_shared<Appartment>(city, street, building_number, appartment_number));
                }
                catch (const std::invalid_argument&) {
                    throw FileContentError("Line " + std::to_string(line_number) + ": Building or apartment number is not a valid integer.");
                }
                catch (const std::out_of_range&) {
                    throw FileContentError("Line " + std::to_string(line_number) + ": Building or apartment number is out of range.");
                }
            }
            else {
                throw FileContentError("Line " + std::to_string(line_number) + ": Incorrect data for " + address_type + " (expected 3 or 4 values)");
            }
        }
        catch (const std::out_of_range&) {
            throw FileContentError("Line " + std::to_string(line_number) + ": Integer value is out of range");
        }
    }

    return addresses;
}



////знову кілометровий метод - розбити, метод не повинен займати більше екрану
//std::vector<std::shared_ptr<Address>> FileHandler::_parseFile(std::ifstream& file) {
//    std::vector<std::shared_ptr<Address>> addresses;
//    std::string line;
//    int line_number = 0;
//
//    while (std::getline(file, line)) {
//        line_number++;
//
//        // Видаляємо зайві пробіли з початку та кінця рядка
//        line = line.substr(line.find_first_not_of(" "), line.find_last_not_of(" ") + 1);
//
//        // Розділяємо рядок на дві частини за допомогою ":"
//        size_t colon_pos = line.find(":");
//        if (colon_pos == std::string::npos) {
//            throw FileContentError("Line " + std::to_string(line_number) + ": Incorrect format (missing ':' separator)");
//        }
//
//        std::string address_type = line.substr(0, colon_pos);
//        std::string address_data = line.substr(colon_pos + 1);
//
//        // Очищаємо пробіли навколо даних
//        address_type = address_type.substr(address_type.find_first_not_of(" "), address_type.find_last_not_of(" ") + 1);
//        address_data = address_data.substr(address_data.find_first_not_of(" "), address_data.find_last_not_of(" ") + 1);
//
//        std::istringstream data_stream(address_data);
//        std::vector<std::string> tokens;
//        std::string token;
//
//        // Розбиваємо дані на складові
//        while (data_stream >> token) {
//            tokens.push_back(token);
//        }
//
//        // Перевірка для PrivateHouse або Appartment
//        try {
//            if (address_type == "Private" && tokens.size() == 3) {
//                std::string city = tokens[0];
//                std::string street = tokens[1];
//                if (std::stof(tokens[2]) != std::stoi(tokens[2])) {
//                    throw FileContentError("Line " + std::to_string(line_number) + ": Building or appartment number is not an integer");
//                };
//                int building_number = std::stoi(tokens[2]);
//                addresses.push_back(std::make_shared<PrivateHouse>(city, street, building_number));
//            }
//            else if (address_type == "Appartment" && tokens.size() == 4) {
//                std::string city = tokens[0];
//                std::string street = tokens[1];
//                //рядки 90-92 і 93-95 відрізняються одним символом - у метод
//                if (std::stof(tokens[2]) != std::stoi(tokens[2])) {
//                    throw FileContentError("Line " + std::to_string(line_number) + ": Building or appartment number is not an integer");
//                };
//                int building_number = std::stoi(tokens[2]);
//                if (std::stof(tokens[3]) != std::stoi(tokens[3])) {
//                    throw FileContentError("Line " + std::to_string(line_number) + ": Building or appartment number is not an integer");
//                };
//                int appartment_number = std::stoi(tokens[3]);
//                addresses.push_back(std::make_shared<Appartment>(city, street, building_number, appartment_number));
//            }
//            else {
//                throw FileContentError("Line " + std::to_string(line_number) + ": Incorrect data for " + address_type + " (expected 3 or 4 values)");
//            }
//        }
//        catch (const std::out_of_range&) {
//            throw FileContentError("Line " + std::to_string(line_number) + ": Integer value is out of range");
//        }
//    }
//
//    return addresses;
//}

void FileHandler::SaveAddress(const Address& address) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << address.toString() << std::endl;
        file.close();
    }
    else {
        std::cerr << "Error opening file for saving." << std::endl;
    }
}
