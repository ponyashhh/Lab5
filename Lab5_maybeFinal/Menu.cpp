#include "Menu.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include "FileHandler.h"
#include "addressBook.h"
#include "UI.h"
#include "Exceptions.h"
#include <algorithm>
#include "TestFileHandler.h"
#include "TestAddressBook.h"

//я вот читав і так і не поняв, тут є класи якійсь? якщо так то чого вони ніде явно не вказані чи я сліпий вже
//гарний початок для файлу це назва namespace, потім назва класу і потім тільки погнали все інше

//якщо це клас меню, то тут не має бути цієї функції - винести в екстенш 
bool isAlphabetic(const std::string& str) {
    for (char ch : str) {
        if (!std::isalpha(ch)) {
            return false;
        }
    }
    return true;
}

//навза методу старт канешно єбейша, і головне шо робить цей метод так і не понятно - вона і виводить і считує і валідує - прям гігачад метод якийсь
void Menu::start() {
    std::string file_path = "C:/Users/User/Documents/Беляш/vs/Lab5/Lab5/addresses.txt";

    //якшо юзати системи контролю версій то потрібність в подібних коментарях відпадає, можна просто закомітить шось і потім відкатити потрібну частину
    // Заготовочка для демонстрації неправильного шляху до файлу для NotFoundFileError
    //string file_path = "C:/Users/User/Documents/Беляш/vs/Lab5/Lab5/aaddresses.txt";

    // А я то думав шо тут відбувається - пасіба коментарю
    // Створення об'єктів
    AddressBook address_book;
    FileHandler file_handler(file_path);
    UI ui(address_book, file_handler);

    //шо за -1 зробити з цим шось
    int choice1 = -1;

    std::cout << "1. Start the main program\n";
    std::cout << "2. Start unit-testing\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
    std::string user_input;
    std::getline(std::cin, user_input);
    choice1 = std::stoi(user_input);

    int choice = -1;
    switch (choice1) {
        //всі оці кейс 1 2 3 4- винести в енам, кожен кейс також потягне на окрему функцію якщо не на клас
    case 1: {
        std::cout << "Starting the main program... ";

        while (choice != 0) {
            //метод
            std::cout << "\nMenu:\n";
            std::cout << "1. Load addresses from file\n";
            std::cout << "2. Add private house\n";
            std::cout << "3. Add apartment\n";
            std::cout << "4. Select addresses for mailing\n";
            std::cout << "5. Analyze addresses\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter your choice: ";
            //

            try {
                std::string user_input;
                std::getline(std::cin, user_input);

                //чи має цим займатись ця функція?
                // Перевірка на числовий ввід
                if (user_input.empty() || !std::all_of(user_input.begin(), user_input.end(), ::isdigit)) {
                    throw NotNumberError("Menu choice must be a number.");
                }

                choice = std::stoi(user_input);

                if (choice < 0 || choice > 5) {
                    throw WrongNumberError("Choice must be a number between 0 and 5.");
                }

                switch (choice) {
                    //всі оці кейс 1 2 3 4- винести в енам, кожен кейс також потягне на окрему функцію якщо не на клас
                case 1:
                    ui.LoadAddresses();
                    break;
                case 2: {
                    std::string city, street;
                    int building_number;
                    std::cout << "Enter city, street, building number: ";
                    std::getline(std::cin, user_input);
                    std::istringstream ss(user_input);
                    //ця функція точно не повинна займатися валідацією данних
                    if (ss >> city >> street >> building_number) {

                        if (!isAlphabetic(city)) {
                            throw NotAddressFormatError("City must contain only alphabetic characters.");
                            break;
                        }
                        if (!isAlphabetic(street)) {
                            throw NotAddressFormatError("Street must contain only alphabetic characters.");
                            break;
                        }

                        ui.AddPrivateAddress(city, street, building_number);
                    }
                    else {
                        throw NotAddressFormatError("You must provide exactly three values: city(str), street(str), and building number(int).");
                    }
                    break;
                }
                case 3: {
                    std::string city, street;
                    int building_number, apartment_number;
                    std::cout << "Enter city, street, building number and apartment number: ";
                    std::getline(std::cin, user_input);
                    std::istringstream ss(user_input);

                    if (ss >> city >> street >> building_number >> apartment_number) {
                        if (!isAlphabetic(city)) {
                            throw NotAddressFormatError("City must contain only alphabetic characters.");
                            break;
                        }
                        if (!isAlphabetic(street)) {
                            throw NotAddressFormatError("Street must contain only alphabetic characters.");
                            break;
                        }

                        ui.AddAppartmentAddress(city, street, building_number, apartment_number);
                    }
                    else {
                        throw NotAddressFormatError("You must provide exactly four values: city(str), stree(str), building number(int) and appartment number(int).");
                    }
                    break;
                }
                case 4:
                    ui.SelectAddressesForMailing();
                    break;
                case 5:
                    ui.AnalyzeAddresses();
                    break;
                case 0:
                    std::cout << "Exiting...\n";
                    break;
                default:
                    throw WrongNumberError("Invalid choice. Please try again.");
                }
            }
            //тупо все шо знизву відрізняється декількома символами - в метод
            catch (const NotNumberError& e) {
                //Єбать логування помилки
                log_exception(e);  // Логування помилки
                std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
            }
            catch (const WrongNumberError& e) {
                //Єбать логування помилки
                log_exception(e);  // Логування помилки
                std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
            }
            catch (const NotAddressFormatError& e) {
                //Єбать логування помилки
                log_exception(e);  // Логування помилки
                std::cerr << "Wrong data format! Caught exception: " << e.what() << "\n";
            }
            catch (const std::exception& e) {
                //Єбать логування помилки
                log_exception(e);  // Логування помилки
                std::cerr << "An unexpected error occurred: " << e.what() << "\n";
            }
        }
        break;
    }
    case 2: {
        std::cout << "Starting unit-testing... ";
        cout << endl;

        cout << "-------TestFileHandler------" << endl;
        TestFileHandler test_handler;
        // Запускаємо всі тести
        test_handler.run_all_tests();


        //// Відкриваємо null stream, щоб все зайве йшло в "чорну діру"
        //std::ofstream null_stream("NUL");

        //// Перехоплюємо стандартний вивід
        //std::streambuf* old_buf = std::cout.rdbuf(null_stream.rdbuf());

        cout << "-------TestAddressBook------" << endl;
        //TestAddressBook test_book; 
        //// Запускаємо всі тести
        //test_book.run_all_tests(); 

        //// Відновлюємо стандартний вивід
        //std::cout.rdbuf(old_buf); 

        TestAddressBook tests;
        tests.run_all_tests();


        break;
    }
    case 0:
        std::cout << "Exiting...\n";
        break;
    }

}

