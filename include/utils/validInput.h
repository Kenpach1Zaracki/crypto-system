#pragma once
#include <string>

int validInputMainMenu();    // 0 - выход, 1 - обработка файла
int validInputSubMenu();     // 1 - Caesar, 2 - Atbash, 3 - Double Transposition
int validInputAction();      // 1 - encrypt, 2 - decrypt
int validInputKeyCaesar();   // возвращает int
std::string validInputKey(); // для Double Transposition
std::string validInputPathFile();
