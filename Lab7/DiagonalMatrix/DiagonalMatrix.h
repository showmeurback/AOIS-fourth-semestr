#ifndef DIAGONAL_MATRIX_HPP
#define DIAGONAL_MATRIX_HPP

#include <vector>
#include <string>

class DiagonalMatrix {
private:
    int rows_;
    int cols_;
    std::vector<std::vector<int>> matrix_;

public:
    DiagonalMatrix(int rows, int cols);
    std::vector<int> readWord(int startRow, int wordIndex) const;
    void writeWord(const std::vector<int>& word, int startRow, int wordIndex);
    std::vector<int> readAntiDiagonal(int sum) const;
    std::vector<int> logicalOperation(int startRow1, int col1, int startRow2, int col2, const std::string& function) const;
    std::vector<int> andOperation(int startRow1, int col1, int startRow2, int col2) const;
    std::vector<int> nandOperation(int startRow1, int col1, int startRow2, int col2) const;
    std::vector<int> repeatFirstOperation(int startRow1, int col1, int startRow2, int col2) const;
    std::vector<int> negateFirstOperation(int startRow1, int col1, int startRow2, int col2) const;
    static bool logicalAnd(bool a, bool b);
    static bool logicalNand(bool a, bool b);
    static bool repeatFirst(bool a, bool b);
    static bool negateFirst(bool a, bool b);
    std::vector<std::string> findClosestWord(const std::string& inputWord, bool isGreater, const std::vector<int>& startRows) const;
    std::vector<int> addBinaryNumbers(const std::vector<int>& a, const std::vector<int>& b) const;
    void addFieldsByDiagonals(const std::vector<int>& startRows, int vFilter);
    void printMatrix() const;
    void printAllWords(const std::vector<int>& startRows) const;
};

#endif // DIAGONAL_MATRIX_HPP