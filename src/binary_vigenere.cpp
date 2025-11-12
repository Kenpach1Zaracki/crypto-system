#include "../include/binary_vigenere.h"
#include <vector>
#include <string>

using namespace std;

// Вспомогательные функции
static string keyToBinary(const string& key) {
    string binaryKey;
    for (char c : key) {
        for (int i = 7; i >= 0; --i) {
            binaryKey += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return binaryKey;
}

// Экспортируемые функции
extern "C" {
    void binary_vigenere_encrypt(vector<unsigned char>& data, const string& key) {
        if (data.empty() || key.empty()) return;
        string binaryKey = keyToBinary(key);

        for (size_t i = 0; i < data.size(); ++i) {
            unsigned char result = 0;
            for (int bit = 0; bit < 8; ++bit) {
                size_t keyIndex = (i * 8 + bit) % binaryKey.length();
                int dataBit = (data[i] >> bit) & 1;
                int keyBit = (binaryKey[keyIndex] == '1') ? 1 : 0;
                int encryptedBit = dataBit ^ keyBit;
                result |= (encryptedBit << bit);
            }
            data[i] = result;
        }
    }

    void binary_vigenere_decrypt(vector<unsigned char>& data, const string& key) {
        binary_vigenere_encrypt(data, key); // Симметричное к XOR
    }
}