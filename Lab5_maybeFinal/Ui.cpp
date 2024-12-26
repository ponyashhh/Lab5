#include "UI.h"
#include "addressBook.h"
#include "FileHandler.h"
#include "PrivateHouse.h"
#include "Appartment.h"
#include <iostream>
#include "Exceptions.h"  // ��� ������������ �������
#include <algorithm>

UI::UI(AddressBook& addressBook, FileHandler& fileHandler)
    : addressBook(addressBook), fileHandler(fileHandler) {}

void UI::LoadAddresses() {
    //�� ����, �������� �� ����� �����, ������� �� ����� ������
    bool success = false; // ��������� ��� ���������� �������� ��������� 

    try {
        // ������� ������ ����� ����� ����� �������������, ��� �������� ����������
        addressBook.ClearAddresses();

        // ����������� ������ � �����
        auto addresses = fileHandler.LoadAddresses();
        for (const auto& address : addresses) {
            addressBook.AddAddress(address);
        }

        success = true; // ���� ��� ������� ������, ������������ ���������
    }
    //������ ����� - ����������
    catch (const NotFoundFileError& e) {
        log_exception(e); // ��������� �������
        std::cerr << "Error loading addresses from file! Caught exception: " << e.what() << std::endl;
    }
    catch (const FileContentError& e) {
        log_exception(e); // ��������� ������� 
        std::cerr << "File content error! Caught exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        log_exception(e); // ��������� �������
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }
    //������ ���������� ����� ��������� 11 � 10
    // �������� ����������� ��� ������ ������������ ���� � �������, ���� ������� �� ����
    if (success) {
        std::cout << "Addresses loaded successfully. Here is the list of addresses:" << std::endl;
        //�����, ��� �������� �� ���� ���������, ���� ���� ��� �� ��� �������� ��������
        addressBook.DisplayAddresses(); // �������� ������ ����� ���� ������������
    }
}

void UI::AddPrivateAddress(const std::string& city, const std::string& street, int buildingNumber) {

    try {
        //��� �� �������� ��������� ��� �����
        // �������� ������� ���� �� ������
        if (city.empty() || street.empty() ||
            !std::all_of(city.begin(), city.end(), ::isalpha) ||
            !std::all_of(street.begin(), street.end(), ::isalpha)) {
            throw NotAddressFormatError("City and street must be strings containing only alphabetic characters.");
        }

        // ��������� ������
        auto address = std::make_shared<PrivateHouse>(city, street, buildingNumber);
        addressBook.AddAddress(address);
        fileHandler.SaveAddress(*address);

        std::cout << "Address successfully added: " << address->toString() << std::endl;

    }
    //�����
    catch (const NotAddressFormatError& e) {
        log_exception(e); // ��������� �������
        std::cerr << "Wrong data format! Caught exception: " << e.what() << std::endl;

    }
    catch (const std::exception& e) {
        log_exception(e); // ��������� �������
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

}

void UI::AddAppartmentAddress(const std::string& city, const std::string& street, int buildingNumber, int appartmentNumber) {
    try {
        //��� �� �������� ��������� ��� �����
        // �������� ������� ���� �� ������
        if (city.empty() || street.empty() ||
            !std::all_of(city.begin(), city.end(), ::isalpha) ||
            !std::all_of(street.begin(), street.end(), ::isalpha)) {
            throw NotAddressFormatError("City and street must be strings containing only alphabetic characters.");
        }

        // ��������� ������, ���� �������� ������� ������
        auto address = std::make_shared<Appartment>(city, street, buildingNumber, appartmentNumber);
        addressBook.AddAddress(address);
        fileHandler.SaveAddress(*address);

        std::cout << "Address successfully added: " << address->toString() << std::endl;

    }
    //����� �2
    catch (const NotAddressFormatError& e) {
        log_exception(e); // ��������� �������
        std::cerr << "Wrong data format! Caught exception: " << e.what() << std::endl;

    }
    catch (const std::exception& e) {
        log_exception(e); // ��������� �������
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

}

void UI::AnalyzeAddresses() {
    addressBook.AnalyzeAddresses();
}

void UI::SelectAddressesForMailing() {
    addressBook.SelectAddressesForMailing();
}
