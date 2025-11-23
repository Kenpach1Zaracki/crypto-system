#pragma once
#include <string>
void codeCaesarFile(const std::string& inFile, const std::string& outFile, int choice, int shift);
std::string caesarEncrypt(const std::string& text, int shift);
std::string caesarDecrypt(const std::string& text, int shift);
