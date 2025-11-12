#ifndef AES_CFB_H
#define AES_CFB_H

#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

void aes_cfb_encrypt(std::vector<unsigned char>& data, const std::string& key);
void aes_cfb_decrypt(std::vector<unsigned char>& data, const std::string& key);

#ifdef __cplusplus
}
#endif

#endif