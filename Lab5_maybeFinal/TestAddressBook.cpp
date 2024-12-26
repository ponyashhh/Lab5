#include "TestAddressBook.h"
#include "addressBook.h" 

void TestAddressBook::test_add_address() {
    AddressBook book;
    std::shared_ptr<Address> privateHouse = std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12);

    book.AddAddress(privateHouse);

    if (book.GetAddresses().size() == 1 && book.GetAddresses()[0] == privateHouse) {
        std::cout << "Test passed: Address added correctly.\n";
    }
    else {
        std::cerr << "Test failed: Address not added.\n";
    }
}

void TestAddressBook::test_display_addresses() {
    AddressBook book;
    std::shared_ptr<Address> privateHouse = std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12);
    std::shared_ptr<Address> appartment = std::make_shared<Appartment>("Lviv", "Hvylyasta", 1, 22);

    book.AddAddress(privateHouse);
    book.AddAddress(appartment);

    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    book.DisplayAddresses();

    std::cout.rdbuf(originalCoutBuffer);

    std::string result = output.str();
    if (result.find("Kyiv") != std::string::npos && result.find("Lviv") != std::string::npos) {
        std::cout << "Test passed: Addresses displayed correctly.\n";
    }
    else {
        std::cerr << "Test failed: Addresses not displayed correctly.\n";
    }
}

void TestAddressBook::test_analyze_addresses_empty() {
    AddressBook book;
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    book.AnalyzeAddresses();

    std::cout.rdbuf(originalCoutBuffer);

    if (output.str().find("There are no addresses selected for analysis.") != std::string::npos) {
        std::cout << "Test passed: Empty address analysis handled correctly.\n";
    }
    else {
        std::cerr << "Test failed: Empty address analysis not handled correctly.\n";
    }
}

void TestAddressBook::test_analyze_addresses_with_data() {
    AddressBook book;
    book.AddAddress(std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12));
    book.AddAddress(std::make_shared<Appartment>("Lviv", "Hvylyasta", 1, 22));
    book.AddAddress(std::make_shared<Appartment>("Odesa", "Jordanskya", 2, 33));

    // �������� ��� �����������: ���� ������� 1, 2 �� 3
    std::istringstream input("1 2 3\n");
    std::cin.rdbuf(input.rdbuf()); // ��������������� std::cin

    // ��������������� ���� � �����
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // ��������� �������, ��� ����� ����� �� �����������
    book.SelectAddressesForMailing();

    // �������� ����� ������
    book.AnalyzeAddresses();

    // ³��������� ����������� ����
    std::cout.rdbuf(originalCoutBuffer);

    // �������� ���������
    std::string result = output.str();

    // ��������, �� �������� ���������� ������
    if (result.find("Number of private houses: 1") != std::string::npos &&
        result.find("Number of appartments: 2") != std::string::npos &&
        result.find("Number of unique buildings: 2") != std::string::npos) {
        std::cout << "Test passed: Address analysis with data handled correctly.\n";
    }
    else {
        std::cerr << "Test failed: Address analysis with data not handled correctly.\n";
    }

    // ³��������� ����������� ���
    std::cin.rdbuf(std::cin.rdbuf());
}

void TestAddressBook::test_select_addresses_for_mailing_valid() {
    AddressBook book;
    book.AddAddress(std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12));
    book.AddAddress(std::make_shared<Appartment>("Lviv", "Hvylyasta", 1, 22));

    // �������� ��� �����������: ���� ������� 1 �� 2
    std::istringstream input("1 2");
    std::cin.rdbuf(input.rdbuf()); // ��������������� std::cin

    // ��������������� ���� � �����
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // ��������� �������, ��� ����� ����� �� �����������
    book.SelectAddressesForMailing();

    // ³��������� ����������� ����
    std::cout.rdbuf(originalCoutBuffer);

    // �������� ���������
    if (book.GetSelectedIndices() == std::vector<int>{0, 1}) {
        std::cout << "Test passed: Valid address selection handled correctly.\n";
    }
    else {
        std::cerr << "Test failed: Valid address selection not handled correctly.\n";
    }

    // ³��������� ����������� ���
    std::cin.rdbuf(std::cin.rdbuf());
}



