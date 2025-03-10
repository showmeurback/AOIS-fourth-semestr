#include <iostream>
#include "BinaryOperations.h"

void showMainMenu() {
    std::cout << "Главное меню:\n"
        << "1. Работа с целыми числами\n"
        << "2. Работа с IEEE-754\n"
        << "0. Выход\n";
}

void integerOperationsMenu() {
    int choice;
    do {
        std::cout << "\nОперации с целыми числами:\n"
            << "1. Перевод в коды\n"
            << "2. Сложение\n"
            << "3. Вычитание\n"
            << "4. Умножение\n"
            << "5. Деление\n"
            << "0. Назад\n"
            << "Выберите операцию: ";
        std::cin >> choice;

        try {
            int num1, num2;
            std::string bin1, bin2;

            switch (choice) {
            case 1:
                std::cout << "Введите число: ";
                std::cin >> num1;
                std::cout << "Прямой код: " << BinaryOperations::toStraightCode(num1) << "\n"
                    << "Обратный код: " << BinaryOperations::toReverseCode(BinaryOperations::toStraightCode(num1)) << "\n"
                    << "Дополнительный код: " << BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num1)) << "\n";
                break;
            case 2:
                std::cout << "Введите первое число: ";
                std::cin >> num1;
                std::cout << "Введите второе число: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num1));
                bin2 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num2));
                std::cout << "Результат: " << BinaryOperations::add(bin1, bin2) << " ("
                    << BinaryOperations::binaryToInt(BinaryOperations::add(bin1, bin2)) << ")\n";
                break;
            case 3:
                std::cout << "Введите первое число: ";
                std::cin >> num1;
                std::cout << "Введите второе число: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num1));
                bin2 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num2));
                std::cout << "Результат: " << BinaryOperations::subtract(bin1, bin2) << " ("
                    << BinaryOperations::binaryToInt(BinaryOperations::subtract(bin1, bin2)) << ")\n";
                break;
            case 4:
                std::cout << "Введите первое число: ";
                std::cin >> num1;
                std::cout << "Введите второе число: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toStraightCode(num1);
                bin2 = BinaryOperations::toStraightCode(num2);
                std::cout << "Результат: " << BinaryOperations::multiply(bin1, bin2) << " ("
                    << BinaryOperations::binaryToInt(BinaryOperations::multiply(bin1, bin2)) << ")\n";
                break;
            case 5:
                std::cout << "Введите делимое: ";
                std::cin >> num1;
                std::cout << "Введите делитель: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toStraightCode(num1);
                bin2 = BinaryOperations::toStraightCode(num2);
                std::cout << "Результат: " << BinaryOperations::divide(bin1, bin2) << "\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void floatOperationsMenu() {
    int choice;
    do {
        std::cout << "\nОперации с IEEE-754:\n"
            << "1. Сложение\n"
            << "2. Перевод в IEEE-754\n"
            << "3. Перевод из IEEE-754\n"
            << "0. Назад\n"
            << "Выберите операцию: ";
        std::cin >> choice;

        try {
            float num1, num2;
            std::string bin1, bin2;

            switch (choice) {
            case 1:
                std::cout << "Введите первое число: ";
                std::cin >> num1;
                std::cout << "Введите второе число: ";
                std::cin >> num2;
                bin1 = BinaryOperations::floatToIEEE754(num1);
                bin2 = BinaryOperations::floatToIEEE754(num2);
                std::cout << "Результат: " << BinaryOperations::addIEEE754(bin1, bin2) << "\n"
                    << "Десятичный вид: " << BinaryOperations::ieee754ToDecimal(BinaryOperations::addIEEE754(bin1, bin2)) << "\n";
                break;
            case 2:
                std::cout << "Введите число: ";
                std::cin >> num1;
                std::cout << "IEEE-754: " << BinaryOperations::floatToIEEE754(num1) << "\n";
                break;
            case 3:
                std::cout << "Введите двоичное представление (32 бита): ";
                std::cin >> bin1;
                std::cout << "Десятичное число: " << BinaryOperations::ieee754ToDecimal(bin1) << "\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice;
    do {
        showMainMenu();
        std::cout << "Выберите раздел: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            integerOperationsMenu();
            break;
        case 2:
            floatOperationsMenu();
            break;
        }
    } while (choice != 0);

    return 0;
}