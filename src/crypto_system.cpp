#include "crypto_system.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

void CryptoSystem::showMenu() {
    clearScreen();
    cout << "Криптографическая система\n";
    cout << "1. Ввести текст в файл\n";
    cout << "2. Зашифровать файл\n";
    cout << "3. Расшифровать файл\n";
    cout << "4. Просмотреть файл\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

void CryptoSystem::inputTextToFile() {
    clearScreen();
    cout << "Введите имя файла для записи текста: ";
    string filename;
    getline(cin, filename);
    cout << "Введите текст для записи (для завершения введите пустую строку):\n";
    ofstream fout(filename, ios::binary);
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        fout << line << "\n";
    }
    fout.close();
    cout << "Текст записан в файл " << filename << endl;
    cout << "Нажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CryptoSystem::encryptFile() {
    clearScreen();
    string filename = getFilename("Введите имя файла для шифрования: ");
    vector<unsigned char> data = readBinaryFile(filename);

    int algo = chooseAlgorithm();
    string key = getPassword();

    switch (algo) {
        case 1: rc4Encrypt(data, key); break;
        case 2: aesCfbEncrypt(data, key); break;
        case 3: binaryVigenereEncrypt(data, key); break;
        default: cout << "Неверный выбор алгоритма!" << endl; return;
    }

    string outname = filename + ".encrypted";
    writeBinaryFile(outname, data);
    cout << "Файл зашифрован: " << outname << endl;
    cout << "Нажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CryptoSystem::decryptFile() {
    clearScreen();
    string filename = getFilename("Введите имя файла для расшифровки: ");
    vector<unsigned char> data = readBinaryFile(filename);

    int algo = chooseAlgorithm();
    string key = getPassword();

    switch (algo) {
        case 1: rc4Decrypt(data, key); break;
        case 2: aesCfbDecrypt(data, key); break;
        case 3: binaryVigenereDecrypt(data, key); break;
        default: cout << "Неверный выбор алгоритма!" << endl; return;
    }

    string outname = filename + ".decrypted";
    writeBinaryFile(outname, data);
    cout << "Файл расшифрован: " << outname << endl;
    cout << "Нажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CryptoSystem::displayFile() {
    clearScreen();
    string filename = getFilename("Введите имя файла для просмотра: ");
    vector<unsigned char> data = readBinaryFile(filename);

    cout << "Содержимое файла " << filename << ":\n";
    for (unsigned char c : data) {
        cout << c;
    }
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Алгоритмы
void CryptoSystem::rc4Encrypt(vector<unsigned char>& data, const string& key) {
    RC4::encrypt(data, key);
}
void CryptoSystem::rc4Decrypt(vector<unsigned char>& data, const string& key) {
    RC4::decrypt(data, key);
}
void CryptoSystem::aesCfbEncrypt(vector<unsigned char>& data, const string& key) {
    AES_CFB::encrypt(data, key);
}
void CryptoSystem::aesCfbDecrypt(vector<unsigned char>& data, const string& key) {
    AES_CFB::decrypt(data, key);
}
void CryptoSystem::binaryVigenereEncrypt(vector<unsigned char>& data, const string& key) {
    BinaryVigenere::encrypt(data, key);
}
void CryptoSystem::binaryVigenereDecrypt(vector<unsigned char>& data, const string& key) {
    BinaryVigenere::decrypt(data, key);
}

// Вспомогательные методы
string CryptoSystem::getPassword() {
    cout << "Введите ключ шифрования: ";
    string key;
    getline(cin, key);
    return key;
}

string CryptoSystem::getFilename(const string& prompt) {
    cout << prompt;
    string filename;
    getline(cin, filename);
    return filename;
}

int CryptoSystem::chooseAlgorithm() {
    cout << "\nВыберите алгоритм:\n"
         << "1. RC4\n"
         << "2. AES-128 CFB\n"
         << "3. Бинарный Виженер\n"
         << "Ваш выбор: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

vector<unsigned char> CryptoSystem::readBinaryFile(const string& filename) {
    ifstream fin(filename, ios::binary);
    vector<unsigned char> data((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    return data;
}

void CryptoSystem::writeBinaryFile(const string& filename, const vector<unsigned char>& data) {
    ofstream fout(filename, ios::binary);
    fout.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void CryptoSystem::clearScreen() {
    cout << endl;
}