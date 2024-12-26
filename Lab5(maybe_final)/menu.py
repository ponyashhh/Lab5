import unittest
from unittest.mock import patch, mock_open
from address_book import AddressBook
from private_house import PrivateHouse
from appartment import Appartment
from exceptions import NotNumberError, WrongNumberError, NotAddressFormatError
import io
from contextlib import redirect_stdout


class TestAddressBook(unittest.TestCase):
    def setUp(self):
        """Налаштування тестового середовища."""
        self.book = AddressBook()
        self.private_address = PrivateHouse("Kyiv", "Hvosta", 12)
        self.appartment1 = Appartment("Lviv", "Hvylyasta", 1, 22)
        self.appartment2 = Appartment("Odesa", "Jordanskya", 2, 33)

    def test_add_address(self):
        """Перевірка методу додавання адрес."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)
        self.assertEqual(len(self.book.addresses), 2)
        self.assertIs(self.book.addresses[0], self.private_address)

    @patch("sys.stdout")
    def test_display_addresses(self):
        """Перевірка виведення списку адрес."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)

        buffer = io.StringIO()
        with redirect_stdout(buffer):
            self.book.display_addresses()

        output = buffer.getvalue()
        self.assertIn("Kyiv", output)
        self.assertIn("Lviv", output)

    @patch("sys.stdout")
    def test_analyze_addresses(self):
        """Перевірка аналізу адрес."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)
        self.book.selected_indices = [0, 1]

        buffer = io.StringIO()
        with redirect_stdout(buffer):
            self.book.analyze_addresses()

        output = buffer.getvalue()
        self.assertIn("Number of private houses: 1", output)
        self.assertIn("Number of appartments: 1", output)

    @patch("builtins.input", return_value="1 2")
    def test_select_addresses_for_mailing_valid(self, mock_input):
        """Перевірка вибору адрес для розсилки."""
        self.book.add_address(self.private_address)
        self.book.add_address(self.appartment1)
        self.book.select_addresses_for_mailing()
        self.assertEqual(self.book.selected_indices, [0, 1])

    @patch("builtins.input", return_value="3")
    @patch("sys.stderr")
    def test_select_addresses_for_mailing_invalid_number(self, mock_stderr, mock_input):
        """Перевірка некоректного вибору адрес."""
        self.book.add_address(self.private_address)
        self.book.select_addresses_for_mailing()
        error_output = mock_stderr.getvalue()
        self.assertIn("is out of range", error_output)


if __name__ == "__main__":
    unittest.main()
