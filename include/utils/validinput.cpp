#include <iostream>
#include <string>
#include <filesystem>
#include "../../include/utils/validInput.h"

using namespace std;

int validInputMainMenu() {
    while (true) {
        try {
            cout << "Выберите действие:\n";
            cout << "1 - Ввести текст в файл\n";
            cout << "2 - Зашифровать файл\n"; 
            cout << "3 - Расшифровать файл\n";
            cout << "4 - Просмотреть файл\n";
            cout << "0 - Выход\n";
            cout << "Ваш выбор >> ";
            
            string input;
            getline(cin, input);
            
            if (input == "0") return 0;
            if (input == "1") return 1;
            if (input == "2") return 2;
            if (input == "3") return 3;
            if (input == "4") return 4;
            
            cout << "Неверный выбор! Попробуйте снова.\n";
        } catch (...) {
            cout << "Ошибка ввода! Попробуйте снова.\n";
        }
    }
}

int validInputSubMenu() {
    while (true) {
        try {
            cout << "Выберите алгоритм шифрования:\n";
            cout << "1 - Шифр Цезаря\n";
            cout << "2 - Шифр Атбаш\n";
            cout << "3 - Двойная перестановка\n";
            cout << "Ваш выбор >> ";
            
            string input;
            getline(cin, input);
            
            if (input == "1") return 1;
            if (input == "2") return 2;
            if (input == "3") return 3;
            
            cout << "Неверный выбор! Попробуйте снова.\n";
        } catch (...) {
            cout << "Ошибка ввода! Попробуйте снова.\n";
        }
    }
}

int validInputKeyCaesar() {
    while (true) {
        try {
            cout << "Введите ключ для шифра Цезаря (число) >> ";
            string input;
            getline(cin, input);
            return stoi(input);
        } catch (...) {
            cout << "Ошибка: введите целое число!\n";
        }
    }
}

int validInputAction() {
    while (true) {
        cout << "Выберите действие:\n";
        cout << "1 - Шифрование\n";
        cout << "2 - Дешифрование\n";
        cout << "Ваш выбор >> ";
        
        string input;
        getline(cin, input);
        
        if (input == "1") return 1;
        if (input == "2") return 2;
        
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

string validInputKey() {
    string input;
    while (true) {
        cout << "Введите ключ >> ";
        getline(cin, input);
        
        if (!input.empty()) {
            return input;
        }
        cout << "Ошибка: ключ не может быть пустым!\n";
    }
}

string validInputPathFile() {
    string input;
    while (true) {
        cout << "Введите путь к файлу >> ";
        getline(cin, input);
        
        if (filesystem::exists(input)) {
            return input;
        }
        cout << "Ошибка: файл не найден!\n";
    }
}
