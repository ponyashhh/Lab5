#include "addressBook.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <set>
#include <algorithm>

AddressBook::AddressBook() {}

void AddressBook::AddAddress(shared_ptr<Address> address) {
    try {
        if (!address) {
            throw NotAddressFormatError("Invalid address format: Address is null");
        }
        addresses.push_back(address);
    }
    catch (const NotAddressFormatError& e) {
        // removes this fucking coments
        log_exception(e);  // Логування помилки
        cerr << "Caught exception: " << e.what() << endl;  // Виведення повідомлення про помилку
    }
    catch (const exception& e) {
        log_exception(e);  // Логування інших помилок
        cerr << "An unexpected error occurred: " << e.what() << endl;
    }
}

void AddressBook::AnalyzeAddresses() {
    // потрібно напрям прописати модифікатори доступу, класів це також стосується
    int privateHouseCount = 0;
    int appartmentCount = 0;
    std::map<int, int> appartmentDistribution;

    if (selectedIndices.empty()) {
        std::cout << "There are no addresses selected for analysis." << std::endl;
        return;
    }

    for (int index : selectedIndices) {
        if (index >= 0 && index < addresses.size()) {
            const auto& address = addresses[index];
            // хз чи яке таке в плюсах але в шарпах були порівнянян набагто кращі ніж по строці. Можливо є шось типу is або typeof 
            if (address->GetType() == "Private") {
                privateHouseCount++;
            }
            else if (address->GetType() == "Appartment") {
                appartmentCount++;
                //мені вс підсвічує що dynamic_cast писати не обовязково
                int buildingNumber = dynamic_cast<Appartment*>(address.get())->GetBuildingNumber();
                appartmentDistribution[buildingNumber]++;
            }
        }
        else {
            std::cerr << "Warning: Invalid index " << index << " (out of range)" << std::endl;
        }
    }

    int buildingCount = appartmentDistribution.size();
    std::cout << "\nAnalysis Results:" << std::endl;
    std::cout << "Number of private houses: " << privateHouseCount << std::endl;
    std::cout << "Number of appartments: " << appartmentCount << std::endl;
    std::cout << "Number of unique buildings: " << buildingCount << std::endl;

    if (buildingCount > 0) {
        //аналогічно static_cast
        double averageAppartments = static_cast<double>(appartmentCount) / buildingCount;
        std::cout << "Average number of appartments per building: " << averageAppartments << std::endl;
        for (const auto& pair : appartmentDistribution) {
            std::cout << "Building " << pair.first << ": " << pair.second << " appartments" << std::endl;
        }
    }
    else if (appartmentCount > 0) {
        std::cout << "Warning: Apartments found but building numbers could not be determined." << std::endl;
    }
}

void AddressBook::DisplayAddresses() const {
    for (size_t i = 0; i < addresses.size(); i++) {
        //в плюсах не можна в строку додатвати текст типу "Hello {value} Word"?, якщо можна то краще робити так
        std::cout << i + 1 << ": " << addresses[i]->toString() << std::endl;
    }
}


void AddressBook::SelectAddressesForMailing() {

    DisplayAddresses();
    string inputStr;
    cout << "Enter the numbers of the addresses (separated by spaces) for mailing: ";
    getline(cin, inputStr);

    selectedIndices.clear();
    istringstream iss(inputStr);
    string numStr;
    set<int> duplicatesChecker;

    while (iss >> numStr) {
        try {
            //прибрати коментарі
            // !all_of(numStr.begin(), numStr.end(), ::isdigit) оцю фігню можна в окремий метод винести щоб було зрозуміло що тут відбувається
            // Перевірка, чи є введене значення числом
            if (!all_of(numStr.begin(), numStr.end(), ::isdigit)) {
                throw NotNumberError("Input contains non-integer values - " + numStr + ". Please enter valid integer numbers.");
            }

            int number = stoi(numStr) - 1;
            //зауваження аналогічні
            // Перевірка, чи введений індекс у межах допустимих значень
            if (number < 0 || number >= static_cast<int>(addresses.size())) {
                throw WrongNumberError("Number " + numStr + " is out of range. Please select valid addresses.");
            }

            selectedIndices.push_back(number);
            //тут пробіл не потрібний
        }
        catch (const NotNumberError& e) {
            log_exception(e);
            cerr << "Caught exception: " << e.what() << endl;

        }
        catch (const WrongNumberError& e) {
            log_exception(e);
            cerr << "Caught exception: " << e.what() << endl;

        }
        catch (const exception& e) {
            log_exception(e);
            cerr << "An unexpected error occurred: " << e.what() << endl;
        }
    }

    //це все ще одна функція? фігня повна - розбити

    // Перевірка дублікатів
    duplicatesChecker.insert(selectedIndices.begin(), selectedIndices.end());
    if (duplicatesChecker.size() != selectedIndices.size()) {
        cout << "Warning: There are duplicate indices in your selection." << endl;
        cout << "Enter 'R' to re-enter values or 'A' to automatically remove duplicates: ";
        char choice;
        cin >> choice;
        choice = toupper(choice);
        //що таке R і A - це якийсь вибір але мені просто по букві не зрозуміло - винести в enum
        if (choice == 'R') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter the addresses again." << endl;
            //коментар
            SelectAddressesForMailing();  // Рекурсивний виклик
            return;
        }
        else if (choice == 'A') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            selectedIndices.assign(duplicatesChecker.begin(), duplicatesChecker.end());
            cout << "Duplicates have been automatically removed." << endl;
        }
        else {
            cout << "Invalid choice. No action taken." << endl;
        }
    }

    // Підсумковий результат
    if (!selectedIndices.empty()) {
        cout << "You have selected addresses with numbers: ";
        for (int index : selectedIndices) {
            cout << index + 1 << " ";
        }
        cout << endl;
    }
    else {
        cout << "No addresses have been selected." << endl;
    }
}

//додати усюди явно модифікатори доступу
void AddressBook::ClearAddresses() {
    addresses.clear();
}

// Геттер для `addresses` - повертає список адрес
const std::vector<std::shared_ptr<Address>>& AddressBook::GetAddresses() const {
    return addresses;
}

// Геттер для `selectedIndices` - повертає список обраних індексів
const std::vector<int>& AddressBook::GetSelectedIndices() const {
    return selectedIndices;
}
