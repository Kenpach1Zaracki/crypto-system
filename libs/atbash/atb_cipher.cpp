#include "../include/cryptoLibs.h"

std::string atbashAll(const std::string& data) {
std::string result = data;
for (size_t i = 0; i < result.size(); ++i)
result[i] = static_cast<char>(255 - static_cast<unsigned char>(result[i]));
return result;
}
