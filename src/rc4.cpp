#include "../include/rc4.h"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

void RC4::encrypt(vector<unsigned char>& data, const string& key) {
    if (data.empty() || key.empty()) return;
    
    // Правильная реализация RC4
    vector<unsigned char> S(256);
    
    // KSA - Key Scheduling Algorithm
    keySchedulingAlgorithm(S, key);
    
    // PRGA - Pseudo-Random Generation Algorithm
    pseudoRandomGenerationAlgorithm(data, S);
}

void RC4::decrypt(vector<unsigned char>& data, const string& key) {
    // RC4 симметричен
    encrypt(data, key);
}

void RC4::keySchedulingAlgorithm(vector<unsigned char>& S, const string& key) {
    // Инициализация S-box
    for (int i = 0; i < 256; ++i) {
        S[i] = static_cast<unsigned char>(i);
    }
    
    // Перемешивание S-box с использованием ключа
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + static_cast<unsigned char>(key[i % key.length()])) % 256;
        swap(S[i], S[j]);
    }
}

void RC4::pseudoRandomGenerationAlgorithm(vector<unsigned char>& data, vector<unsigned char>& S) {
    int i = 0, j = 0;
    
    for (size_t k = 0; k < data.size(); ++k) {
        // Обновляем индексы
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        
        // Меняем местами
        swap(S[i], S[j]);
        
        // Генерируем ключевой байт
        unsigned char keyByte = S[(S[i] + S[j]) % 256];
        
        // XOR с данными
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

void RC4::printRC4Analysis(const vector<unsigned char>& original, 
                          const vector<unsigned char>& encrypted) {
    cout << "\n=== КРИПТОАНАЛИЗ RC4 ===" << endl;
    cout << "Размер данных: " << original.size() << " байт" << endl;
    
    // Анализ распределения байтов
    map<unsigned char, int> origFreq, encFreq;
    for (size_t i = 0; i < original.size(); ++i) {
        origFreq[original[i]]++;
        encFreq[encrypted[i]]++;
    }
    
    cout << "Уникальных байтов в исходном: " << origFreq.size() << endl;
    cout << "Уникальных байтов в зашифрованном: " << encFreq.size() << endl;
    
    double bias = calculateBias(encrypted);
    cout << fixed << setprecision(6);
    cout << "Статистическое смещение: " << bias << endl;
    
    if (bias < 0.01) {
        cout << "✅ ОТЛИЧНАЯ случайность (смещение < 0.01)" << endl;
    } else if (bias < 0.05) {
        cout << "✅ ХОРОШАЯ случайность (смещение < 0.05)" << endl;
    } else {
        cout << "⚠️  ЗАМЕТНОЕ смещение (смещение > 0.05)" << endl;
    }
    
    // Проверка на известные слабости RC4
    if (original.size() > 256) {
        bool hasWeakness = false;
        for (size_t i = 0; i < min(original.size(), size_t(256)); ++i) {
            if (encrypted[i] == (i + 1) % 256) {
                hasWeakness = true;
                break;
            }
        }
        if (hasWeakness) {
            cout << "⚠️  ОБНАРУЖЕНА слабость в первых байтах RC4!" << endl;
        } else {
            cout << "✅ Слабости в первых байтах не обнаружено" << endl;
        }
    }
}

double RC4::calculateBias(const vector<unsigned char>& data) {
    if (data.empty()) return 0.0;
    
    vector<int> frequency(256, 0);
    for (unsigned char byte : data) {
        frequency[byte]++;
    }
    
    double expected = static_cast<double>(data.size()) / 256.0;
    double chiSquare = 0.0;
    
    for (int i = 0; i < 256; ++i) {
        double diff = frequency[i] - expected;
        chiSquare += (diff * diff) / expected;
    }
    
    // Нормализованное смещение
    return chiSquare / data.size();
}