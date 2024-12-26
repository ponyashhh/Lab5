import unittest
from unittest.mock import mock_open, patch
from exceptions import NotFoundFileError, FileContentError
from address import Address
from appartment import Appartment
from private_house import PrivateHouse
from file_handler import FileHandler
import tempfile
import os

# C:\Users\User\Documents\Беляш\VS_code\Lab5
# python -m unittest TestFileHandler.py -v 

class TestFileHandler(unittest.TestCase):

    # Тест 1: Завантаження адрес із існуючого файлу
    def test_load_addresses_valid_file(self):
        # Тестові дані
        mock_file_content = "Private: Kyiv Khreshchatyk 10\nAppartment: Lviv Shevchenka 5 12\n"
        
        # Використовуємо mock_open для імітації відкриття файлу
        with patch("builtins.open", mock_open(read_data=mock_file_content)):
            file_handler = FileHandler(r"C:\Users\User\Documents\Беляш\VS_code\Lab5(maybe_final)\addresses.txt")  # використовуємо сировий рядок
            addresses = file_handler.load_addresses()
            
            self.assertEqual(len(addresses), 2)
            self.assertIsInstance(addresses[0], PrivateHouse)
            self.assertIsInstance(addresses[1], Appartment)

    # Тест 2: Завантаження адрес з файлу, якого не існує
    def test_load_addresses_file_not_found(self):
        with self.assertRaises(NotFoundFileError):
            file_handler = FileHandler(r"C:\Users\User\Documents\Беляш\VS_code\Lab5(maybe_final)\non_existent_file.txt")  # Вказуємо коректний шлях
            file_handler.load_addresses()

    # Тест 3: Завантаження файлу з некоректним форматом
    def test_load_addresses_invalid_format(self):
        mock_file_content = "Private: Kyiv Khreshchatyk 10\nInvalidLineWithoutColon\n"
        
        with patch("builtins.open", mock_open(read_data=mock_file_content)):
            file_handler = FileHandler(r"C:\Users\User\Documents\Беляш\VS_code\Lab5(maybe_final)\addresses.txt")
            with self.assertRaises(FileContentError):
                file_handler.load_addresses()

    # Тест 4: Завантаження файлу з некоректними числовими даними
    def test_load_addresses_invalid_number(self):
        mock_file_content = "Private: Kyiv Khreshchatyk ABC\n"
        
        with patch("builtins.open", mock_open(read_data=mock_file_content)):
            file_handler = FileHandler(r"C:\Users\User\Documents\Беляш\VS_code\Lab5(maybe_final)\addresses.txt")
            with self.assertRaises(FileContentError):
                file_handler.load_addresses()

    # Тест 5: Збереження адреси у файл
    def test_save_address(self):
        # Створення тестової адреси
        address = PrivateHouse("Kyiv", "Khreshchatyk", 10)

        # Використовуємо mock_open для перевірки запису у файл
        with patch("builtins.open", mock_open()) as mock_file:
            file_handler = FileHandler(r"C:\Users\User\Documents\Беляш\VS_code\Lab5(maybe_final)\addresses.txt")
            file_handler.save_address(address)
            
            # Перевіряємо, що файл відкривається з кодуванням 'windows-1251'
            mock_file.assert_called_once_with(r"C:\Users\User\Documents\Беляш\VS_code\Lab5(maybe_final)\addresses.txt", "a", encoding="utf-8")
            mock_file().write.assert_called_once_with(address.to_string() + '\n')
    
    # Тест 6: Граничні значення 
    def test_load_addresses_boundary_values(self):
        # Створення тимчасового файлу для тесту
        with tempfile.NamedTemporaryFile(delete=False, mode='w', encoding="utf-8") as temp_file:
            temp_filename = temp_file.name
            # Запис даних з граничними значеннями для тесту
            temp_file.write(f"Private: Kyiv Khreshchatyk {str(-2**31)}\n")  # Мінімальне значення int (-2147483648)
            temp_file.write(f"Private: Lviv Shevchenka {str(2**31-1)}\n")  # Максимальне значення int (2147483647)
            temp_file.write("Private: Odesa Pushkina 0\n")  # Нульове значення

        # Тепер завантажуємо адреси з цього тимчасового файлу
        file_handler = FileHandler(temp_filename)
        addresses = file_handler.load_addresses()

        # Перевірка кількості адрес
        self.assertEqual(len(addresses), 3)

        # Перевірка типу всіх адрес
        for address in addresses:
            self.assertIsInstance(address, PrivateHouse)

        # Перевірка значень адрес
        self.assertEqual(addresses[0].building_number, -2**31)
        self.assertEqual(addresses[1].building_number, 2**31-1)
        self.assertEqual(addresses[2].building_number, 0)

        # Видаляємо тимчасовий файл після тесту
        os.remove(temp_filename)

if __name__ == "__main__":
    unittest.main()
