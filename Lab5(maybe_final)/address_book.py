from typing import List, Dict
from address import Address
from private_house import PrivateHouse
from appartment import Appartment
import sys  # для Exception
from exceptions import NotAddressFormatError, log_exception, NotNumberError, WrongNumberError


class AddressBook:
    def __init__(self):
        self.addresses: List[Address] = []      # список адрес
        self.selected_indices: List[int] = []   # індекси вибраних адрес для розсилки

    def add_address(self, address: Address):
        try:
            self.addresses.append(address)
        except NotAddressFormatError as e:
            log_exception(e)  # Логування помилки
            print(f"Caught exception: {e}", file=sys.stderr)
            raise

            
    def analyze_addresses(self):
        private_house_count = 0
        appartment_count = 0
        appartment_distribution: Dict[int, int] = {}

        if not self.selected_indices:
            print("There are no addresses selected for analysis.")
            return

        # Обробляємо вибрані адреси
        for index in self.selected_indices:
            address = self.addresses[index]
            if address.get_type() == "Private":
                private_house_count += 1
            elif address.get_type() == "Appartment":
                appartment_count += 1
                building_number = address.building_number
                if building_number in appartment_distribution:
                    appartment_distribution[building_number] += 1
                else:
                    appartment_distribution[building_number] = 1

        building_count = len(appartment_distribution)
        print("\nAnalysis Results:")
        print(f"Number of private houses: {private_house_count}")
        print(f"Number of appartments: {appartment_count}")
        print(f"Number of unique buildings: {building_count}")
        if building_count > 0:
            average_appartments = appartment_count / building_count
            print(f"Average number of appartments per building: {average_appartments:.2f}")
            for building, count in appartment_distribution.items():
                print(f"Building {building}: {count} appartments")

    def display_addresses(self):
        for idx, address in enumerate(self.addresses, start=1):
            print(f"{idx}: {address.to_string()}")

    def select_addresses_for_mailing(self):
        # Дозволяє користувачу обрати адреси для розсилки
        self.display_addresses()
        input_str = input("Enter the numbers of the addresses (separated by spaces) for mailing:  ")
        selected_numbers = input_str.split()

        self.selected_indices.clear()
        for num_str in selected_numbers:
            try:
                # Перевірка, чи введене значення є цілим числом
                if not num_str.isdigit():
                    raise NotNumberError(f"Input contains non-integer values - {num_str}. Please enter valid integer numbers.")

                number = int(num_str) - 1
                # Перевірка, чи введений індекс знаходиться в межах доступних адрес
                if not (0 <= number < len(self.addresses)):
                    raise WrongNumberError(f"Number {num_str} is out of range. Please select valid addresses.")

                self.selected_indices.append(number)

            except NotNumberError as e:
                log_exception(e)  # Логування помилки
                print(f"Caught exception: {e}", file=sys.stderr)

            except WrongNumberError as e:
                log_exception(e)  # Логування помилки
                print(f"Caught exception: {e}", file=sys.stderr)

            except Exception as e:
                log_exception(e)  # Логування помилки
                print(f"An unexpected error occurred: {e}", file=sys.stderr)
            
            # Перевірка наявності дублікатів у списку
        if len(self.selected_indices) != len(set(self.selected_indices)):
            print("Warning: There are duplicate indices in your selection.")
            user_choice = input("Enter 'R' to re-enter values or 'A' to automatically remove duplicates: ").strip().upper()

            if user_choice == 'R':
                print("Please enter the addresses again.")
                self.select_addresses_for_mailing()  # Рекурсивний виклик для повторного введення
            elif user_choice == 'A':
                # Видалення дублікатів за допомогою перетворення у множину
                self.selected_indices = list(set(self.selected_indices))
                print("Duplicates have been automatically removed.")
            else:
                print("Invalid choice. No action taken.")

        if self.selected_indices:
            print("You have selected addresses with numbers:", ", ".join(str(i + 1) for i in self.selected_indices))
        else:
            print("No addresses have been selected.")
