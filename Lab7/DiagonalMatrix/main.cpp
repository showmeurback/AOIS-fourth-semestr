#include "DiagonalMatrix.h"
#include <iostream>
#include <vector>

int main() {
    setlocale(LC_ALL, "RU");

    DiagonalMatrix dm(16, 16);
    std::vector<int> startRows = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

    dm.writeWord({ 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 }, startRows[0], 0);
    dm.writeWord({ 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0 }, startRows[1], 1);
    dm.writeWord({ 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0 }, startRows[2], 2);
    dm.writeWord({ 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 }, startRows[3], 3);

    std::cout << "\n=== Initial Matrix ===\n";
    dm.printMatrix();
    std::cout << "\nAll words before operation:\n";
    dm.printAllWords(startRows);

    std::cout << "\n=== Test 1: Addition for words with Vj=3 (011) ===\n";
    dm.addFieldsByDiagonals(startRows, 3);
    std::cout << "All words after operation (Vj=3):\n";
    dm.printAllWords(startRows);

    std::cout << "\n=== Test 2: Addition for words with Vj=7 (111) ===\n";
    dm.addFieldsByDiagonals(startRows, 7);
    std::cout << "All words after operation (Vj=7):\n";
    dm.printAllWords(startRows);

    std::cout << "\n=== Test 3: Logical Operations ===\n";
    std::vector<std::vector<int>> testColumns = { {startRows[0], 0, startRows[1], 1}, {startRows[2], 2, startRows[3], 3} };
    for (const auto& pair : testColumns) {
        int startRow1 = pair[0], col1 = pair[1], startRow2 = pair[2], col2 = pair[3];
        std::cout << "\nOperations on words S_" << col1 << " (startRow=" << startRow1 << ") and S_" << col2 << " (startRow=" << startRow2 << "):\n";
        std::vector<int> word1 = dm.readWord(startRow1, col1);
        std::vector<int> word2 = dm.readWord(startRow2, col2);
        std::cout << "Word S_" << col1 << ": [";
        for (size_t i = 0; i < word1.size(); ++i) {
            std::cout << word1[i];
            if (i < word1.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "Word S_" << col2 << ": [";
        for (size_t i = 0; i < word2.size(); ++i) {
            std::cout << word2[i];
            if (i < word2.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::vector<int> andResult = dm.andOperation(startRow1, col1, startRow2, col2);
        std::vector<int> nandResult = dm.nandOperation(startRow1, col1, startRow2, col2);
        std::vector<int> repeatResult = dm.repeatFirstOperation(startRow1, col1, startRow2, col2);
        std::vector<int> negateResult = dm.negateFirstOperation(startRow1, col1, startRow2, col2);
        std::cout << "AND: [";
        for (size_t i = 0; i < andResult.size(); ++i) {
            std::cout << andResult[i];
            if (i < andResult.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "NAND: [";
        for (size_t i = 0; i < nandResult.size(); ++i) {
            std::cout << nandResult[i];
            if (i < nandResult.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "Repeat First: [";
        for (size_t i = 0; i < repeatResult.size(); ++i) {
            std::cout << repeatResult[i];
            if (i < repeatResult.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "Negate First: [";
        for (size_t i = 0; i < negateResult.size(); ++i) {
            std::cout << negateResult[i];
            if (i < negateResult.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    std::cout << "\n=== Test 4: Find Closest Word ===\n";
    try {
        std::vector<std::string> result = dm.findClosestWord("1000000000000000", false, startRows);
        std::cout << "Closest word (less): [" << result[0] << ", " << result[1] << "]\n";
        result = dm.findClosestWord("1000000000000000", true, startRows);
        std::cout << "Closest word (greater): [" << result[0] << ", " << result[1] << "]\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}