#include "crypto_system.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

// CLI-режим
int cliMode(int argc, char* argv[]) {
    string cipher = getArg(argc, argv, "--cipher");
    bool encrypt = hasFlag(argc, argv, "-e") || hasFlag(argc, argv, "--encrypt");
    bool decrypt = hasFlag(argc, argv, "-d") || hasFlag(argc, argv, "--decrypt");
    string input = getArg(argc, argv, "--input");
    string output = getArg(argc, argv, "--output");
    string key = getArg(argc, argv, "--key");
    string iv = getArg(argc, argv, "--iv"); // опционально для AES

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

    if (cipher == "rc4") {
        if (encrypt) system.rc4Encrypt(data, key);
        if (decrypt) system.rc4Decrypt(data, key);
    } else if (cipher == "aes") {
        if (encrypt) system.aesCfbEncrypt(data, key); // IV можно добавить при необходимости
        if (decrypt) system.aesCfbDecrypt(data, key);
    } else if (cipher == "binvig" || cipher == "binary_vigenere") {
        if (encrypt) system.binaryVigenereEncrypt(data, key);
        if (decrypt) system.binaryVigenereDecrypt(data, key);
    } else {
        cout << "Неизвестный алгоритм: " << cipher << endl;
        return 3;
    }

    system.writeBinaryFile(output, data);
    cout << "Готово. Результат сохранён в " << output << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    setlocale (LC_ALL, "");
    // --- CLI-режим если есть параметры ---
    if (argc > 1) {
        return cliMode(argc, argv);
    }

    // --- Интерактивный режим (оригинальный код) ---
    CryptoSystem system;
    int choice;
    
    do {
        system.showMenu();
        
        // ИСПРАВЛЯЕМ ВВОД
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }
        cin.ignore(); // Очищаем буфер после числа
        
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
            case 5:
                system.createTestFiles();
                break;
            case 0:
                cout << "\n👋 Выход из программы. До свидания!" << endl;
                break;
            default:
                cout << "\n⚠️  Неверный выбор! Попробуйте снова." << endl;
                cout << "📄 Нажмите Enter для продолжения...";
                cin.get();
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}