#include "pch.h"
#include <gtest/gtest.h>
#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 7\AOIS-LR-7\DiagonalMatrix.h"
#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 7\AOIS-LR-7\DiagonalMatrix.cpp"
#include <sstream>
#include <vector>
#include <string>
#include <functional>

// Test fixture for DiagonalMatrix tests
class DiagonalMatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize a 4x4 matrix for most tests
        dm = new DiagonalMatrix(4, 4);
    }

    void TearDown() override {
        delete dm;
    }

    DiagonalMatrix* dm;

    // Helper function to capture console output
    std::string captureOutput(std::function<void()> func) {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        func();
        std::cout.rdbuf(old);
        return buffer.str();
    }
};

// Test constructor and matrix initialization
TEST_F(DiagonalMatrixTest, ConstructorInitializesMatrix) {
    std::vector<std::vector<int>> expected(4, std::vector<int>(4, 0));
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_EQ(0, dm->readWord(0, j)[i]) << "Matrix should be initialized to zeros";
        }
    }
}

// Test writeWord and readWord
TEST_F(DiagonalMatrixTest, WriteAndReadWord) {
    std::vector<int> word = { 1, 0, 1, 1 };
    dm->writeWord(word, 0, 0);
    std::vector<int> read = dm->readWord(0, 0);
    ASSERT_EQ(word, read) << "Read word should match written word";

    // Test with non-zero startRow
    dm->writeWord(word, 2, 1);
    read = dm->readWord(2, 1);
    ASSERT_EQ(word, read) << "Read word with startRow=2 should match written word";
}

// Test writeWord with invalid word length
TEST_F(DiagonalMatrixTest, WriteWordInvalidLength) {
    std::vector<int> invalidWord = { 1, 0, 1 };
    ASSERT_THROW(dm->writeWord(invalidWord, 0, 0), std::invalid_argument)
        << "Writing word with wrong length should throw";
}

// Test readAntiDiagonal
TEST_F(DiagonalMatrixTest, ReadAntiDiagonal) {
    std::vector<int> word = { 1, 0, 1, 1 };
    dm->writeWord(word, 0, 0);
    dm->writeWord({ 0, 1, 0, 1 }, 0, 1);
    std::vector<int> diag = dm->readAntiDiagonal(1); // Should get matrix[0][1], matrix[1][0]
    ASSERT_EQ(std::vector<int>({ 0, 0 }), diag) << "Anti-diagonal sum=1 should match expected values";
}

// Test logicalOperation with AND
TEST_F(DiagonalMatrixTest, LogicalOperationAnd) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->logicalOperation(0, 0, 0, 1, "and");
    ASSERT_EQ(std::vector<int>({ 0, 0, 1, 0 }), result) << "AND operation should produce correct result";
}

// Test logicalOperation with NAND
TEST_F(DiagonalMatrixTest, LogicalOperationNand) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->logicalOperation(0, 0, 0, 1, "nand");
    ASSERT_EQ(std::vector<int>({ 1, 1, 0, 1 }), result) << "NAND operation should produce correct result";
}

// Test logicalOperation with Repeat
TEST_F(DiagonalMatrixTest, LogicalOperationRepeat) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->logicalOperation(0, 0, 0, 1, "repeat");
    ASSERT_EQ(std::vector<int>({ 1, 0, 1, 1 }), result) << "Repeat operation should return first word";
}

// Test logicalOperation with Negate
TEST_F(DiagonalMatrixTest, LogicalOperationNegate) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->logicalOperation(0, 0, 0, 1, "negate");
    ASSERT_EQ(std::vector<int>({ 0, 1, 0, 0 }), result) << "Negate operation should negate first word";
}

// Test logicalOperation with invalid function
TEST_F(DiagonalMatrixTest, LogicalOperationInvalidFunction) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->logicalOperation(0, 0, 0, 1, "invalid");
    ASSERT_TRUE(result.empty()) << "Invalid function should return empty vector";
}

