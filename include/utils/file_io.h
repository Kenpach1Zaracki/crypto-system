#pragma once
#include <string>

void writeToFile(const std::string& filename, const std::string& content);
std::string readFromFile(const std::string& filename);
void displayFileContent(const std::string& filename);
