#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>
#include <string>
#include <vector>

#include "cryptoLibs.h"
#include "../libs/double_transposition/dtrans.h"
#include "utils/validInput.h"

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

string identityRowKey(size_t rows) {
    string result;
    for (size_t i = 0; i < rows; ++i)
        result += std::to_string((i % rows) + 1); 
    return result;
}

void getDoubleTransKeys(string& colKey, string& rowKey, bool forFile, size_t fileRows = 0) {
    do {
        cout << "Введите ключ для столбцов (например, 4132): ";
        getline(cin, colKey);
        if (colKey.empty())
            cout << "Ключ не должен быть пустым! Попробуйте снова.\n";
    } while(colKey.empty());

    if (forFile) {
        rowKey = identityRowKey(fileRows);
    } else {
        do {
            cout << "Введите ключ для строк (например, 3142): ";
            getline(cin, rowKey);
            if(rowKey.empty())
                cout << "Ключ не должен быть пустым! Попробуйте снова.\n";
        } while(rowKey.empty());
    }
}

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

void doubleTranspositionFileFunct(const string &filename, int action) {
    if (!fileExists(filename)) {
        cout << "Ошибка чтения файла: " << filename << "\n";
        return;
    }
    string colKey, rowKey;
    string data = readFile(filename);

    do {
        cout << "Введите ключ для столбцов (например, 4132): ";
        getline(cin, colKey);
        if (colKey.empty())
            cout << "Ключ не должен быть пустым! Попробуйте снова.\n";
    } while(colKey.empty());

    size_t cols = colKey.size();
    size_t rows = (data.size() + cols - 1) / cols;
    rowKey = identityRowKey(rows);

    string result = (action == 1 ? doubleTransEncrypt(data, colKey, rowKey)
                                 : doubleTransDecrypt(data, colKey, rowKey));
    writeFile(filename + (action == 1 ? ".enc" : ".dec"), result);
}

void doubleTranspositionTextFunct(const string& inputText, int action) {
    string colKey, rowKey, result;
    getDoubleTransKeys(colKey, rowKey, false);
    result = (action == 1 ? doubleTransEncrypt(inputText, colKey, rowKey)
                          : doubleTransDecrypt(inputText, colKey, rowKey));
    cout << (action == 1 ? "Зашифрованный текст: " : "Расшифрованный текст: ") << result << "\n";
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
                        cout << (action == 1 ? "Зашифрованный текст: " : "Расшифрованный текст: ") << output << "\n";
                        break;
                    case 2: // Atbash (только для текста)
                        output = atbashText(inputText);
                        cout << (action == 1 ? "Зашифрованный текст: " : "Расшифрованный текст: ") << output << "\n";
                        break;
                    case 3:
                        doubleTranspositionTextFunct(inputText, action);
                        break;
                }
                pause();
                break;
            }
            case 2: { 
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
                    case 3:
                        doubleTranspositionFileFunct(filename, action);
                        break;
                }
                pause();
                break;
            }
            case 3: { 
                int cipherChoice = validInputCipher();
                string filename = smartFindFile(validInputFile());
                if (filename.empty()) {
                    cout << "Ошибка: файл не найден ни в текущей директории, ни в test_data/\n";
                    break;
                }
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
                    case 3:
                        doubleTranspositionFileFunct(filename, action);
                        break;
                }
                pause();
                break;
            }
            case 4: { 
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
