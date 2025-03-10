#include "BinaryOperations.h"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <stdexcept>

std::string BinaryOperations::intToBinary(int number, bool signedNum) {
    if (signedNum && (number < -128 || number > 127))
        throw std::overflow_error("Число за пределами 8 бит");

    bool isNegative = number < 0;
    number = std::abs(number);

    std::string binary;
    do {
        binary = std::to_string(number % 2) + binary;
        number /= 2;
    } while (number > 0);

    // Дополняем до 8 бит
    binary = std::string(8 - binary.length(), '0') + binary;

    if (signedNum) {
        if (isNegative) {
            // Преобразование в дополнительный код
            binary = toComplementCode(binary);
        }
        else {
            binary = "0" + binary.substr(1);
        }
    }

    return binary;
}

std::string BinaryOperations::toStraightCode(int number) {
    return intToBinary(number, true);
}

std::string BinaryOperations::toReverseCode(const std::string& binary) {
    if (binary[0] == '0') return binary; // Прямой код

    std::string inverted = binary;
    for (size_t i = 0; i < inverted.size(); ++i) {
        inverted[i] = (inverted[i] == '0') ? '1' : '0';
    }
    return inverted;
}

std::string BinaryOperations::toComplementCode(const std::string& binary) {
    if (binary[0] == '0') return binary;

    std::string reversed = toReverseCode(binary);
    std::string one(8, '0');
    one[7] = '1';
    return add(reversed, one);
}

std::string BinaryOperations::add(const std::string& a, const std::string& b) {
    std::string result(8, '0');
    bool carry = false;

    for (int i = 7; i >= 0; --i) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result[i] = '0' + (sum % 2);
        carry = (sum > 1);
    }

    return result;
}

std::string BinaryOperations::subtract(const std::string& a_straight, const std::string& b_straight) {
    int a_value = binaryToInt(a_straight);
    int b_value = binaryToInt(b_straight);
    return intToBinary(a_value - b_value);
}

std::string BinaryOperations::multiply(const std::string& a, const std::string& b) {
    int num1 = binaryToInt(a);
    int num2 = binaryToInt(b);
    return intToBinary(num1 * num2);
}

std::string BinaryOperations::divide(const std::string& a, const std::string& b) {
    int dividend = binaryToInt(a);
    int divisor = binaryToInt(b);

    if (divisor == 0)
        throw std::invalid_argument("Деление на ноль");

    int quotient = dividend / divisor;
    int remainder = dividend % divisor;

    std::string result = intToBinary(quotient, true);
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty()) result = "0";

    remainder = std::abs(remainder);
    divisor = std::abs(divisor);

    result += ".";
    for (int i = 0; i < 5; ++i) {
        remainder *= 2;
        int bit = (remainder >= divisor) ? 1 : 0;
        result += std::to_string(bit);
        remainder -= bit * divisor;
    }

    return result;
}

int BinaryOperations::binaryToInt(const std::string& binary) {
    if (binary[0] == '0') {
        return std::stoi(binary, nullptr, 2);
    }
    else {
        std::string complement = binary;
        for (char& c : complement) {
            c = (c == '0') ? '1' : '0';
        }
        int value = std::stoi(complement, nullptr, 2) + 1;
        return -value;
    }
}

std::string BinaryOperations::floatToIEEE754(float number) {
    union {
        float f;
        unsigned int i;
    } converter;
    converter.f = number;
    return std::bitset<32>(converter.i).to_string();
}

float BinaryOperations::ieee754ToDecimal(const std::string& binary) {
    std::bitset<32> bits(binary);
    union {
        unsigned int i;
        float f;
    } converter;
    converter.i = bits.to_ulong();
    return converter.f;
}

std::string BinaryOperations::addIEEE754(const std::string& a, const std::string& b) {
    float num1 = ieee754ToDecimal(a);
    float num2 = ieee754ToDecimal(b);
    return floatToIEEE754(num1 + num2);
}