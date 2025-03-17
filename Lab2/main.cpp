#include "D:\BSUIR\2 ����\4 �������\����\�� 2\AOIS-LR-2\LogicFunction.h"
#include <locale> 

void displayMenu() {
    std::cout << "\n����:\n";
    std::cout << "1. ������� ������� ����������\n";
    std::cout << "2. ��������� ����\n";
    std::cout << "3. ��������� ����\n";
    std::cout << "4. ������� �������� �����\n";
    std::cout << "5. ������� ��������� �����\n";
    std::cout << "6. �����\n";
    std::cout << "�������� ��������: ";
}

int main() {
    setlocale(LC_ALL, "RU");

    std::string expr;
    std::cout << "������� ���������� �������: ";
    std::getline(std::cin, expr);

    try {
        LogicFunction logicFunction(expr);

        int choice;
        do {
            displayMenu();
            std::cin >> choice;
            std::cin.ignore(); 

            switch (choice) {
            case 1:
                logicFunction.printTruthTable();
                break;
            case 2:
                std::cout << "����: " << logicFunction.getDNF() << "\n";
                break;
            case 3:
                std::cout << "����: " << logicFunction.getCNF() << "\n";
                break;
            case 4: {
                std::set<int> dnfTerms = logicFunction.getDNFTerms();
                std::set<int> cnfTerms = logicFunction.getCNFTerms();
                std::cout << "�������� ����� ����: ";
                for (int term : dnfTerms) std::cout << term << " ";
                std::cout << "\n�������� ����� ����: ";
                for (int term : cnfTerms) std::cout << term << " ";
                std::cout << "\n";
                break;
            }
            case 5:
                std::cout << "��������� �����: " << logicFunction.getIndexForm() << "\n";
                break;
            case 6:
                std::cout << "�����...\n";
                break;
            default:
                std::cout << "�������� �����. ���������� �����.\n";
            }
        } while (choice != 6);
    }
    catch (const std::exception& e) {
        std::cerr << "������: " << e.what() << "\n";
    }

    return 0;
}