import unittest
from unittest.mock import patch, MagicMock
from address_book import AddressBook
from private_house import PrivateHouse
from appartment import Appartment
from exceptions import NotNumberError, WrongNumberError
import io


class TestAddressBook(unittest.TestCase):
    def setUp(self):
        """Set up test environment before each test."""
        self.book = AddressBook()
        self.private_address = PrivateHouse("Kyiv", "Hvosta", 12)
        self.appartment1 = Appartment("Lviv", "Hvylyasta", 1, 22)
        self.appartment2 = Appartment("Odesa", "Jordanskya", 2, 33)

    def test_add_address(self):     # ПОЗИТИВНИЙ/ВІДНОШЕННЯ - взаємодія AddressBook із класами PrivateHouse та Appartment.
        """Test adding addresses to the address book."""
        self.book.add_address(self.private_address)
        self.assertEqual(len(self.book.addresses), 1)
        self.assertIs(self.book.addresses[0], self.private_address)

        self.book.add_address(self.appartment1)
        self.assertEqual(len(self.book.addresses), 2)
        self.assertIs(self.book.addresses[1], self.appartment1)

    @patch('sys.stdout', new_callable=io.StringIO)
    def test_display_addresses(self, mock_stdout):      # ПОЗИТИВНИЙ
        """Test displaying addresses."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)
        
        self.book.display_addresses()
        output = mock_stdout.getvalue()
        
        self.assertIn("Kyiv", output)
        self.assertIn("Hvosta", output)
        self.assertIn("Lviv", output)
        self.assertIn("Hvylyasta", output)

    def test_analyze_addresses_empty(self):     # ГРАНИЧНИЙ
        """Test analyzing addresses when no addresses are selected."""
        with patch('sys.stdout', new_callable=io.StringIO) as mock_stdout:
            self.book.analyze_addresses()
            self.assertIn("There are no addresses selected for analysis.", mock_stdout.getvalue())

    def test_analyze_addresses_with_data(self):     # ПОЗИТИВНИЙ/ВІДНОШЕННЯ - робота з даними різних класів 
        """Test analyzing addresses with selected addresses."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)
        self.book.add_address(self.appartment2)
        self.book.selected_indices = [0, 1, 2]

        with patch('sys.stdout', new_callable=io.StringIO) as mock_stdout:
            self.book.analyze_addresses()
            output = mock_stdout.getvalue()
            
            self.assertIn("Number of private houses: 1", output)
            self.assertIn("Number of appartments: 2", output)
            self.assertIn("Number of unique buildings: 2", output)

    @patch('builtins.input', side_effect=["1 2"])  # Автоматично вводимо номери 1 і 2
    def test_select_addresses_for_mailing_valid(self, mock_input):      # ПОЗИТИВНИЙ
        """Test selecting valid addresses for mailing."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)

        self.book.select_addresses_for_mailing()
        self.assertEqual(self.book.selected_indices, [0, 1])

    @patch('builtins.input', side_effect=["1 1", "A"])  # Дублікати та вибір "A" для видалення дублікатив
    def test_select_addresses_duplicates(self, mock_input):     # ГРАНИЧНИЙ
        """Test handling duplicate selections."""
        self.book.add_address(self.private_address)

        self.book.select_addresses_for_mailing()
        self.assertEqual(self.book.selected_indices, [0])  # Дублікати мають бути видалені

    @patch('builtins.input', side_effect=["99"])  # Введення невалідного індексу
    def test_select_addresses_out_of_range(self, mock_input):       # НЕГАТИВНИЙ/ГРАНИЧНИЙ/ВИНЯТКОВИЙ
        """Test handling out of range input when selecting addresses."""
        self.book.add_address(self.private_address)

        with patch('sys.stderr', new=io.StringIO()) as fake_stderr:
            self.book.select_addresses_for_mailing()
            self.assertIn("is out of range", fake_stderr.getvalue())

    @patch('builtins.input', side_effect=["abc"])  # Невалідний ввід, наприклад "abc"
    def test_select_addresses_invalid_input(self, mock_input):      # НЕГАТИВНИЙ/ВИНЯТКОВИЙ
        """Test handling invalid input when selecting addresses."""
        self.book.add_address(self.private_address)

        with patch('sys.stderr', new=io.StringIO()) as fake_stderr:
            self.book.select_addresses_for_mailing()
            self.assertIn("Input contains non-integer values", fake_stderr.getvalue())

if __name__ == '__main__':
    unittest.main()