void TestAddressBook::test_select_addresses_duplicates() {
    AddressBook book;
    book.AddAddress(std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12));

    // Simulate user input with duplicates and 'A' choice to auto-remove duplicates
    std::istringstream input("1 1\nA\n");
    std::cin.rdbuf(input.rdbuf());

    // Capture console output
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Capture error output
    std::ostringstream errorOutput;
    std::streambuf* originalCerrBuffer = std::cerr.rdbuf();
    std::cerr.rdbuf(errorOutput.rdbuf());

    book.SelectAddressesForMailing();

    // Restore original buffers
    std::cout.rdbuf(originalCoutBuffer);
    std::cerr.rdbuf(originalCerrBuffer);

    auto selectedIndices = book.GetSelectedIndices();
    if (selectedIndices == std::vector<int>{0}) {
        std::cout << "Test passed: Duplicate address selection handled correctly.\n";
    }
    else {
        std::cerr << "Test failed: Duplicate address selection not handled correctly.\n";
    }
}

void TestAddressBook::test_select_addresses_out_of_range() {
    AddressBook book;
    book.AddAddress(std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12));

    // �������� ��� �����������: ������ 99 (���� ���� ���������)
    std::istringstream input("99");
    std::cin.rdbuf(input.rdbuf()); // ��������������� std::cin

    // ��������������� ������ ����� �� ������
    std::ostringstream output;
    std::ostringstream errorOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::streambuf* originalCerrBuffer = std::cerr.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    std::cerr.rdbuf(errorOutput.rdbuf());

    // ��������� �������, ��� ����� ����� �� �����������
    book.SelectAddressesForMailing();

    // ³��������� ��������� ������
    std::cout.rdbuf(originalCoutBuffer);
    std::cerr.rdbuf(originalCerrBuffer);

    // ����������, �� � � ����� ����������� ��� ������� "is out of range"
    if (errorOutput.str().find("is out of range") != std::string::npos) {
        std::cout << "Test passed: Out of range index handled correctly.\n";
    }
    else {
        std::cerr << "Test failed: Out of range index not handled correctly.\n";
    }

    // ³��������� ����������� ���
    std::cin.rdbuf(std::cin.rdbuf());
}

void TestAddressBook::test_select_addresses_invalid_input() {
    AddressBook book;
    book.AddAddress(std::make_shared<PrivateHouse>("Kyiv", "Hvosta", 12));

    // �������� ��� �����������: ����������� ��� "abc"
    std::istringstream input("abc");
    std::cin.rdbuf(input.rdbuf()); // ��������������� std::cin

    // ��������������� ������ ����� �� ������
    std::ostringstream output;
    std::ostringstream errorOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::streambuf* originalCerrBuffer = std::cerr.rdbuf();
    std::cout.rdbuf(output.rdbuf());  // ��������������� std::cout
    std::cerr.rdbuf(errorOutput.rdbuf()); // ��������������� std::cerr

    // ��������� �������, ��� ����� ����� �� �����������
    book.SelectAddressesForMailing();

    // ³��������� ��������� ������
    std::cout.rdbuf(originalCoutBuffer);
    std::cerr.rdbuf(originalCerrBuffer);

    // ����������, �� � � ����� ����������� ��� ����������� ���
    if (errorOutput.str().find("Input contains non-integer values") != std::string::npos) {
        std::cout << "Test passed: Invalid input handled correctly.\n";
    }
    else {
        std::cerr << "Test failed: Invalid input not handled correctly.\n";
    }

    // ³��������� ����������� ���
    std::cin.rdbuf(std::cin.rdbuf());
}

void TestAddressBook::run_all_tests() {
    test_add_address();
    test_display_addresses();
    test_analyze_addresses_empty();
    test_analyze_addresses_with_data();
    test_select_addresses_for_mailing_valid();
    test_select_addresses_duplicates();
    test_select_addresses_out_of_range();
    test_select_addresses_invalid_input();
}
