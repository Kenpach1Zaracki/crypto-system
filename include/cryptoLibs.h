#pragma once
#include <string>

// Caesar
std::string caesarEncrypt(const std::string& data, int shift);
std::string caesarDecrypt(const std::string& data, int shift);

// Atbash
std::string atbashAll(const std::string& data);

// Double Transposition
std::string doubleTranspositionEncrypt(const std::string& data, const std::string& key);
std::string doubleTranspositionDecrypt(const std::string& data, const std::string& key);
