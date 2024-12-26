#pragma once
#ifndef UI_H 
#define UI_H

#include "addressBook.h"
#include "Address.h"
#include "FileHandler.h"

class UI {
public:
    UI(AddressBook& address_book, FileHandler& file_handler);

    void LoadAddresses();
    void AddPrivateAddress(const string& city, const string& street, int building_number);
    void AddAppartmentAddress(const string& city, const string& street, int building_number, int appartment_number);
    void AnalyzeAddresses();
    void SelectAddressesForMailing();

private:
    AddressBook& addressBook;
    FileHandler& fileHandler;
};

#endif // UI_H
