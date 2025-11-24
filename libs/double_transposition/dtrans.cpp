#include "dtrans.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

// Парсит строковый ключ вида "3142" -> {2,0,3,1} (от 1 до N)
static std::vector<int> parseKey(const std::string& key) {
    std::vector<int> perm;
    for (char ch : key) {
        if (ch < '1' || ch > '9') throw std::invalid_argument("Ключ должен содержать только цифры от 1 до N.");
        perm.push_back(int(ch - '1'));
    }
    return perm;
}

static std::vector<int> inversePerm(const std::vector<int>& perm) {
    std::vector<int> inv(perm.size());
    for (size_t i = 0; i < perm.size(); ++i)
        inv[perm[i]] = int(i);
    return inv;
}

std::string doubleTransEncrypt(const std::string& text, const std::string& colKey, const std::string& rowKey) {
    auto colPerm = parseKey(colKey);
    auto rowPerm = parseKey(rowKey);
    size_t cols = colPerm.size();
    size_t rows = rowPerm.size();

    // Создать таблицу, дополнить пробелами если текста не хватает
    std::vector<std::vector<char>> table(rows, std::vector<char>(cols, ' '));
    size_t pos = 0;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            if (pos < text.size()) table[r][c] = text[pos++];

    // Сначала переставляем столбцы
    std::vector<std::vector<char>> afterCols(rows, std::vector<char>(cols));
    for (size_t c = 0; c < cols; ++c)
        for (size_t r = 0; r < rows; ++r)
            afterCols[r][c] = table[r][colPerm[c]];

    // Затем строки
    std::vector<std::vector<char>> afterRows(rows, std::vector<char>(cols));
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            afterRows[r][c] = afterCols[rowPerm[r]][c];

    // Читать по строкам, собрать строку
    std::string result;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            result += afterRows[r][c];
    return result;
}

std::string doubleTransDecrypt(const std::string& cipher, const std::string& colKey, const std::string& rowKey) {
    auto colPerm = parseKey(colKey);
    auto rowPerm = parseKey(rowKey);
    size_t cols = colPerm.size();
    size_t rows = rowPerm.size();
    if (cipher.size() != rows * cols)
        throw std::invalid_argument("Размер текста не кратен размеру таблицы! Попробуйте дописать пробелы в конец шифртекста.");

    // Заполнить таблицу построчно
    std::vector<std::vector<char>> table(rows, std::vector<char>(cols));
    size_t pos = 0;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            table[r][c] = cipher[pos++];

    // Сначала обратная перестановка строк
    auto invRow = inversePerm(rowPerm);
    std::vector<std::vector<char>> afterRows(rows, std::vector<char>(cols));
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            afterRows[invRow[r]][c] = table[r][c];

    // Затем обратная перестановка столбцов
    auto invCol = inversePerm(colPerm);
    std::vector<std::vector<char>> afterCols(rows, std::vector<char>(cols));
    for (size_t c = 0; c < cols; ++c)
        for (size_t r = 0; r < rows; ++r)
            afterCols[r][invCol[c]] = afterRows[r][c];

    // Читать по строкам
    std::string result;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            result += afterCols[r][c];
    return result;
}