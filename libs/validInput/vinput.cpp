#include <iostream>
#include <string>
#include <limits>

using namespace std;

int validInputMainMenu() {
    int choice;
    while (true) {
        cout << "\nГлавное меню:\n"
             << "1. Ввести текст\n"
             << "2. Зашифровать файл\n"
             << "3. Расшифровать файл\n"
             << "4. Просмотреть файл\n"
             << "0. Выход\n"
             << "Ваш выбор: ";

        if (cin >> choice && choice >= 0 && choice <= 4) {
            cin.ignore();
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

int validInputCipher() {
    int choice;
    while (true) {
        cout << "\nВыберите алгоритм:\n"
             << "1. Caesar\n"
             << "2. Atbash\n"
             << "3. Double Transposition\n"
             << "Ваш выбор: ";

        if (cin >> choice && choice >= 1 && choice <= 3) {
            cin.ignore();
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

int validInputAction() {
    int choice;
    while (true) {
        cout << "Выберите действие:\n"
             << "1. Шифровать\n"
             << "2. Дешифровать\n"
             << "Ваш выбор: ";

        if (cin >> choice && (choice == 1 || choice == 2)) {
            cin.ignore();
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

int validInputShift() {
    int shift;
    cout << "Введите ключ шифрования (число): ";
    cin >> shift;
    cin.ignore();
    return shift;
}

string validInputKey() {
    cout << "Введите ключ шифрования: ";
    string key;
    getline(cin, key);
    return key;
}

string validInputFile() {
    cout << "Введите имя файла: ";
    string filename;
    getline(cin, filename);
    return filename;
}
