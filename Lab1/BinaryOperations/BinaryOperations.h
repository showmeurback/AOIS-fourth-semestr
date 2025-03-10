#pragma once
#include <string>
#include <iostream>

class BinaryOperations {
public:
    static std::string intToBinary(int number, bool signedNum = true);
    static std::string toStraightCode(int number);
    static std::string toReverseCode(const std::string& binary);
    static std::string toComplementCode(const std::string& binary);
    static std::string add(const std::string& a, const std::string& b);
    static std::string subtract(const std::string& a, const std::string& b);
    static std::string multiply(const std::string& a, const std::string& b);
    static std::string divide(const std::string& a, const std::string& b);
    static int binaryToInt(const std::string& binary);
    static std::string floatToIEEE754(float number);
    static float ieee754ToDecimal(const std::string& binary);
    static std::string addIEEE754(const std::string& a, const std::string& b);
};