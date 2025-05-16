#include "DiagonalMatrix.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

DiagonalMatrix::DiagonalMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
    matrix_.resize(rows, std::vector<int>(cols, 0));
}

std::vector<int> DiagonalMatrix::readWord(int startRow, int wordIndex) const {
    int col = wordIndex % cols_;
    std::vector<int> word(rows_);
    for (int i = 0; i < rows_; ++i) {
        int row = (startRow + i) % rows_;
        word[i] = matrix_[row][col];
    }
    return word;
}

void DiagonalMatrix::writeWord(const std::vector<int>& word, int startRow, int wordIndex) {
    if (word.size() != static_cast<size_t>(rows_)) {
        throw std::invalid_argument("Word length must be " + std::to_string(rows_) + " bits.");
    }
    int col = wordIndex % cols_;
    for (int i = 0; i < rows_; ++i) {
        int row = (startRow + i) % rows_;
        matrix_[row][col] = word[i];
    }
}

std::vector<int> DiagonalMatrix::readAntiDiagonal(int sum) const {
    std::vector<int> antiDiagonal(rows_);
    int count = 0;
    for (int i = 0; i < rows_; ++i) {
        int j = sum - i;
        if (j >= 0 && j < cols_) {
            antiDiagonal[count++] = matrix_[i][j];
        }
    }
    antiDiagonal.resize(count);
    return antiDiagonal;
}

std::vector<int> DiagonalMatrix::logicalOperation(int startRow1, int col1, int startRow2, int col2, const std::string& function) const {
    std::vector<int> word1 = readWord(startRow1, col1);
    std::vector<int> word2 = readWord(startRow2, col2);
    std::vector<int> result(rows_);
    for (int i = 0; i < rows_; ++i) {
        bool a = word1[i] != 0;
        bool b = word2[i] != 0;
        std::string func = function;
        std::transform(func.begin(), func.end(), func.begin(), ::tolower);
        if (func == "and") {
            result[i] = logicalAnd(a, b) ? 1 : 0;
        }
        else if (func == "nand") {
            result[i] = logicalNand(a, b) ? 1 : 0;
        }
        else if (func == "repeat") {
            result[i] = repeatFirst(a, b) ? 1 : 0;
        }
        else if (func == "negate") {
            result[i] = negateFirst(a, b) ? 1 : 0;
        }
        else {
            return {};
        }
    }
    return result;
}

std::vector<int> DiagonalMatrix::andOperation(int startRow1, int col1, int startRow2, int col2) const {
    return logicalOperation(startRow1, col1, startRow2, col2, "and");
}

std::vector<int> DiagonalMatrix::nandOperation(int startRow1, int col1, int startRow2, int col2) const {
    return logicalOperation(startRow1, col1, startRow2, col2, "nand");
}

std::vector<int> DiagonalMatrix::repeatFirstOperation(int startRow1, int col1, int startRow2, int col2) const {
    return logicalOperation(startRow1, col1, startRow2, col2, "repeat");
}

std::vector<int> DiagonalMatrix::negateFirstOperation(int startRow1, int col1, int startRow2, int col2) const {
    return logicalOperation(startRow1, col1, startRow2, col2, "negate");
}

bool DiagonalMatrix::logicalAnd(bool a, bool b) {
    return a && b;
}

bool DiagonalMatrix::logicalNand(bool a, bool b) {
    return !(a && b);
}

bool DiagonalMatrix::repeatFirst(bool a, bool b) {
    return a;
}

bool DiagonalMatrix::negateFirst(bool a, bool b) {
    return !a;
}

