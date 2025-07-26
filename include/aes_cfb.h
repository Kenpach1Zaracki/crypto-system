#ifndef AES_CFB_H
#define AES_CFB_H

#include <vector>
#include <string>
#include <cstdint>

class AES_CFB {
private:
    static const int AES_BLOCK_SIZE = 16;
    static const int AES_KEY_SIZE = 16; // 128-bit key
    static const int Nb = 4; // Number of columns (32-bit words) in State
    static const int Nk = 4; // Number of 32-bit words in key
    static const int Nr = 10; // Number of rounds

    // AES S-box
    static const uint8_t sbox[256];
    static const uint8_t inv_sbox[256];
    
    // Round constants
    static const uint8_t Rcon[11];

    // AES core functions
    static void KeyExpansion(const uint8_t* key, uint32_t* w);
    static void AddRoundKey(uint8_t* state, const uint32_t* roundKey);
    static void SubBytes(uint8_t* state);
    static void ShiftRows(uint8_t* state);
    static void MixColumns(uint8_t* state);
    static void AES_Encrypt(const uint8_t* plaintext, uint8_t* ciphertext, const uint32_t* roundKeys);
    
    // Utility functions
    static uint8_t xtime(uint8_t x);
    static uint8_t multiply(uint8_t x, uint8_t y);
    static std::vector<uint8_t> deriveKey(const std::string& password);
    static std::vector<uint8_t> generateIV();

public:
    static void encrypt(std::vector<unsigned char>& data, const std::string& password);
    static void decrypt(std::vector<unsigned char>& data, const std::string& password);
};

#endif // AES_CFB_H
