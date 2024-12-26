#ifndef TEST_FILE_HANDLER_H
#define TEST_FILE_HANDLER_H

class TestFileHandler {
public:
    // Тест 1: Завантаження адрес із існуючого файлу (ПОЗИТИВНИЙ/ВІДНОСИНИ МІЖ КЛАСАМИ FileHandler ТА PrivateHouse, Appartment)
    static void test_load_addresses_valid_file();

    // Тест 2: Завантаження адрес з файлу, якого не існує (НЕГАТИВНИЙ/ВИНЯТКОВИЙ)
    static void test_load_addresses_file_not_found();

    // Тест 3: Завантаження файлу з некоректним форматом (НЕГАТИВНИЙ/ВИНЯТКОВИЙ)
    static void test_load_addresses_invalid_format();

    // Тест 4: Завантаження файлу з некоректними числовими даними (НЕГАТИВНИЙ/ВИНЯТКОВИЙ)
    static void test_load_addresses_invalid_number();

    // Тест 5: Збереження адреси у файл (ПОЗИТИВНИЙ/ВІДНОСИНИ МІЖ КЛАСАМИ FileHandler ТА Address)
    static void test_save_address();

    // Тест 6: Перевірка на граничні значення (ГРАНИЧНИЙ)
    static void test_load_addresses_boundary_values();

    // Функція для запуску всіх тестів
    void run_all_tests();
};

#endif // TEST_FILE_HANDLER_H
