#ifndef TEST_ADDRESS_BOOK_H
#define TEST_ADDRESS_BOOK_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <exception>
#include <stdexcept>
#include <C:/Users/User/Documents/�����/vs/Lab5_maybeFinal/Lab5_maybeFinal/addressBook.h> 
#include "PrivateHouse.h"
#include "Appartment.h"
#include "Exceptions.h"

class TestAddressBook {
public:
    // ���� 1: ��������� ������ (���������� ����)
    static void test_add_address();

    // ���� 2: ³���������� ����� (���������� ����)
    static void test_display_addresses();

    // ���� 3: ����� ���������� ������ ����� (���������� ����)
    static void test_analyze_addresses_empty();

    // ���� 4: ����� ����� �� ������ (���������� ����)
    static void test_analyze_addresses_with_data();

    // ���� 5: ���� ������� ����� ��� �������� (���������� ����)
    static void test_select_addresses_for_mailing_valid();

    // ���� 6: ������� �������� �� ��� ������ (���������� ����)
    static void test_select_addresses_duplicates();

    // ���� 7: ������� ������ �� ��� �������� (���������� ����)
    static void test_select_addresses_out_of_range();

    // ���� 8: ������� ������������ ����� (���������� ����)
    static void test_select_addresses_invalid_input();

    // ������ ��� �����
    static void run_all_tests();
};

#endif // TEST_ADDRESS_BOOK_H
