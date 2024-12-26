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
#include <C:/Users/User/Documents/Беляш/vs/Lab5_maybeFinal/Lab5_maybeFinal/addressBook.h> 
#include "PrivateHouse.h"
#include "Appartment.h"
#include "Exceptions.h"

class TestAddressBook {
public:
    // Тест 1: Додавання адреси (ПОЗИТИВНИЙ ТЕСТ)
    static void test_add_address();

    // Тест 2: Відображення адрес (ПОЗИТИВНИЙ ТЕСТ)
    static void test_display_addresses();

    // Тест 3: Аналіз порожнього списку адрес (НЕГАТИВНИЙ ТЕСТ)
    static void test_analyze_addresses_empty();

    // Тест 4: Аналіз адрес із даними (ПОЗИТИВНИЙ ТЕСТ)
    static void test_analyze_addresses_with_data();

    // Тест 5: Вибір валідних адрес для розсилки (ПОЗИТИВНИЙ ТЕСТ)
    static void test_select_addresses_for_mailing_valid();

    // Тест 6: Обробка дублікатів під час вибору (НЕГАТИВНИЙ ТЕСТ)
    static void test_select_addresses_duplicates();

    // Тест 7: Обробка виходу за межі діапазону (НЕГАТИВНИЙ ТЕСТ)
    static void test_select_addresses_out_of_range();

    // Тест 8: Обробка некоректного вводу (НЕГАТИВНИЙ ТЕСТ)
    static void test_select_addresses_invalid_input();

    // Запуск усіх тестів
    static void run_all_tests();
};

#endif // TEST_ADDRESS_BOOK_H
