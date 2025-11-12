#include "crypto_system.h"
#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h>

using namespace std;

// Типы указателей на функции из библиотек
typedef void (*CryptoFunc)(vector<unsigned char>&, const string&);

// --- CLI helpers ---
string getArg(int argc, char* argv[], const string& name) {
    for (int i = 1; i < argc - 1; ++i) {
        if (argv[i] == name)
            return argv[i + 1];
    }
    return "";
}

bool hasFlag(int argc, char* argv[], const string& flag) {
    for (int i = 1; i < argc; ++i) if (argv[i] == flag) return true;
    return false;
}

// CLI-режим с динамической загрузкой
int cliMode(int argc, char* argv[]) {
    string cipher = getArg(argc, argv, "--cipher");
    bool encrypt = hasFlag(argc, argv, "-e") || hasFlag(argc, argv, "--encrypt");
    bool decrypt = hasFlag(argc, argv, "-d") || hasFlag(argc, argv, "--decrypt");
    string input = getArg(argc, argv, "--input");
    string output = getArg(argc, argv, "--output");
    string key = getArg(argc, argv, "--key");

    if (cipher.empty() || input.empty() || output.empty() || key.empty() || (!encrypt && !decrypt)) {
        cout << "Недостаточно параметров.\n";
        cout << "Пример:\n./crypto_app --cipher rc4 -e --input input.txt --output enc.dat --key secret\n";
        cout << "Алгоритмы: rc4, aes, binvig\n";
        cout << "Флаги: -e (encrypt), -d (decrypt)\n";
        return 1;
    }

    CryptoSystem system;
    vector<unsigned char> data = system.readBinaryFile(input);
    if (data.empty()) {
        cout << "Ошибка чтения файла: " << input << endl;
        return 2;
    }

    // Определяем библиотеку и функцию
    const char* libPath = nullptr;
    const char* funcName = nullptr;
    
    if (cipher == "rc4") {
        libPath = "./lib/librc4.so";
        funcName = encrypt ? "rc4_encrypt" : "rc4_decrypt";
    } else if (cipher == "aes") {
        libPath = "./lib/libaes.so";
        funcName = encrypt ? "aes_cfb_encrypt" : "aes_cfb_decrypt";
    } else if (cipher == "binvig" || cipher == "binary_vigenere") {
        libPath = "./lib/libbinvig.so";
        funcName = encrypt ? "binary_vigenere_encrypt" : "binary_vigenere_decrypt";
    } else {
        cout << "Неизвестный алгоритм: " << cipher << endl;
        return 3;
    }

    // Загрузка библиотеки
    void* handle = dlopen(libPath, RTLD_LAZY);
    if (!handle) {
        cerr << "Ошибка загрузки библиотеки " << libPath << ": " << dlerror() << endl;
        return 4;
    }

    // Получение указателя на функцию
    CryptoFunc cryptoFunc = (CryptoFunc)dlsym(handle, funcName);
    if (!cryptoFunc) {
        cerr << "Ошибка получения функции " << funcName << ": " << dlerror() << endl;
        dlclose(handle);
        return 5;
    }

    // Вызов функции шифрования/дешифрования
    cryptoFunc(data, key);

    // Выгрузка библиотеки
    dlclose(handle);

    system.writeBinaryFile(output, data);
    cout << "Готово. Результат сохранён в " << output << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    
    if (argc > 1) {
        return cliMode(argc, argv);
    }

    // Интерактивный режим
    CryptoSystem system;
    int choice;
    
    do {
        system.showMenu();
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }
        cin.ignore();
        
        switch (choice) {
            case 1:
                system.inputTextToFile();
                break;
            case 2:
                system.encryptFile();
                break;
            case 3:
                system.decryptFile();
                break;
            case 4:
                system.displayFile();
                break;
            case 0:
                cout << "\nВыход из программы. До свидания!" << endl;
                break;
            default:
                cout << "\n⚠️  Неверный выбор! Попробуйте снова." << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.get();
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}