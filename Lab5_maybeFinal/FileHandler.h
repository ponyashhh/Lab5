#pragma once
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include "Address.h"
#include "PrivateHouse.h"
#include "Appartment.h"
class UI; // Пряме оголошення для уникнення циклічного включення 

class FileHandler {
public:
    FileHandler(const string& filename);

    std::vector<std::shared_ptr<Address>> LoadAddresses();
    std::vector<std::shared_ptr<Address>> _parseFile(std::ifstream& file);
    void SaveAddress(const Address& address);

    friend UI;

private:
    string filename;
};

#endif // FILEHANDLER_H
