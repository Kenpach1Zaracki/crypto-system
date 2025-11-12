#ifndef RC4_H
#define RC4_H

#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

void rc4_encrypt(std::vector<unsigned char>& data, const std::string& key);
void rc4_decrypt(std::vector<unsigned char>& data, const std::string& key);

#ifdef __cplusplus
}
#endif

#endif