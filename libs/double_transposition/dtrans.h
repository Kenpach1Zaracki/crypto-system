#pragma once
#include <string>
#include <vector>

std::string doubleTransEncrypt(const std::string& text, const std::string& colKey, const std::string& rowKey);
std::string doubleTransDecrypt(const std::string& cipher, const std::string& colKey, const std::string& rowKey);
