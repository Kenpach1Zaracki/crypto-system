#include <iostream>
#include <fstream>
#include "../../include/utils/file_io.h"

using namespace std;

void writeToFile(const string& filename, const string& content) {
    ofstream file(filename, ios::binary);
    if (file) {
        file.write(content.c_str(), content.size());
        cout << "Файл записан: " << filename << endl;
    } else {
        cerr << "Ошибка записи файла: " << filename << endl;
    }
}

string readFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (file) {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        return content;
    } else {
        cerr << "Ошибка чтения файла: " << filename << endl;
        return "";
    }
}

void displayFileContent(const string& filename) {
    string content = readFromFile(filename);
    if (!content.empty()) {
        cout << "Содержимое файла " << filename << ":\n";
        cout << content << endl;
    }
}
