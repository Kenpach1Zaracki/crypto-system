#pragma once
#include <string>

std::string doubleTransEncrypt(const std::string& data, const std::string& colKey, const std::string& rowKey);
std::string doubleTransDecrypt(const std::string& data, const std::string& colKey, const std::string& rowKey);