#ifndef TEST_FILE_HANDLER_H
#define TEST_FILE_HANDLER_H

class TestFileHandler {
public:
    // ���� 1: ������������ ����� �� ��������� ����� (����������/²������� ̲� ������� FileHandler �� PrivateHouse, Appartment)
    static void test_load_addresses_valid_file();

    // ���� 2: ������������ ����� � �����, ����� �� ���� (����������/����������)
    static void test_load_addresses_file_not_found();

    // ���� 3: ������������ ����� � ����������� �������� (����������/����������)
    static void test_load_addresses_invalid_format();

    // ���� 4: ������������ ����� � ������������ ��������� ������ (����������/����������)
    static void test_load_addresses_invalid_number();

    // ���� 5: ���������� ������ � ���� (����������/²������� ̲� ������� FileHandler �� Address)
    static void test_save_address();

    // ���� 6: �������� �� ������� �������� (���������)
    static void test_load_addresses_boundary_values();

    // ������� ��� ������� ��� �����
    void run_all_tests();
};

#endif // TEST_FILE_HANDLER_H
