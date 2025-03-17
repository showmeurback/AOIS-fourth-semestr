#ifndef LOGICFUNCTION_HPP
#define LOGICFUNCTION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

class LogicFunction {
private:
    std::string expression; // Логическое выражение
    std::vector<char> variables; // Список переменных
    std::vector<std::map<char, bool>> truthTable; // Таблица истинности

    // Вспомогательные методы
    bool evaluate(const std::string& expr, const std::map<char, bool>& values) const;
    void generateTruthTable();
    std::string getTerm(const std::map<char, bool>& row, bool isDNF) const;

public:
    // Конструктор
    LogicFunction(const std::string& expr);

    // Построение СДНФ
    std::string getDNF() const;

    // Построение СКНФ
    std::string getCNF() const;

    // Числовая форма для СДНФ
    std::set<int> getDNFTerms() const;

    // Числовая форма для СКНФ
    std::set<int> getCNFTerms() const;

    // Индексная форма
    int getIndexForm() const;

    // Вывод таблицы истинности
    void printTruthTable() const;
};

#endif