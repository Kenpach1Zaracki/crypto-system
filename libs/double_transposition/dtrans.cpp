#include "dtrans.h"
#include <vector>
#include <algorithm>
#include <cstdint>

std::vector<unsigned char> doubleTranspositionEncryptBinary(const std::vector<unsigned char>& data, const std::string& key) {
    size_t n = key.size();
    if (n == 0) return data;

    size_t rows = (data.size() + n - 1) / n;
    std::vector<unsigned char> padded(data);
    padded.resize(rows * n, 0);

    std::vector<std::pair<char, size_t>> key_order;
    for (size_t i = 0; i < key.size(); ++i) key_order.push_back({key[i], i});
    std::sort(key_order.begin(), key_order.end());

    std::vector<unsigned char> encrypted;
    encrypted.reserve(rows * n);

    for (auto &k : key_order) {
        size_t col = k.second;
        for (size_t r = 0; r < rows; ++r) {
            encrypted.push_back(padded[r * n + col]);
        }
    }

    return encrypted;
}

std::vector<unsigned char> doubleTranspositionDecryptBinary(const std::vector<unsigned char>& data, const std::string& key, size_t original_size) {
    size_t n = key.size();
    if (n == 0) return data;

    size_t rows = (data.size() + n - 1) / n;

    std::vector<std::pair<char, size_t>> key_order;
    for (size_t i = 0; i < key.size(); ++i) key_order.push_back({key[i], i});
    std::sort(key_order.begin(), key_order.end());

    std::vector<unsigned char> temp(rows * n);
    size_t index = 0;
    for (auto &k : key_order) {
        size_t col = k.second;
        for (size_t r = 0; r < rows; ++r) {
            temp[r * n + col] = data[index++];
        }
    }

    temp.resize(original_size);
    return temp;
}

std::string doubleTranspositionEncrypt(const std::string& data, const std::string& key) {
    uint64_t size64 = data.size();
    std::vector<unsigned char> header(8);
    for (int i = 0; i < 8; ++i) header[i] = (size64 >> (56 - i*8)) & 0xFF;

    std::vector<unsigned char> body(data.begin(), data.end());
    std::vector<unsigned char> encrypted = doubleTranspositionEncryptBinary(body, key);

    std::string out(header.begin(), header.end());
    out += std::string(encrypted.begin(), encrypted.end());
    return out;
}

std::string doubleTranspositionDecrypt(const std::string& data, const std::string& key) {
    if (data.size() < 8) return "";

    uint64_t original_size = 0;
    for (int i = 0; i < 8; ++i) {
        original_size = (original_size << 8) | static_cast<unsigned char>(data[i]);
    }

    std::vector<unsigned char> body(data.begin() + 8, data.end());
    std::vector<unsigned char> decrypted = doubleTranspositionDecryptBinary(body, key, original_size);

    return std::string(decrypted.begin(), decrypted.end());
}
