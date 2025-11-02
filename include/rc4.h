#ifndef RC4_H
#define RC4_H

#include <vector>
#include <string>

class RC4 {
public:
    static void encrypt(std::vector<unsigned char>& data, const std::string& key);
    static void decrypt(std::vector<unsigned char>& data, const std::string& key);

private:
    static void keySchedulingAlgorithm(std::vector<unsigned char>& S, const std::string& key);
    static void pseudoRandomGenerationAlgorithm(std::vector<unsigned char>& data, 
                                               std::vector<unsigned char>& S);
    static std::vector<unsigned char> generateKeyStream(const std::string& key, size_t length);
};

#endif // RC4_H