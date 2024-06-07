#include <iostream>
#include <string>
#include <windows.h>

typedef bool (*CheckCharactersFunc)(const char*, const char*);
int main() {

    setlocale(LC_ALL, "rus");

    // Запрос у пользователя строки и символов для поиска
    std::string inputString;
    std::string searchChars;

    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);

    std::cout << "Введите символы для поиска: ";
    std::getline(std::cin, searchChars);

    // Загрузка библиотеки
    HMODULE hLib = LoadLibraryA("MyLibrary.dll");  // Используйте LoadLibraryA для узких строк
    if (hLib == nullptr) {
        std::cerr << "Не удалось загрузить библиотеку!" << std::endl;
        return 1;
    }

    // Получение адреса функции
    CheckCharactersFunc CheckCharacters = (CheckCharactersFunc)GetProcAddress(hLib, "CheckCharacters");
    if (CheckCharacters == nullptr) {
        std::cerr << "Не удалось получить адрес функции!" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    // Вызов функции
    bool result = CheckCharacters(inputString.c_str(), searchChars.c_str());

    // Вывод результата
    if (result) {
        std::cout << "Все символы найдены в строке." << std::endl;
    }
    else {
        std::cout << "Не все символы найдены в строке." << std::endl;
    }

    // Освобождение библиотеки
    FreeLibrary(hLib);
    return 0;
}