// Test static logical functions
TEST_F(DiagonalMatrixTest, StaticLogicalFunctions) {
    ASSERT_TRUE(DiagonalMatrix::logicalAnd(true, true));
    ASSERT_FALSE(DiagonalMatrix::logicalAnd(true, false));
    ASSERT_TRUE(DiagonalMatrix::logicalNand(false, true));
    ASSERT_FALSE(DiagonalMatrix::logicalNand(true, true));
    ASSERT_TRUE(DiagonalMatrix::repeatFirst(true, false));
    ASSERT_FALSE(DiagonalMatrix::repeatFirst(false, true));
    ASSERT_FALSE(DiagonalMatrix::negateFirst(true, false));
    ASSERT_TRUE(DiagonalMatrix::negateFirst(false, true));
}

// Test specific logical operation methods
TEST_F(DiagonalMatrixTest, AndOperation) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->andOperation(0, 0, 0, 1);
    ASSERT_EQ(std::vector<int>({ 0, 0, 1, 0 }), result) << "andOperation should match logicalOperation(and)";
}

TEST_F(DiagonalMatrixTest, NandOperation) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->nandOperation(0, 0, 0, 1);
    ASSERT_EQ(std::vector<int>({ 1, 1, 0, 1 }), result) << "nandOperation should match logicalOperation(nand)";
}

TEST_F(DiagonalMatrixTest, RepeatFirstOperation) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->repeatFirstOperation(0, 0, 0, 1);
    ASSERT_EQ(std::vector<int>({ 1, 0, 1, 1 }), result) << "repeatFirstOperation should match logicalOperation(repeat)";
}

TEST_F(DiagonalMatrixTest, NegateFirstOperation) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    dm->writeWord({ 0, 1, 1, 0 }, 0, 1);
    std::vector<int> result = dm->negateFirstOperation(0, 0, 0, 1);
    ASSERT_EQ(std::vector<int>({ 0, 1, 0, 0 }), result) << "negateFirstOperation should match logicalOperation(negate)";
}

// Test findClosestWord with invalid input
TEST_F(DiagonalMatrixTest, FindClosestWordInvalidLength) {
    std::vector<int> startRows = { 0, 0, 0, 0 };
    ASSERT_THROW(dm->findClosestWord("001", true, startRows), std::invalid_argument)
        << "Invalid word length should throw";
}

// Test findClosestWord with no valid candidates
TEST_F(DiagonalMatrixTest, FindClosestWordNoCandidates) {
    dm->writeWord({ 1, 1, 1, 1 }, 0, 0); // 1111
    dm->writeWord({ 1, 1, 1, 1 }, 0, 1);
    dm->writeWord({ 1, 1, 1, 1 }, 0, 2);
    dm->writeWord({ 1, 1, 1, 1 }, 0, 3);
    std::vector<int> startRows = { 0, 0, 0, 0 };
    ASSERT_THROW(dm->findClosestWord("1111", false, startRows), std::invalid_argument)
        << "No valid candidates should throw";
}

// Test addBinaryNumbers
TEST_F(DiagonalMatrixTest, AddBinaryNumbers) {
    std::vector<int> a = { 1, 1 }; // 11
    std::vector<int> b = { 1, 0 }; // 10
    std::vector<int> result = dm->addBinaryNumbers(a, b);
    ASSERT_EQ(std::vector<int>({ 1, 0, 1 }), result) << "Binary addition 11 + 10 should yield 101";
}

// Test printMatrix
TEST_F(DiagonalMatrixTest, PrintMatrix) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    std::string output = captureOutput([this]() { dm->printMatrix(); });
    std::string expected = "\nMatrix:\n[1, 0, 0, 0]\n[0, 0, 0, 0]\n[1, 0, 0, 0]\n[1, 0, 0, 0]\n";
    ASSERT_EQ(expected, output) << "printMatrix should produce correct output";
}

// Test printAllWords
TEST_F(DiagonalMatrixTest, PrintAllWords) {
    dm->writeWord({ 1, 0, 1, 1 }, 0, 0);
    std::vector<int> startRows = { 0, 0, 0, 0 };
    std::string output = captureOutput([this, &startRows]() { dm->printAllWords(startRows); });
    std::string expected = "\nAll words (by columns with startRow):\n"
        "S_0 (startRow=0): [1, 0, 1, 1]\n"
        "S_1 (startRow=0): [0, 0, 0, 0]\n"
        "S_2 (startRow=0): [0, 0, 0, 0]\n"
        "S_3 (startRow=0): [0, 0, 0, 0]\n";
    ASSERT_EQ(expected, output) << "printAllWords should produce correct output";
}

// Main function for running tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}