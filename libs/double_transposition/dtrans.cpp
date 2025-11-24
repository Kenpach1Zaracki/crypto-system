#include "dtrans.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

// Парсит строковый ключ вида "4132" -> {3,0,2,1}
static std::vector<int> parseKey(const std::string& key) {
    // Удаляем пробелы и невидимые символы из ключа
    std::string cleanKey;
    for (char ch : key) {
        if (ch >= '1' && ch <= '9') {
            cleanKey += ch;
        }
    }
    
    if (cleanKey.empty()) {
        throw std::invalid_argument("Ключ должен содержать хотя бы одну цифру от 1 до 9");
    }
    
    size_t N = cleanKey.size();
    std::vector<int> perm(N);

    for (size_t i = 0; i < N; ++i) {
        char ch = cleanKey[i];
        perm[i] = ch - '1';
    }
    
    return perm;
}

static std::vector<int> inversePerm(const std::vector<int>& perm) {
    std::vector<int> inv(perm.size());
    for (size_t i = 0; i < perm.size(); ++i)
        inv[perm[i]] = int(i);
    return inv;
}

// Универсальный Double Transposition
std::string doubleTransEncrypt(const std::string& data, const std::string& colKey, const std::string& rowKey) {
    auto colPerm = parseKey(colKey);
    auto rowPerm = parseKey(rowKey);
    size_t cols = colPerm.size();
    size_t rows = rowPerm.size();

    std::vector<std::vector<char>> table(rows, std::vector<char>(cols, 0));
    size_t pos = 0;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            if (pos < data.size()) table[r][c] = data[pos++];

    // перестановка столбцов
    std::vector<std::vector<char>> afterCols(rows, std::vector<char>(cols));
    for (size_t c = 0; c < cols; ++c)
        for (size_t r = 0; r < rows; ++r)
            afterCols[r][c] = table[r][colPerm[c]];

    // перестановка строк
    std::vector<std::vector<char>> afterRows(rows, std::vector<char>(cols));
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            afterRows[r][c] = afterCols[rowPerm[r]][c];

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
        throw std::invalid_argument("Размер файла не кратен размеру таблицы. Добавьте недостающие байты.");

    std::vector<std::vector<char>> table(rows, std::vector<char>(cols));
    size_t pos = 0;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            table[r][c] = cipher[pos++];

    auto invRow = inversePerm(rowPerm);
    std::vector<std::vector<char>> afterRows(rows, std::vector<char>(cols));
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            afterRows[invRow[r]][c] = table[r][c];

    auto invCol = inversePerm(colPerm);
    std::vector<std::vector<char>> afterCols(rows, std::vector<char>(cols));
    for (size_t c = 0; c < cols; ++c)
        for (size_t r = 0; r < rows; ++r)
            afterCols[r][invCol[c]] = afterRows[r][c];

    std::string result;
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            result += afterCols[r][c];
    return result;
}