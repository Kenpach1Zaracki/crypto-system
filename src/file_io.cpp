#include "file_io.h"
#include <fstream>
#include <iostream>
#include "../include/cryptoLibs.h"

using namespace std;

bool writeTextToFile(const string& filename, const string& text) {
ofstream outfile(filename, ios::binary);
if (!outfile) return false;
outfile.write(text.c_str(), text.size());
outfile.close();
return true;
}

bool readTextFromFile(const string& filename, string& text) {
ifstream infile(filename, ios::binary);
if (!infile) return false;
text.clear();
char c;
while (infile.get(c)) text += c;
infile.close();
return true;
}

bool caesarFileEncrypt(const string& filename, const string& key) {
int shift = stoi(key);
string text;
if (!readTextFromFile(filename, text)) return false;
string encrypted = caesarEncrypt(text, shift);
return writeTextToFile(filename, encrypted);
}

bool caesarFileDecrypt(const string& filename, const string& key) {
int shift = stoi(key);
string text;
if (!readTextFromFile(filename, text)) return false;
string decrypted = caesarDecrypt(text, shift);
return writeTextToFile(filename, decrypted);
}

bool atbashFileEncrypt(const string& filename, const string& key) {
string text;
if (!readTextFromFile(filename, text)) return false;
string encrypted = atbashUniversal(text); 
return writeTextToFile(filename, encrypted);
}

bool atbashFileDecrypt(const string& filename, const string& key) {
string text;
if (!readTextFromFile(filename, text)) return false;
string decrypted = atbashUniversal(text);
return writeTextToFile(filename, decrypted);
}

bool doubleTranspositionFileEncrypt(const string& filename, const string& key) {
string text;
if (!readTextFromFile(filename, text)) return false;
string encrypted = doubleTranspositionEncrypt(text, key);
return writeTextToFile(filename, encrypted);
}

bool doubleTranspositionFileDecrypt(const string& filename, const string& key) {
string text;
if (!readTextFromFile(filename, text)) return false;
string decrypted = doubleTranspositionDecrypt(text, key);
return writeTextToFile(filename, decrypted);
}
