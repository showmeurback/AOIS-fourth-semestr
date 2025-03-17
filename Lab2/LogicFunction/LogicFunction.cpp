#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 2\AOIS-LR-2\LogicFunction.h"
#include <cmath>

// Конструктор
LogicFunction::LogicFunction(const std::string& expr) : expression(expr) {
    // Определение переменных
    for (char ch : expr) {
        if (ch >= 'a' && ch <= 'e' && std::find(variables.begin(), variables.end(), ch) == variables.end()) {
            variables.push_back(ch);
        }
    }
    std::sort(variables.begin(), variables.end());

    // Генерация таблицы истинности
    generateTruthTable();
}

// Вычисление значения логического выражения
bool LogicFunction::evaluate(const std::string& expr, const std::map<char, bool>& values) const {
    std::vector<bool> stack;
    std::vector<char> operators;

    for (size_t i = 0; i < expr.size(); ++i) {
        char ch = expr[i];
        if (ch == ' ') continue; // Пропускаем пробелы

        if (ch >= 'a' && ch <= 'e') {
            // Если символ — переменная, добавляем её значение в стек
            stack.push_back(values.at(ch));
        }
        else if (ch == '!') {
            // Обработка отрицания
            operators.push_back(ch);
        }
        else if (ch == '&' || ch == '|' || ch == '-' || ch == '~') {
            // Обработка операций
            while (!operators.empty() && operators.back() != '(' &&
                (operators.back() == '!' || (operators.back() == '&' && ch != '!') ||
                    (operators.back() == '|' && ch != '!' && ch != '&'))) {
                char op = operators.back();
                operators.pop_back();

                if (op == '!') {
                    if (stack.empty()) throw std::runtime_error("Ошибка: недостаточно операндов для операции !");
                    bool a = stack.back(); stack.pop_back();
                    stack.push_back(!a);
                }
                else {
                    if (stack.size() < 2) throw std::runtime_error("Ошибка: недостаточно операндов для операции " + std::string(1, op));
                    bool b = stack.back(); stack.pop_back();
                    bool a = stack.back(); stack.pop_back();

                    if (op == '&') stack.push_back(a && b);
                    else if (op == '|') stack.push_back(a || b);
                    else if (op == '-') stack.push_back(!a || b);
                    else if (op == '~') stack.push_back((a && b) || (!a && !b));
                }
            }
            operators.push_back(ch);
        }
        else if (ch == '(') {
            // Открывающая скобка
            operators.push_back(ch);
        }
        else if (ch == ')') {
            // Закрывающая скобка
            while (!operators.empty() && operators.back() != '(') {
                char op = operators.back();
                operators.pop_back();

                if (op == '!') {
                    if (stack.empty()) throw std::runtime_error("Ошибка: недостаточно операндов для операции !");
                    bool a = stack.back(); stack.pop_back();
                    stack.push_back(!a);
                }
                else {
                    if (stack.size() < 2) throw std::runtime_error("Ошибка: недостаточно операндов для операции " + std::string(1, op));
                    bool b = stack.back(); stack.pop_back();
                    bool a = stack.back(); stack.pop_back();

                    if (op == '&') stack.push_back(a && b);
                    else if (op == '|') stack.push_back(a || b);
                    else if (op == '-') stack.push_back(!a || b);
                    else if (op == '~') stack.push_back((a && b) || (!a && !b));
                }
            }
            if (operators.empty() || operators.back() != '(') {
                throw std::runtime_error("Ошибка: несбалансированные скобки");
            }
            operators.pop_back(); // Удаляем '('
        }
    }

    // Обработка оставшихся операторов
    while (!operators.empty()) {
        char op = operators.back();
        operators.pop_back();

        if (op == '!') {
            if (stack.empty()) throw std::runtime_error("Ошибка: недостаточно операндов для операции !");
            bool a = stack.back(); stack.pop_back();
            stack.push_back(!a);
        }
        else {
            if (stack.size() < 2) throw std::runtime_error("Ошибка: недостаточно операндов для операции " + std::string(1, op));
            bool b = stack.back(); stack.pop_back();
            bool a = stack.back(); stack.pop_back();

            if (op == '&') stack.push_back(a && b);
            else if (op == '|') stack.push_back(a || b);
            else if (op == '-') stack.push_back(!a || b);
            else if (op == '~') stack.push_back((a && b) || (!a && !b));
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Ошибка: некорректное выражение");
    return stack.back();
}

// Генерация таблицы истинности
void LogicFunction::generateTruthTable() {
    int n = variables.size();
    for (int i = 0; i < (1 << n); ++i) {
        std::map<char, bool> row;
        for (int j = 0; j < n; ++j) {
            row[variables[j]] = (i >> j) & 1;
        }
        try {
            bool result = evaluate(expression, row);
            row['0'] = false;
            row['1'] = true;
            truthTable.push_back(row);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при вычислении выражения: " << e.what() << "\n";
            throw;
        }
    }
}

// Получение терма для СДНФ или СКНФ
std::string LogicFunction::getTerm(const std::map<char, bool>& row, bool isDNF) const {
    std::string term;
    for (char var : variables) {
        if (isDNF) {
            term += (row.at(var) ? "" : "!") + std::string(1, var) + " & ";
        }
        else {
            term += (row.at(var) ? "" : "!") + std::string(1, var) + " | ";
        }
    }
    if (!term.empty()) {
        term.erase(term.size() - 3); // Удаляем последний " & " или " | "
    }
    return term;
}

// Построение СДНФ
std::string LogicFunction::getDNF() const {
    std::string dnf;
    for (const auto& row : truthTable) {
        if (evaluate(expression, row)) {
            dnf += "(" + getTerm(row, true) + ") | ";
        }
    }
    if (!dnf.empty()) {
        dnf.erase(dnf.size() - 3); // Удаляем последний " | "
    }
    return dnf.empty() ? "Нет СДНФ" : dnf;
}

// Построение СКНФ
std::string LogicFunction::getCNF() const {
    std::string cnf;
    for (const auto& row : truthTable) {
        if (!evaluate(expression, row)) {
            cnf += "(" + getTerm(row, false) + ") & ";
        }
    }
    if (!cnf.empty()) {
        cnf.erase(cnf.size() - 3); // Удаляем последний " & "
    }
    return cnf.empty() ? "Нет СКНФ" : cnf;
}

// Числовая форма для СДНФ
std::set<int> LogicFunction::getDNFTerms() const {
    std::set<int> terms;
    int index = 0;
    for (const auto& row : truthTable) {
        if (evaluate(expression, row)) {
            terms.insert(index);
        }
        index++;
    }
    return terms;
}

// Числовая форма для СКНФ
std::set<int> LogicFunction::getCNFTerms() const {
    std::set<int> terms;
    int index = 0;
    for (const auto& row : truthTable) {
        if (!evaluate(expression, row)) {
            terms.insert(index);
        }
        index++;
    }
    return terms;
}

// Индексная форма
int LogicFunction::getIndexForm() const {
    int index = 0;
    for (const auto& row : truthTable) {
        index = (index << 1) | (evaluate(expression, row) ? 1 : 0);
    }
    return index;
}

// Вывод таблицы истинности
void LogicFunction::printTruthTable() const {
    std::cout << "Таблица истинности:\n";
    for (char var : variables) {
        std::cout << var << " ";
    }
    std::cout << "Result\n";
    for (const auto& row : truthTable) {
        for (char var : variables) {
            std::cout << row.at(var) << " ";
        }
        try {
            std::cout << evaluate(expression, row) << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}