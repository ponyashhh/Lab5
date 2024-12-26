import sys
from file_handler import FileHandler
from address_book import AddressBook
from appartment import Appartment
from private_house import PrivateHouse
from exceptions import NotFoundFileError, log_exception, FileContentError, NotAddressFormatError

class UI:
    def __init__(self, address_book: AddressBook, file_handler: FileHandler):
        self.address_book = address_book
        self.file_handler = file_handler

    def load_addresses(self):
        try: 
            # Очищуємо список адрес перед новим завантаженням, щоб уникнути дублювання
            self.address_book.addresses.clear()

            # Завантажуємо адреси з файлу та додаємо їх до книги адрес
            addresses = self.file_handler.load_addresses()
            for address in addresses:
                self.address_book.add_address(address)

            print("Addresses loaded successfully. Here is the list of addresses:")
            self.address_book.display_addresses()  # Виводимо список адрес після завантаження

        except NotFoundFileError as e:
            log_exception(e)  # Логування помилки
            print(f"Error loading addresses from file! Caught exception: {e}", file=sys.stderr)

        except FileContentError as e:
            log_exception(e)  # Логування помилки
            print(f"File content error! Caught exception: {e}")

        except Exception as e:
            log_exception(e)  # Логування помилки
            print(f"An unexpected error occurred: {e}", file=sys.stderr)

    def add_private_address(self, city, street, building_number):
        try:
            # Перевірка формату міста та вулиці
            if not (isinstance(city, str) and city.isalpha() and isinstance(street, str) and street.isalpha()):
                raise NotAddressFormatError("City and street must be strings containing only alphabetic characters.")

            # Приведення building_number до int (оскільки тут очікуємо, що перевірка відбулася у меню)
            building_number = int(building_number)

            # Додавання адреси
            address = PrivateHouse(city, street, building_number)
            self.address_book.add_address(address)
            self.file_handler.save_address(address)
            print(f"Address successfully added: {address.to_string()}")

        except NotAddressFormatError as e:
            log_exception(e)  # Логування помилки
            print(f"Wrong data format! Caught exception: {e}", file=sys.stderr)

        except Exception as e:
            log_exception(e)  # Логування помилки
            print(f"An unexpected error occurred: {e}", file=sys.stderr)

    def add_appartment_address(self, city, street, building_number, appartment_number):
        try:
            if not (isinstance(city, str) and city.isalpha() and isinstance(street, str) and street.isalpha()):
                raise NotAddressFormatError("City and street must be strings containing only alphabetic characters.")

            # Приведення building_number до int (оскільки тут очікуємо, що перевірка відбулася у меню)
            building_number = int(building_number)
            # Приведення appartment_number до int (оскільки тут очікуємо, що перевірка відбулася у меню)
            appartment_number = int(appartment_number)

            # Додавання адреси, якщо перевірка пройшла
            address = Appartment(city, street, building_number, appartment_number)
            self.address_book.add_address(address)
            self.file_handler.save_address(address)
            print(f"Address successfully added: {address.to_string()}")

        except NotAddressFormatError as e:
            log_exception(e)  # Логування помилки
            print(f"Wrong data format! Caught exception: {e}", file=sys.stderr)

        except Exception as e:
            log_exception(e)  # Логування помилки
            print(f"An unexpected error occurred: {e}", file=sys.stderr)

    def analyze_addresses(self):
        self.address_book.analyze_addresses()

    def select_addresses_for_mailing(self):
        if not self.address_book.addresses:
            print("Loading...")
            addresses = self.file_handler.load_addresses()
            for address in addresses:
                self.address_book.add_address(address)
                
        self.address_book.select_addresses_for_mailing()
