import os
from typing import List
from address import Address
from appartment import Appartment
from private_house import PrivateHouse
from exceptions import NotFoundFileError, FileContentError


class FileHandler:
    def __init__(self, filename: str):
        self.filename = filename

    def load_addresses(self) -> List[Address]:
        addresses = []
        if not os.path.exists(self.filename):
            raise NotFoundFileError(f"File not found: {self.filename}")
        
        try:
            with open(self.filename, "r", encoding="utf-8") as file:
                addresses = self._parse_file(file)
                
        except UnicodeDecodeError:
            print("Warning: UTF-8 decoding failed, trying Windows-1251...")
            with open(self.filename, "r", encoding="windows-1251") as file:
                addresses = self._parse_file(file)
        return addresses

    def _parse_file(self, file) -> List[Address]:
        addresses = []
        line_number = 0

        for line in file:
            line_number += 1
            parts = line.strip().split(":")

            if len(parts) != 2:
                raise FileContentError(f"Line {line_number}: Incorrect format (missing ':' separator)")
            
            address_type = parts[0].strip()
            address_data = parts[1].strip().split()

            try:
                if address_type == "Private" and len(address_data) == 3:
                    city, street, building_number = address_data
                    address = PrivateHouse(city, street, int(building_number))
                    addresses.append(address)
                elif address_type == "Appartment" and len(address_data) == 4:
                    city, street, building_number, appartment_number = address_data
                    address = Appartment(city, street, int(building_number), int(appartment_number))
                    addresses.append(address)
                else:
                    raise FileContentError(
                        f"Line {line_number}: Incorrect data for {address_type} (expected 3 or 4 values)"
                    )
            except ValueError:
                raise FileContentError(
                    f"Line {line_number}: Building or appartment number is not an integer"
                )
        return addresses

    def save_address(self, address: Address):
        with open(self.filename, 'a', encoding="utf-8") as file:
            file.write(address.to_string() + '\n')
