#include <iostream>
#include "BinaryOperations.h"

void showMainMenu() {
    std::cout << "������� ����:\n"
        << "1. ������ � ������ �������\n"
        << "2. ������ � IEEE-754\n"
        << "0. �����\n";
}

void integerOperationsMenu() {
    int choice;
    do {
        std::cout << "\n�������� � ������ �������:\n"
            << "1. ������� � ����\n"
            << "2. ��������\n"
            << "3. ���������\n"
            << "4. ���������\n"
            << "5. �������\n"
            << "0. �����\n"
            << "�������� ��������: ";
        std::cin >> choice;

        try {
            int num1, num2;
            std::string bin1, bin2;

            switch (choice) {
            case 1:
                std::cout << "������� �����: ";
                std::cin >> num1;
                std::cout << "������ ���: " << BinaryOperations::toStraightCode(num1) << "\n"
                    << "�������� ���: " << BinaryOperations::toReverseCode(BinaryOperations::toStraightCode(num1)) << "\n"
                    << "�������������� ���: " << BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num1)) << "\n";
                break;
            case 2:
                std::cout << "������� ������ �����: ";
                std::cin >> num1;
                std::cout << "������� ������ �����: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num1));
                bin2 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num2));
                std::cout << "���������: " << BinaryOperations::add(bin1, bin2) << " ("
                    << BinaryOperations::binaryToInt(BinaryOperations::add(bin1, bin2)) << ")\n";
                break;
            case 3:
                std::cout << "������� ������ �����: ";
                std::cin >> num1;
                std::cout << "������� ������ �����: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num1));
                bin2 = BinaryOperations::toComplementCode(BinaryOperations::toStraightCode(num2));
                std::cout << "���������: " << BinaryOperations::subtract(bin1, bin2) << " ("
                    << BinaryOperations::binaryToInt(BinaryOperations::subtract(bin1, bin2)) << ")\n";
                break;
            case 4:
                std::cout << "������� ������ �����: ";
                std::cin >> num1;
                std::cout << "������� ������ �����: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toStraightCode(num1);
                bin2 = BinaryOperations::toStraightCode(num2);
                std::cout << "���������: " << BinaryOperations::multiply(bin1, bin2) << " ("
                    << BinaryOperations::binaryToInt(BinaryOperations::multiply(bin1, bin2)) << ")\n";
                break;
            case 5:
                std::cout << "������� �������: ";
                std::cin >> num1;
                std::cout << "������� ��������: ";
                std::cin >> num2;
                bin1 = BinaryOperations::toStraightCode(num1);
                bin2 = BinaryOperations::toStraightCode(num2);
                std::cout << "���������: " << BinaryOperations::divide(bin1, bin2) << "\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "������: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void floatOperationsMenu() {
    int choice;
    do {
        std::cout << "\n�������� � IEEE-754:\n"
            << "1. ��������\n"
            << "2. ������� � IEEE-754\n"
            << "3. ������� �� IEEE-754\n"
            << "0. �����\n"
            << "�������� ��������: ";
        std::cin >> choice;

        try {
            float num1, num2;
            std::string bin1, bin2;

            switch (choice) {
            case 1:
                std::cout << "������� ������ �����: ";
                std::cin >> num1;
                std::cout << "������� ������ �����: ";
                std::cin >> num2;
                bin1 = BinaryOperations::floatToIEEE754(num1);
                bin2 = BinaryOperations::floatToIEEE754(num2);
                std::cout << "���������: " << BinaryOperations::addIEEE754(bin1, bin2) << "\n"
                    << "���������� ���: " << BinaryOperations::ieee754ToDecimal(BinaryOperations::addIEEE754(bin1, bin2)) << "\n";
                break;
            case 2:
                std::cout << "������� �����: ";
                std::cin >> num1;
                std::cout << "IEEE-754: " << BinaryOperations::floatToIEEE754(num1) << "\n";
                break;
            case 3:
                std::cout << "������� �������� ������������� (32 ����): ";
                std::cin >> bin1;
                std::cout << "���������� �����: " << BinaryOperations::ieee754ToDecimal(bin1) << "\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "������: " << e.what() << "\n";
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice;
    do {
        showMainMenu();
        std::cout << "�������� ������: ";
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