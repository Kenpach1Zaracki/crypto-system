// libs/atbash/atb_cipher.cpp
#include "../include/cryptoLibs.h"
#include <string>

std::string atbashText(const std::string& text) {
    std::string result;
    result.reserve(text.size());

    for (size_t i = 0; i < text.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(text[i]);

        // ASCII uppercase
        if (c >= 65 && c <= 90) {
            unsigned char mapped = static_cast<unsigned char>(65 + (90 - c));
            result += static_cast<char>(mapped);
        }
        // ASCII lowercase
        else if (c >= 97 && c <= 122) {
            unsigned char mapped = static_cast<unsigned char>(97 + (122 - c));
            result += static_cast<char>(mapped);
        }
        // Note: the following blocks assume single-byte Cyrillic (CP1251/ISO-8859-5).
        // If your terminal/input uses UTF-8, Cyrillic letters are multi-byte and
        // should be handled via proper UTF-8 decoding -> Unicode codepoints.
        else if (c >= 192 && c <= 223) { // upper cyrillic in single-byte encodings
            unsigned char mapped = static_cast<unsigned char>(192 + (223 - c));
            result += static_cast<char>(mapped);
        }
        else if (c >= 224 && c <= 255) { // lower cyrillic in single-byte encodings
            unsigned char mapped = static_cast<unsigned char>(224 + (255 - c));
            result += static_cast<char>(mapped);
        }
        // digits
        else if (c >= 48 && c <= 57) {
            unsigned char mapped = static_cast<unsigned char>(48 + (57 - c));
            result += static_cast<char>(mapped);
        }
        else {
            // keep byte as-is
            result += static_cast<char>(c);
        }
    }

    return result;
}

std::string atbashAll(const std::string& data) {
    std::string result;
    result.resize(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char b = static_cast<unsigned char>(data[i]);
        result[i] = static_cast<char>(255 - b);
    }
    return result;
}
