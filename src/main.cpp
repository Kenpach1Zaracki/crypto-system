#include "crypto_system.h"
#include <iostream>

using namespace std;

int main() {
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