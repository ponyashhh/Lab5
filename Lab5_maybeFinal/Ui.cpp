#include "UI.h"
#include "addressBook.h"
#include "FileHandler.h"
#include "PrivateHouse.h"
#include "Appartment.h"
#include <iostream>
#include "Exceptions.h"  // Для використання винятків
#include <algorithm>

UI::UI(AddressBook& addressBook, FileHandler& fileHandler)
    : addressBook(addressBook), fileHandler(fileHandler) {}

void UI::LoadAddresses() {
    //ух сюка, прапорки це хуйня повна, уникаємо як тільки можемо
    bool success = false; // Прапорець для відстеження успішного виконання 

    try {
        // Очищуємо список адрес перед новим завантаженням, щоб уникнути дублювання
        addressBook.ClearAddresses();

        // Завантажуємо адреси з файлу
        auto addresses = fileHandler.LoadAddresses();
        for (const auto& address : addresses) {
            addressBook.AddAddress(address);
        }

        success = true; // Якщо все пройшло успішно, встановлюємо прапорець
    }
    //методи знизу - дублювання
    catch (const NotFoundFileError& e) {
        log_exception(e); // Логування помилки
        std::cerr << "Error loading addresses from file! Caught exception: " << e.what() << std::endl;
    }
    catch (const FileContentError& e) {
        log_exception(e); // Логування помилки 
        std::cerr << "File content error! Caught exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        log_exception(e); // Логування помилки
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }
    //ставлю очевидності цього коментаря 11 з 10
    // Виводимо повідомлення про успішне завантаження лише у випадку, якщо помилки не було
    if (success) {
        std::cout << "Addresses loaded successfully. Here is the list of addresses:" << std::endl;
        //ладно, цей коментар ще більш очевидний, якшо юзаєш гпт то хоч коментарі прибирай
        addressBook.DisplayAddresses(); // Виводимо список адрес після завантаження
    }
}

void UI::AddPrivateAddress(const std::string& city, const std::string& street, int buildingNumber) {

    try {
        //цим не повинний займатися цей метод
        // Перевірка формату міста та вулиці
        if (city.empty() || street.empty() ||
            !std::all_of(city.begin(), city.end(), ::isalpha) ||
            !std::all_of(street.begin(), street.end(), ::isalpha)) {
            throw NotAddressFormatError("City and street must be strings containing only alphabetic characters.");
        }

        // Додавання адреси
        auto address = std::make_shared<PrivateHouse>(city, street, buildingNumber);
        addressBook.AddAddress(address);
        fileHandler.SaveAddress(*address);

        std::cout << "Address successfully added: " << address->toString() << std::endl;

    }
    //ЄБАТЬ
    catch (const NotAddressFormatError& e) {
        log_exception(e); // Логування помилки
        std::cerr << "Wrong data format! Caught exception: " << e.what() << std::endl;

    }
    catch (const std::exception& e) {
        log_exception(e); // Логування помилки
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

}

void UI::AddAppartmentAddress(const std::string& city, const std::string& street, int buildingNumber, int appartmentNumber) {
    try {
        //цим не повинний займатися цей метод
        // Перевірка формату міста та вулиці
        if (city.empty() || street.empty() ||
            !std::all_of(city.begin(), city.end(), ::isalpha) ||
            !std::all_of(street.begin(), street.end(), ::isalpha)) {
            throw NotAddressFormatError("City and street must be strings containing only alphabetic characters.");
        }

        // Додавання адреси, якщо перевірка пройшла успішно
        auto address = std::make_shared<Appartment>(city, street, buildingNumber, appartmentNumber);
        addressBook.AddAddress(address);
        fileHandler.SaveAddress(*address);

        std::cout << "Address successfully added: " << address->toString() << std::endl;

    }
    //ЄБАТЬ х2
    catch (const NotAddressFormatError& e) {
        log_exception(e); // Логування помилки
        std::cerr << "Wrong data format! Caught exception: " << e.what() << std::endl;

    }
    catch (const std::exception& e) {
        log_exception(e); // Логування помилки
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

}

void UI::AnalyzeAddresses() {
    addressBook.AnalyzeAddresses();
}

void UI::SelectAddressesForMailing() {
    addressBook.SelectAddressesForMailing();
}
