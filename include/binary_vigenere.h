#ifndef BINARY_VIGENERE_H
#define BINARY_VIGENERE_H

#include <vector>
#include <string>

class BinaryVigenere {
public:
    static void encrypt(std::vector<unsigned char>& data, const std::string& key);
    static void decrypt(std::vector<unsigned char>& data, const std::string& key);

private:
    static std::string keyToBinary(const std::string& key);
    static void applyBinaryKey(std::vector<unsigned char>& data, const std::string& binaryKey, bool encrypt);
    static std::vector<int> generateKeySchedule(const std::string& key, size_t dataSize);
};

#endif // BINARY_VIGENERE_H