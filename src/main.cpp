#include <iostream>
#include <fstream>
#include <filesystem>  
#include <limits>      
#include <string>
#include <vector>
#include "cryptoLibs.h"

using namespace std;

void pause() {
cout << "Нажмите Enter, чтобы продолжить...";
cin.ignore();
}

bool fileExists(const string &path) {
return filesystem::exists(path);
}
string smartFindFile(const string& filename) {
    if (filesystem::exists(filename))
        return filename;
    string alt = "test_data/" + filename;
    if (filesystem::exists(alt))
        return alt;
    return "";
}

string readFile(const string &filename) {
ifstream infile(filename, ios::binary);
return string((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
}

void writeFile(const string &filename, const string &data) {
ofstream outfile(filename, ios::binary);
outfile.write(data.data(), data.size());
cout << "Готово. Результат сохранён в " << filename << "\n";
}

int validInputMainMenu() {
int choice;
while (true) {
cout << "\nГлавное меню:\n1. Ввести текст\n2. Зашифровать файл\n3. Расшифровать файл\n4. Просмотреть файл\n0. Выход\nВаш выбор: ";
if (cin >> choice && choice >= 0 && choice <= 4) {
cin.ignore();
return choice;
}
cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Неверный выбор! Попробуйте снова.\n";
}
}

int validInputCipher() {
int choice;
while (true) {
cout << "\nВыберите алгоритм:\n1. Caesar\n2. Atbash\n3. Double Transposition\nВаш выбор: ";
if (cin >> choice && choice >= 1 && choice <= 3) {
cin.ignore();
return choice;
}
cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Неверный выбор! Попробуйте снова.\n";
}
}

int validInputAction() {
int choice;
while (true) {
cout << "Выберите действие:\n1. Шифровать\n2. Дешифровать\nВаш выбор: ";
if (cin >> choice && (choice == 1 || choice == 2)) {
cin.ignore();
return choice;
}
cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
string key;
cout << "Введите ключ шифрования: ";
getline(cin, key);
return key;
}

string validInputFile() {
string filename;
cout << "Введите имя файла: ";
getline(cin, filename);
return filename;
}

// Функции для файлов
void codeCaesar(const string &filename, int shift, int action) {
if (!fileExists(filename)) {
cout << "Ошибка чтения файла: " << filename << "\n";
return;
}
string data = readFile(filename);
string result = (action == 1 ? caesarEncrypt(data, shift) : caesarDecrypt(data, shift));
writeFile(filename + (action == 1 ? ".enc" : ".dec"), result);
}

void atbashAsciiFunct(const string &filename, int action) {
if (!fileExists(filename)) {
cout << "Ошибка чтения файла: " << filename << "\n";
return;
}
string data = readFile(filename);
string result = atbashAll(data);
writeFile(filename + (action == 1 ? ".enc" : ".dec"), result);
}

void doubleTranspositionFunct(const string &filename, const string &key, int action) {
if (!fileExists(filename)) {
cout << "Ошибка чтения файла: " << filename << "\n";
return;
}
string data = readFile(filename);
string result = (action == 1 ? doubleTranspositionEncrypt(data, key) : doubleTranspositionDecrypt(data, key));
writeFile(filename + (action == 1 ? ".enc" : ".dec"), result);
}

int main() {
bool running = true;

while (running) {
    int mainChoice = validInputMainMenu();
    switch (mainChoice) {
        case 0:
            running = false;
            cout << "Выход из программы. До свидания!\n";
            break;
        case 1: { 
            int cipherChoice = validInputCipher();
            string inputText, output, key;
            cout << "Введите текст: ";
            getline(cin, inputText);
            int action = validInputAction();
            switch (cipherChoice) {
                case 1: 
                    key = to_string(validInputShift());
                    output = (action == 1 ? caesarEncrypt(inputText, stoi(key)) : caesarDecrypt(inputText, stoi(key)));
                    break;
                case 2: 
                    output = atbashAll(inputText);
                    break;
                case 3: 
                    key = validInputKey();
                    output = (action == 1 ? doubleTranspositionEncrypt(inputText, key) : doubleTranspositionDecrypt(inputText, key));
                    break;
            }
            cout << (action == 1 ? "Зашифрованный текст: " : "Расшифрованный текст: ") << output << "\n";
            pause();
            break;
        }
        case 2: { // Шифровать файл
            int cipherChoice = validInputCipher();
            string filename = smartFindFile(validInputFile());
            if (filename.empty()) {
                cout << "Ошибка: файл не найден ни в текущей директории, ни в test_data/\n";
                break;
            }
            int action = 1;
            switch (cipherChoice) {
                case 1: {
                    int shift = validInputShift();
                    codeCaesar(filename, shift, action);
                    break;
                }
                case 2:
                    atbashAsciiFunct(filename, action);
                    break;
                case 3: {
                    string key = validInputKey();
                    doubleTranspositionFunct(filename, key, action);
                    break;
                }
            }
            pause();
            break;
        }
        case 3: { // Дешифровать файл
            int cipherChoice = validInputCipher();
            string filename = validInputFile();
            int action = 2;
            switch (cipherChoice) {
                case 1: {
                    int shift = validInputShift();
                    codeCaesar(filename, shift, action);
                    break;
                }
                case 2:
                    atbashAsciiFunct(filename, action);
                    break;
                case 3: {
                    string key = validInputKey();
                    doubleTranspositionFunct(filename, key, action);
                    break;
                }
            }
            pause();
            break;
        }
        case 4: { // Просмотр файла
            string filename = validInputFile();
            if (!fileExists(filename)) {
                cout << "Ошибка чтения файла: " << filename << "\n";
                break;
            }
            string data = readFile(filename);
            cout << "Содержимое файла " << filename << ": " << data << "\n";
            pause();
            break;
        }
    }
}
return 0;
}
