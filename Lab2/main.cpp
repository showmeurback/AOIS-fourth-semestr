#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 2\AOIS-LR-2\LogicFunction.h"
#include <locale> 

void displayMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Вывести таблицу истинности\n";
    std::cout << "2. Построить СДНФ\n";
    std::cout << "3. Построить СКНФ\n";
    std::cout << "4. Вывести числовые формы\n";
    std::cout << "5. Вывести индексную форму\n";
    std::cout << "6. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "RU");

    std::string expr;
    std::cout << "Введите логическую функцию: ";
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
                std::cout << "СДНФ: " << logicFunction.getDNF() << "\n";
                break;
            case 3:
                std::cout << "СКНФ: " << logicFunction.getCNF() << "\n";
                break;
            case 4: {
                std::set<int> dnfTerms = logicFunction.getDNFTerms();
                std::set<int> cnfTerms = logicFunction.getCNFTerms();
                std::cout << "Числовая форма СДНФ: ";
                for (int term : dnfTerms) std::cout << term << " ";
                std::cout << "\nЧисловая форма СКНФ: ";
                for (int term : cnfTerms) std::cout << term << " ";
                std::cout << "\n";
                break;
            }
            case 5:
                std::cout << "Индексная форма: " << logicFunction.getIndexForm() << "\n";
                break;
            case 6:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } while (choice != 6);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}