#include "rc4.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// Вспомогательные функции (internal)
static void keySchedulingAlgorithm(vector<unsigned char>& S, const string& key) {
    for (int i = 0; i < 256; ++i) {
        S[i] = static_cast<unsigned char>(i);
    }
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + static_cast<unsigned char>(key[i % key.length()])) % 256;
        swap(S[i], S[j]);
    }
}

static void pseudoRandomGenerationAlgorithm(vector<unsigned char>& data, vector<unsigned char>& S) {
    int i = 0, j = 0;
    for (size_t k = 0; k < data.size(); ++k) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        unsigned char keyByte = S[(S[i] + S[j]) % 256];
        data[k] ^= keyByte;
    }
}

// Экспортируемые функции
extern "C" {
    void rc4_encrypt(vector<unsigned char>& data, const string& key) {
        if (data.empty() || key.empty()) return;
        vector<unsigned char> S(256);
        keySchedulingAlgorithm(S, key);
        pseudoRandomGenerationAlgorithm(data, S);
    }

    void rc4_decrypt(vector<unsigned char>& data, const string& key) {
        rc4_encrypt(data, key); // RC4 симметричен
    }
}
