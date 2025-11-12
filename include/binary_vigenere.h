#ifndef BINARY_VIGENERE_H
#define BINARY_VIGENERE_H

#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

void binary_vigenere_encrypt(std::vector<unsigned char>& data, const std::string& key);
void binary_vigenere_decrypt(std::vector<unsigned char>& data, const std::string& key);

#ifdef __cplusplus
}
#endif

#endif