//    while (choice != 0) {
//        //метод
//        std::cout << "\nMenu:\n";
//        std::cout << "1. Load addresses from file\n";
//        std::cout << "2. Add private house\n";
//        std::cout << "3. Add apartment\n";
//        std::cout << "4. Select addresses for mailing\n";
//        std::cout << "5. Analyze addresses\n";
//        std::cout << "0. Exit\n";
//        std::cout << "Enter your choice: ";
//        //
//
//        try {
//            std::string user_input;
//            std::getline(std::cin, user_input);
//
//            //чи має цим займатись ця функція?
//            // Перевірка на числовий ввід
//            if (user_input.empty() || !std::all_of(user_input.begin(), user_input.end(), ::isdigit)) {
//                throw NotNumberError("Menu choice must be a number.");
//            }
//
//            choice = std::stoi(user_input);
//
//            if (choice < 0 || choice > 5) {
//                throw WrongNumberError("Choice must be a number between 0 and 5.");
//            }
//
//            switch (choice) {
//                //всі оці кейс 1 2 3 4- винести в енам, кожен кейс також потягне на окрему функцію якщо не на клас
//            case 1:
//                ui.LoadAddresses();
//                break;
//            case 2: {
//                std::string city, street;
//                int building_number;
//                std::cout << "Enter city, street, building number: ";
//                std::getline(std::cin, user_input);
//                std::istringstream ss(user_input);
//                //ця функція точно не повинна займатися валідацією данних
//                if (ss >> city >> street >> building_number) {
//
//                    if (!isAlphabetic(city)) {
//                        throw NotAddressFormatError("City must contain only alphabetic characters.");
//                        break;
//                    }
//                    if (!isAlphabetic(street)) {
//                        throw NotAddressFormatError("Street must contain only alphabetic characters.");
//                        break;
//                    }
//
//                    ui.AddPrivateAddress(city, street, building_number);
//                }
//                else {
//                    throw NotAddressFormatError("You must provide exactly three values: city(str), street(str), and building number(int).");
//                }
//                break;
//            }
//            case 3: {
//                std::string city, street;
//                int building_number, apartment_number;
//                std::cout << "Enter city, street, building number and apartment number: ";
//                std::getline(std::cin, user_input);
//                std::istringstream ss(user_input);
//
//                if (ss >> city >> street >> building_number >> apartment_number) {
//                    if (!isAlphabetic(city)) {
//                        throw NotAddressFormatError("City must contain only alphabetic characters.");
//                        break;
//                    }
//                    if (!isAlphabetic(street)) {
//                        throw NotAddressFormatError("Street must contain only alphabetic characters.");
//                        break;
//                    }
//
//                    ui.AddAppartmentAddress(city, street, building_number, apartment_number);
//                }
//                else {
//                    throw NotAddressFormatError("You must provide exactly four values: city(str), stree(str), building number(int) and appartment number(int).");
//                }
//                break;
//            }
//            case 4:
//                ui.SelectAddressesForMailing();
//                break;
//            case 5:
//                ui.AnalyzeAddresses();
//                break;
//            case 0:
//                std::cout << "Exiting...\n";
//                break;
//            default:
//                throw WrongNumberError("Invalid choice. Please try again.");
//            }
//        }
//        //тупо все шо знизву відрізняється декількома символами - в метод
//        catch (const NotNumberError& e) {
//            //Єбать логування помилки
//            log_exception(e);  // Логування помилки
//            std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
//        }
//        catch (const WrongNumberError& e) {
//            //Єбать логування помилки
//            log_exception(e);  // Логування помилки
//            std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
//        }
//        catch (const NotAddressFormatError& e) {
//            //Єбать логування помилки
//            log_exception(e);  // Логування помилки
//            std::cerr << "Wrong data format! Caught exception: " << e.what() << "\n";
//        }
//        catch (const std::exception& e) {
//            //Єбать логування помилки
//            log_exception(e);  // Логування помилки
//            std::cerr << "An unexpected error occurred: " << e.what() << "\n";
//        }
//    }
//}
