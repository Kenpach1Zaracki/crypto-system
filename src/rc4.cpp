#include "../include/rc4.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void RC4::encrypt(vector<unsigned char>& data, const string& key) {
    if (data.empty() || key.empty()) return;
    vector<unsigned char> S(256);
    keySchedulingAlgorithm(S, key);
    pseudoRandomGenerationAlgorithm(data, S);
}

void RC4::decrypt(vector<unsigned char>& data, const string& key) {
    encrypt(data, key); // RC4 симметричен
}

void RC4::keySchedulingAlgorithm(vector<unsigned char>& S, const string& key) {
    for (int i = 0; i < 256; ++i) {
        S[i] = static_cast<unsigned char>(i);
    }
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + static_cast<unsigned char>(key[i % key.length()])) % 256;
        swap(S[i], S[j]);
    }
}

void RC4::pseudoRandomGenerationAlgorithm(vector<unsigned char>& data, vector<unsigned char>& S) {
    int i = 0, j = 0;
    for (size_t k = 0; k < data.size(); ++k) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        unsigned char keyByte = S[(S[i] + S[j]) % 256];
        data[k] ^= keyByte;
    }
}

vector<unsigned char> RC4::generateKeyStream(const string& key, size_t length) {
    vector<unsigned char> S(256);
    keySchedulingAlgorithm(S, key);
    vector<unsigned char> keyStream(length);
    int i = 0, j = 0;
    for (size_t k = 0; k < length; ++k) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        keyStream[k] = S[(S[i] + S[j]) % 256];
    }
    return keyStream;
}