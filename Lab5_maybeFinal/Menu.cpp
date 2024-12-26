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

//� ��� ����� � ��� � �� �����, ��� � ����� �����? ���� ��� �� ���� ���� ��� ���� �� ������ �� � ����� ���
//������ ������� ��� ����� �� ����� namespace, ���� ����� ����� � ���� ����� ������� ��� ����

//���� �� ���� ����, �� ��� �� �� ���� ���� ������� - ������� � ������� 
bool isAlphabetic(const std::string& str) {
    for (char ch : str) {
        if (!std::isalpha(ch)) {
            return false;
        }
    }
    return true;
}

//����� ������ ����� ������� ������, � ������� �� ������ ��� ����� ��� � �� ������� - ���� � �������� � ����� � ����� - ���� ������ ����� ������
void Menu::start() {
    std::string file_path = "C:/Users/User/Documents/�����/vs/Lab5/Lab5/addresses.txt";

    //���� ����� ������� �������� ����� �� ��������� � ������� ���������� ������, ����� ������ ��������� ���� � ���� �������� ������� �������
    // ����������� ��� ������������ ������������� ����� �� ����� ��� NotFoundFileError
    //string file_path = "C:/Users/User/Documents/�����/vs/Lab5/Lab5/aaddresses.txt";

    // � � �� ����� �� ��� ���������� - ����� ���������
    // ��������� ��'����
    AddressBook address_book;
    FileHandler file_handler(file_path);
    UI ui(address_book, file_handler);

    //�� �� -1 ������� � ��� ����
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
        //�� ��� ���� 1 2 3 4- ������� � ����, ����� ���� ����� ������� �� ������ ������� ���� �� �� ����
    case 1: {
        std::cout << "Starting the main program... ";

        while (choice != 0) {
            //�����
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

                //�� �� ��� ��������� �� �������?
                // �������� �� �������� ���
                if (user_input.empty() || !std::all_of(user_input.begin(), user_input.end(), ::isdigit)) {
                    throw NotNumberError("Menu choice must be a number.");
                }

                choice = std::stoi(user_input);

                if (choice < 0 || choice > 5) {
                    throw WrongNumberError("Choice must be a number between 0 and 5.");
                }

                switch (choice) {
                    //�� ��� ���� 1 2 3 4- ������� � ����, ����� ���� ����� ������� �� ������ ������� ���� �� �� ����
                case 1:
                    ui.LoadAddresses();
                    break;
                case 2: {
                    std::string city, street;
                    int building_number;
                    std::cout << "Enter city, street, building number: ";
                    std::getline(std::cin, user_input);
                    std::istringstream ss(user_input);
                    //�� ������� ����� �� ������� ��������� ��������� ������
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
            //���� ��� �� ������ ����������� ��������� ��������� - � �����
            catch (const NotNumberError& e) {
                //����� ��������� �������
                log_exception(e);  // ��������� �������
                std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
            }
            catch (const WrongNumberError& e) {
                //����� ��������� �������
                log_exception(e);  // ��������� �������
                std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
            }
            catch (const NotAddressFormatError& e) {
                //����� ��������� �������
                log_exception(e);  // ��������� �������
                std::cerr << "Wrong data format! Caught exception: " << e.what() << "\n";
            }
            catch (const std::exception& e) {
                //����� ��������� �������
                log_exception(e);  // ��������� �������
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
        // ��������� �� �����
        test_handler.run_all_tests();


        //// ³�������� null stream, ��� ��� ����� ���� � "����� ���"
        //std::ofstream null_stream("NUL");

        //// ������������ ����������� ����
        //std::streambuf* old_buf = std::cout.rdbuf(null_stream.rdbuf());

        cout << "-------TestAddressBook------" << endl;
        //TestAddressBook test_book; 
        //// ��������� �� �����
        //test_book.run_all_tests(); 

        //// ³��������� ����������� ����
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
//        //�����
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
//            //�� �� ��� ��������� �� �������?
//            // �������� �� �������� ���
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
//                //�� ��� ���� 1 2 3 4- ������� � ����, ����� ���� ����� ������� �� ������ ������� ���� �� �� ����
//            case 1:
//                ui.LoadAddresses();
//                break;
//            case 2: {
//                std::string city, street;
//                int building_number;
//                std::cout << "Enter city, street, building number: ";
//                std::getline(std::cin, user_input);
//                std::istringstream ss(user_input);
//                //�� ������� ����� �� ������� ��������� ��������� ������
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
//        //���� ��� �� ������ ����������� ��������� ��������� - � �����
//        catch (const NotNumberError& e) {
//            //����� ��������� �������
//            log_exception(e);  // ��������� �������
//            std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
//        }
//        catch (const WrongNumberError& e) {
//            //����� ��������� �������
//            log_exception(e);  // ��������� �������
//            std::cerr << "Wrong input format! Caught exception: " << e.what() << "\n";
//        }
//        catch (const NotAddressFormatError& e) {
//            //����� ��������� �������
//            log_exception(e);  // ��������� �������
//            std::cerr << "Wrong data format! Caught exception: " << e.what() << "\n";
//        }
//        catch (const std::exception& e) {
//            //����� ��������� �������
//            log_exception(e);  // ��������� �������
//            std::cerr << "An unexpected error occurred: " << e.what() << "\n";
//        }
//    }
//}
