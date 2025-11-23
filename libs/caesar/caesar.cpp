#include "cryptoLibs.h"

std::string caesarEncrypt(const std::string& data, int shift) {
std::string result = data;
for (size_t i = 0; i < result.size(); ++i)
result[i] = static_cast<char>((static_cast<unsigned char>(result[i]) + shift) % 256);
return result;
}

std::string caesarDecrypt(const std::string& data, int shift) {
std::string result = data;
for (size_t i = 0; i < result.size(); ++i)
result[i] = static_cast<char>((static_cast<unsigned char>(result[i]) - shift + 256) % 256);
return result;
}
