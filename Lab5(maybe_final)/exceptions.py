import sys  # для Exception
import os   # для роботи з файлами та шляхами

# Ієрархія винятків
class InputError(Exception):
    def __init__(self, message):
        self.message = message

    def __str__(self):
        return f"InputError: {self.message}"

class NotNumberError(InputError):
    def __str__(self):
        return f"NotNumberError: {self.message}"

class NotAddressFormatError(InputError):
    def __str__(self):
        return f"NotAddressFormatError: {self.message}"

class WrongNumberError(InputError):
    def str(self):
        return f"WrongNumberError: {self.message}"

class FileError(Exception):
    def __init__(self, message):
        self.message = message

    def __str__(self):
        return f"FileError: {self.message}"

class NotFoundFileError(FileError):
    def __str__(self):
        return f"NotFoundFileError: {self.message}"

class FileContentError(FileError):
    def __str__(self):
        return f"FileContentError: {self.message}"

# Логування винятків у файл
def log_exception(exception: Exception):
    # Створюємо шлях до файлу exception_log.txt у поточній директорії скрипта
    log_file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "exception_log.txt")
    
    with open(log_file_path, "a", encoding="utf-8") as file:
        file.write(f"Caught exception: {exception}\n")