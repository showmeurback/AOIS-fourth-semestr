#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 3\AOIS-LR-3\Minimization.h"
#include "Minimization.h"
#include <iostream>
#include <vector>
#include <sstream>  // Добавлен для std::stringstream
#include <string>   // Добавлен для std::string

using namespace std;

void printHelp() {
    cout << "Инструкция по вводу:\n";
    cout << "1. Введите количество переменных (например, 3 для a,b,c)\n";
    cout << "2. Выберите тип функции (1 - СДНФ, 2 - СКНФ)\n";
    cout << "3. Введите наборы значений переменных через пробел (1 - true, 0 - false)\n";
    cout << "   Например, для набора a=1, b=0, c=1 введите: 1 0 1\n";
    cout << "4. Введите -1 для завершения ввода\n\n";
}

vector<bool> parseInput(const string& input, int varCount) {
    vector<bool> term;
    stringstream ss(input);
    int val;

    for (int i = 0; i < varCount; ++i) {
        if (!(ss >> val)) {  // Проверка на успешное чтение
            throw runtime_error("Неверный формат ввода");
        }
        term.push_back(val == 1);
    }
    return term;
}

int main() {
    setlocale(LC_ALL, "RU");

    printHelp();

    // Ввод количества переменных
    int varCount;
    cout << "Введите количество переменных (2-4): ";
    cin >> varCount;
    cin.ignore();

    if (varCount < 2 || varCount > 4) {
        cerr << "Ошибка: поддерживается только 2-4 переменные\n";
        return 1;
    }

    // Выбор типа функции
    int functionType;
    cout << "Выберите тип функции (1 - СДНФ, 2 - СКНФ): ";
    cin >> functionType;
    cin.ignore();

    if (functionType != 1 && functionType != 2) {
        cerr << "Ошибка: неверный тип функции\n";
        return 1;
    }

    Minimizer minimizer(varCount);
    cout << "Вводите наборы значений (по " << varCount << " чисел через пробел), -1 для завершения:\n";

    // Ввод наборов
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input == "-1") break;

        try {
            vector<bool> term = parseInput(input, varCount);
            if (term.size() != varCount) {
                cout << "Ошибка: введено неверное количество значений\n";
                continue;
            }

            if (functionType == 1) {
                minimizer.addMinterm(term);
            }
            else {
                minimizer.addMaxterm(term);
            }
        }
        catch (const exception& e) {
            cout << "Ошибка ввода: " << e.what() << ". Попробуйте снова.\n";
        }
    }

    // Минимизация и вывод результатов
    if (functionType == 1) {
        cout << "\nРезультаты минимизации СДНФ:\n";
        cout << "1. Расчетный метод:\n" << minimizer.minimizeDNFCalculation() << endl;
        cout << "2. Расчетно-табличный метод:\n" << minimizer.minimizeDNFCalcTable() << endl;
        cout << "3. Метод Карно:\n" << minimizer.minimizeDNFKarnaugh() << endl;
    }
    else {
        cout << "\nРезультаты минимизации СКНФ:\n";
        cout << "1. Расчетный метод:\n" << minimizer.minimizeCNFCalculation() << endl;
        cout << "2. Расчетно-табличный метод:\n" << minimizer.minimizeCNFCalcTable() << endl;
        cout << "3. Метод Карно:\n" << minimizer.minimizeCNFKarnaugh() << endl;
    }

    return 0;
}