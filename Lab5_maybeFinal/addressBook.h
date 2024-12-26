#pragma once
#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <vector>
#include <memory>
#include <string>
#include "Address.h"
#include "Appartment.h"
#include "PrivateHouse.h"

class UI; // ����� ���������� ��� ��������� ��������� ���������

class AddressBook {
public:

    AddressBook();

    void AddAddress(shared_ptr<Address> address);
    void AnalyzeAddresses();
    void DisplayAddresses() const;
    void SelectAddressesForMailing();
    void ClearAddresses();
    friend UI;

    //// ����� ��� ��������� �����
    //const std::vector<std::shared_ptr<Address>>& getAddresses() const {
    //    return addresses;
    //}

    //// ����� ��� ������������ ������� selectedIndices
    //void setSelectedIndices(const std::vector<int>& indices) {
    //    selectedIndices = indices;
    //}

    //// ����� ��� ��������� ������� �������� �����
    //std::vector<int> getSelectedIndices() const {
    //    return selectedIndices;
    //}

    const std::vector<std::shared_ptr<Address>>& GetAddresses() const;
    const std::vector<int>& GetSelectedIndices() const;


private:
    vector<shared_ptr<Address>> addresses;
    vector<int> selectedIndices;
};

#endif // ADDRESSBOOK_H
