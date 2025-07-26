#ifndef CRYPTO_SYSTEM_H
#define CRYPTO_SYSTEM_H

#include <vector>
#include <string>
#include "rc4.h"
#include "aes_cfb.h"
#include "binary_vigenere.h"

class CryptoSystem {
public:
    enum Algorithm { RC4 = 1, AES_CFB = 2, BINARY_VIGENERE = 3 };

    void showMenu();
    void inputTextToFile();
    void encryptFile();
    void decryptFile();
    void displayFile();
    void createTestFiles();

    // Низкоуровневые алгоритмы
    void rc4Encrypt(std::vector<unsigned char>& data, const std::string& key);
    void rc4Decrypt(std::vector<unsigned char>& data, const std::string& key);

    void aesCfbEncrypt(std::vector<unsigned char>& data, const std::string& key);
    void aesCfbDecrypt(std::vector<unsigned char>& data, const std::string& key);

    void binaryVigenereEncrypt(std::vector<unsigned char>& data, const std::string& key);
    void binaryVigenereDecrypt(std::vector<unsigned char>& data, const std::string& key);

    std::vector<unsigned char> readBinaryFile(const std::string& filename);
    void writeBinaryFile(const std::string& filename, const std::vector<unsigned char>& data);

    std::string getPassword();
    std::string getFilename();
    std::string getFilename(const std::string& prompt);
    std::string chooseFileFromDirectory(const std::string& prompt);
    int chooseAlgorithm();
    void clearScreen();

    // Методы для работы с мультимедиа
    std::string getFileType(const std::string& filename);
    std::string getFileIcon(const std::string& filename);
    void showFileInfo(const std::string& filename);
    bool isImageFile(const std::string& filename);
    bool isAudioFile(const std::string& filename);
    bool isVideoFile(const std::string& filename);
    bool isTextFile(const std::string& filename);
    
    // Создание мультимедиа тестов
    void createTestImage();
    void createTestAudio();
    void createTestVideo();
    void createLargeTextFile();
};

#endif // CRYPTO_SYSTEM_H