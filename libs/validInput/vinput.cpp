#include <iostream>
#include <string>
#include <filesystem>
#include "../../include/utils/validInput.h"

namespace fs = std::filesystem;
using namespace std;

int validInputMainMenu() {
    while (true) {
        cout << "Выберите действие:\n";
        cout << "1 - Ввести текст\n";
        cout << "2 - Зашифровать файл\n"; 
        cout << "3 - Расшифровать файл\n";
        cout << "4 - Просмотреть файл\n";
        cout << "0 - Выход\nВаш выбор >> ";
        string input;
        getline(cin, input);
        if (input == "0") return 0;
        if (input == "1") return 1;
        if (input == "2") return 2;
        if (input == "3") return 3;
        if (input == "4") return 4;
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

int validInputSubMenu() {
    while (true) {
        cout << "Выберите алгоритм шифрования:\n";
        cout << "1 - Шифр Цезаря\n";
        cout << "2 - Шифр Атбаш\n";
        cout << "3 - Двойная перестановка\nВаш выбор >> ";
        string input;
        getline(cin, input);
        if (input == "1") return 1;
        if (input == "2") return 2;
        if (input == "3") return 3;
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

int validInputKeyCaesar() {
    while (true) {
        cout << "Введите ключ для шифра Цезаря (число) >> ";
        string input;
        getline(cin, input);
        try { return stoi(input); } 
        catch (...) { cout << "Ошибка: введите целое число!\n"; }
    }
}

int validInputAction() {
    while (true) {
        cout << "Выберите действие:\n1 - Шифрование\n2 - Дешифрование\nВаш выбор >> ";
        string input;
        getline(cin, input);
        if (input == "1") return 1;
        if (input == "2") return 2;
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

std::string validInputKey() {
    while (true) {
        cout << "Введите ключ >> ";
        string input;
        getline(cin, input);
        if (!input.empty()) return input;
        cout << "Ошибка: ключ не может быть пустым!\n";
    }
}

std::string validInputPathFile() {
    while (true) {
        cout << "Введите путь к файлу >> ";
        string input;
        getline(cin, input);
        if (fs::exists(input)) return input;
        cout << "Ошибка: файл не найден!\n";
    }
}
