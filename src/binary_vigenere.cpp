#include "../include/binary_vigenere.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

void BinaryVigenere::encrypt(vector<unsigned char>& data, const string& key) {
    if (data.empty() || key.empty()) return;
    
    // ПРАВИЛЬНАЯ реализация двоичного шифра Виженера
    string binaryKey = keyToBinary(key);
    
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char result = 0;
        
        // Обрабатываем каждый бит отдельно
        for (int bit = 0; bit < 8; ++bit) {
            size_t keyIndex = (i * 8 + bit) % binaryKey.length();
            
            // Извлекаем биты
            int dataBit = (data[i] >> bit) & 1;
            int keyBit = (binaryKey[keyIndex] == '1') ? 1 : 0;
            
            // Двоичный Виженер = XOR
            int encryptedBit = dataBit ^ keyBit;
            
            // Устанавливаем бит в результат
            result |= (encryptedBit << bit);
        }
        
        data[i] = result;
    }
}

void BinaryVigenere::decrypt(vector<unsigned char>& data, const string& key) {
    // Двоичный Виженер симметричен относительно XOR
    encrypt(data, key);
}

string BinaryVigenere::keyToBinary(const string& key) {
    string binaryKey = "";
    
    for (char c : key) {
        // Преобразуем каждый символ в 8-битное двоичное представление
        for (int i = 7; i >= 0; --i) {
            binaryKey += ((c >> i) & 1) ? '1' : '0';
        }
    }
    
    return binaryKey;
}

double BinaryVigenere::calculateEntropy(const vector<unsigned char>& data) {
    if (data.empty()) return 0.0;
    
    map<unsigned char, int> frequency;
    for (unsigned char byte : data) {
        frequency[byte]++;
    }
    
    double entropy = 0.0;
    double size = static_cast<double>(data.size());
    
    for (const auto& pair : frequency) {
        double prob = static_cast<double>(pair.second) / size;
        if (prob > 0) {
            entropy -= prob * log2(prob);
        }
    }
    
    return entropy;
}

void BinaryVigenere::printBinaryAnalysis(const vector<unsigned char>& original, 
                                       const vector<unsigned char>& encrypted) {
    cout << "\n=== КРИПТОАНАЛИЗ BINARY VIGENERE ===" << endl;
    cout << "Размер данных: " << original.size() << " байт" << endl;
    
    double originalEntropy = calculateEntropy(original);
    double encryptedEntropy = calculateEntropy(encrypted);
    
    cout << fixed << setprecision(4);
    cout << "Энтропия исходных данных: " << originalEntropy << " бит/байт" << endl;
    cout << "Энтропия зашифрованных данных: " << encryptedEntropy << " бит/байт" << endl;
    cout << "Улучшение энтропии: " << (encryptedEntropy - originalEntropy) << " бит/байт" << endl;
    
    // Анализ распределения байтов
    map<unsigned char, int> origFreq, encFreq;
    for (size_t i = 0; i < original.size(); ++i) {
        origFreq[original[i]]++;
        encFreq[encrypted[i]]++;
    }
    
    cout << "Уникальных байтов в исходном: " << origFreq.size() << endl;
    cout << "Уникальных байтов в зашифрованном: " << encFreq.size() << endl;
    
    if (encryptedEntropy > 7.5) {
        cout << "✅ ХОРОШАЯ криптостойкость (энтропия > 7.5)" << endl;
    } else if (encryptedEntropy > 6.0) {
        cout << "⚠️  СРЕДНЯЯ криптостойкость (6.0 < энтропия < 7.5)" << endl;
    } else {
        cout << "❌ СЛАБАЯ криптостойкость (энтропия < 6.0)" << endl;
    }
}

void BinaryVigenere::applyBinaryKey(vector<unsigned char>& data, const string& binaryKey, bool) {
    // Убираем предупреждение о неиспользуемом параметре
    // Этот метод теперь не используется, но оставляем для совместимости
    for (size_t i = 0; i < data.size(); ++i) {
        size_t keyIndex = i % binaryKey.length();
        unsigned char keyByte = (binaryKey[keyIndex] == '1') ? 0xFF : 0x00;
        data[i] ^= keyByte;
    }
}

vector<int> BinaryVigenere::generateKeySchedule(const string& key, size_t dataSize) {
    vector<int> schedule;
    string binaryKey = keyToBinary(key);
    
    for (size_t i = 0; i < dataSize * 8; ++i) {
        schedule.push_back((binaryKey[i % binaryKey.length()] == '1') ? 1 : 0);
    }
    
    return schedule;
}