#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <vector>
#include <string>

class Minimizer {
private:
    std::vector<std::vector<bool>> minterms; // Наборы для СДНФ
    std::vector<std::vector<bool>> maxterms; // Наборы для СКНФ
    int variables; // Количество переменных (a, b, c)

    // Вспомогательные методы
    std::string termToString(const std::vector<bool>& term, bool isDNF) const;
    int hammingDistance(const std::vector<bool>& t1, const std::vector<bool>& t2) const;
    std::vector<bool> glueTerms(const std::vector<bool>& t1, const std::vector<bool>& t2) const;
    bool isCovered(const std::vector<bool>& term, const std::vector<std::vector<bool>>& implicants) const;

public:
    Minimizer(int vars = 3); // По умолчанию 3 переменные (a, b, c)
    void addMinterm(const std::vector<bool>& term); // Добавить набор для СДНФ
    void addMaxterm(const std::vector<bool>& term); // Добавить набор для СКНФ

    // Методы минимизации
    std::string minimizeDNFCalculation(); // Расчетный метод для СДНФ
    std::string minimizeCNFCalculation(); // Расчетный метод для СКНФ
    std::string minimizeDNFCalcTable();   // Расчетно-табличный для СДНФ
    std::string minimizeCNFCalcTable();   // Расчетно-табличный для СКНФ
    std::string minimizeDNFKarnaugh();    // Табличный (карта Карно) для СДНФ
    std::string minimizeCNFKarnaugh();    // Табличный (карта Карно) для СКНФ
};

#endif