std::vector<std::string> DiagonalMatrix::findClosestWord(const std::string& inputWord, bool isGreater, const std::vector<int>& startRows) const {
    if (inputWord.length() != static_cast<size_t>(rows_)) {
        throw std::invalid_argument("Input word length must be " + std::to_string(rows_) + " bits.");
    }
    std::vector<std::vector<std::string>> candidates;
    for (int col = 0; col < cols_; ++col) {
        int startRow = (startRows.size() > static_cast<size_t>(col)) ? startRows[col] : 0;
        std::vector<int> word = readWord(startRow, col);
        std::stringstream ss;
        for (int bit : word) {
            ss << bit;
        }
        std::string wordStr = ss.str();
        bool isValid = false;
        for (size_t i = 0; i < inputWord.length(); ++i) {
            if (inputWord[i] != wordStr[i]) {
                if (isGreater && inputWord[i] == '1' && wordStr[i] == '0') {
                    isValid = true;
                }
                else if (!isGreater && inputWord[i] == '0' && wordStr[i] == '1') {
                    isValid = true;
                }
                break;
            }
        }
        if (isValid) {
            candidates.push_back({ wordStr, std::to_string(col) });
        }
    }
    if (candidates.empty()) {
        throw std::invalid_argument("No words satisfy the comparison condition.");
    }
    auto closest = candidates[0];
    std::string closestWord = closest[0];
    for (size_t i = 1; i < candidates.size(); ++i) {
        std::string word = candidates[i][0];
        int dist1 = 0, dist2 = 0;
        for (size_t j = 0; j < inputWord.length(); ++j) {
            if (inputWord[j] != word[j]) ++dist1;
            if (inputWord[j] != closestWord[j]) ++dist2;
        }
        if (dist1 < dist2) {
            closest = candidates[i];
            closestWord = word;
        }
    }
    return closest;
}

std::vector<int> DiagonalMatrix::addBinaryNumbers(const std::vector<int>& a, const std::vector<int>& b) const {
    int carry = 0;
    size_t maxLen = std::max(a.size(), b.size());
    std::vector<int> result(maxLen + 1);
    for (size_t i = 0; i < maxLen; ++i) {
        int bitA = (i < a.size()) ? a[a.size() - 1 - i] : 0;
        int bitB = (i < b.size()) ? b[b.size() - 1 - i] : 0;
        int sum = bitA + bitB + carry;
        result[result.size() - 1 - i] = sum % 2;
        carry = sum / 2;
    }
    if (carry != 0) {
        result[0] = carry;
    }
    else {
        result.erase(result.begin());
    }
    return result;
}

void DiagonalMatrix::addFieldsByDiagonals(const std::vector<int>& startRows, int vFilter) {
    for (int wordIndex = 0; wordIndex < cols_; ++wordIndex) {
        int startRow = (startRows.size() > static_cast<size_t>(wordIndex)) ? startRows[wordIndex] : 0;
        std::vector<int> word = readWord(startRow, wordIndex);
        int currentV = (word[0] << 2) | (word[1] << 1) | word[2];
        if (currentV != vFilter) continue;
        std::vector<int> v(word.begin(), word.begin() + 3);
        std::vector<int> a(word.begin() + 3, word.begin() + 7);
        std::vector<int> b(word.begin() + 7, word.begin() + 11);
        std::vector<int> s(word.begin() + 11, word.begin() + 16);
        std::vector<int> sumResult = addBinaryNumbers(a, b);
        std::vector<int> newWord(rows_);
        std::copy(v.begin(), v.end(), newWord.begin());
        std::copy(a.begin(), a.end(), newWord.begin() + 3);
        std::copy(b.begin(), b.end(), newWord.begin() + 7);
        std::copy(sumResult.begin(), sumResult.end(), newWord.begin() + 11);
        writeWord(newWord, startRow, wordIndex);
    }
}

void DiagonalMatrix::printMatrix() const {
    std::cout << "\nMatrix:\n";
    for (const auto& row : matrix_) {
        std::cout << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i];
            if (i < row.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
}

void DiagonalMatrix::printAllWords(const std::vector<int>& startRows) const {
    std::cout << "\nAll words (by columns with startRow):\n";
    for (int wordIndex = 0; wordIndex < cols_; ++wordIndex) {
        int startRow = (startRows.size() > static_cast<size_t>(wordIndex)) ? startRows[wordIndex] : 0;
        std::vector<int> word = readWord(startRow, wordIndex);
        std::cout << "S_" << wordIndex << " (startRow=" << startRow << "): [";
        for (size_t i = 0; i < word.size(); ++i) {
            std::cout << word[i];
            if (i < word.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
}