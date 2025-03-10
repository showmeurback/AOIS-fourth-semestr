#include "pch.h"
#include "D:/BSUIR/2 курс/4 семестр/АОИС/ЛР 1/AOIS-LR-1/BinaryOperations.h"
#include "D:/BSUIR/2 курс/4 семестр/АОИС/ЛР 1/AOIS-LR-1/BinaryOperations.cpp"
#include <gtest/gtest.h>


// Тесты для toReverseCode
TEST(BinaryOperationsTest, ToReverseCode) {
    EXPECT_EQ(BinaryOperations::toReverseCode("00000101"), "00000101");
    EXPECT_EQ(BinaryOperations::toReverseCode("11111011"), "00000100");
}

// Тесты для subtract
TEST(BinaryOperationsTest, Subtract) {
    EXPECT_EQ(BinaryOperations::subtract("00000101", "00000010"), "00000011");
    EXPECT_EQ(BinaryOperations::subtract("00000101", "00000101"), "00000000");
}

// Тесты для binaryToInt
TEST(BinaryOperationsTest, BinaryToInt) {
    EXPECT_EQ(BinaryOperations::binaryToInt("00000101"), 5);
    EXPECT_EQ(BinaryOperations::binaryToInt("11111011"), -5);
}

// Тесты для floatToIEEE754
TEST(BinaryOperationsTest, FloatToIEEE754) {
    EXPECT_EQ(BinaryOperations::floatToIEEE754(1.0f), "00111111100000000000000000000000");
    EXPECT_EQ(BinaryOperations::floatToIEEE754(-1.0f), "10111111100000000000000000000000");
}

// Тесты для ieee754ToDecimal
TEST(BinaryOperationsTest, Ieee754ToDecimal) {
    EXPECT_FLOAT_EQ(BinaryOperations::ieee754ToDecimal("00111111100000000000000000000000"), 1.0f);
    EXPECT_FLOAT_EQ(BinaryOperations::ieee754ToDecimal("10111111100000000000000000000000"), -1.0f);
}

// Тесты для addIEEE754
TEST(BinaryOperationsTest, AddIEEE754) {
    std::string a = BinaryOperations::floatToIEEE754(1.0f);
    std::string b = BinaryOperations::floatToIEEE754(2.0f);
    EXPECT_EQ(BinaryOperations::addIEEE754(a, b), BinaryOperations::floatToIEEE754(3.0f));
}

// Тесты для add
TEST(BinaryOperationsTest, Add) {
    EXPECT_EQ(BinaryOperations::add("00000101", "00000010"), "00000111"); // 5 + 2 = 7
    EXPECT_EQ(BinaryOperations::add("11111011", "00000001"), "11111100"); // -5 + 1 = -4
    EXPECT_EQ(BinaryOperations::add("00000101", "11111011"), "00000000"); // 5 + (-5) = 0
}

// Тесты для intToBinary
TEST(BinaryOperationsTest, IntToBinary) {
    EXPECT_NO_THROW(BinaryOperations::intToBinary(5));
    EXPECT_NO_THROW(BinaryOperations::intToBinary(-5));
}

// Тесты для toStraightCode
TEST(BinaryOperationsTest, ToStraightCode) {
    EXPECT_NO_THROW(BinaryOperations::toStraightCode(5));
    EXPECT_NO_THROW(BinaryOperations::toStraightCode(-5));
}

// Тесты для toComplementCode
TEST(BinaryOperationsTest, ToComplementCode) {
    EXPECT_NO_THROW(BinaryOperations::toComplementCode("00000101"));
    EXPECT_NO_THROW(BinaryOperations::toComplementCode("11111011"));
}

// Тесты для multiply
TEST(BinaryOperationsTest, Multiply) {
    EXPECT_NO_THROW(BinaryOperations::multiply("00000101", "00000010"));
    EXPECT_NO_THROW(BinaryOperations::multiply("11111011", "00000001"));
}

// Тесты для divide
TEST(BinaryOperationsTest, Divide) {
    EXPECT_NO_THROW(BinaryOperations::divide("00001010", "00000010"));
    EXPECT_THROW(BinaryOperations::divide("00000100", "00000000"), std::invalid_argument);
}






int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}