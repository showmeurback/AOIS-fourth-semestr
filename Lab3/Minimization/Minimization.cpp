#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 3\AOIS-LR-3\Minimization.h"
#include <sstream>
#include <iostream>
#include <iomanip>

Minimizer::Minimizer(int vars) : variables(vars) {}

void Minimizer::addMinterm(const std::vector<bool>& term) {
    minterms.push_back(term);
}

void Minimizer::addMaxterm(const std::vector<bool>& term) {
    maxterms.push_back(term);
}

std::string Minimizer::termToString(const std::vector<bool>& term, bool isDNF) const {
    std::string result;
    bool first = true;
    for (int i = 0; i < variables; ++i) {
        if (i < term.size()) {
            if (!first) result += (isDNF ? "&" : "|");
            if (!term[i]) result += "!";
            result += char('a' + i);
            first = false;
        }
    }
    return result.empty() ? (isDNF ? "0" : "1") : result;
}

int Minimizer::hammingDistance(const std::vector<bool>& t1, const std::vector<bool>& t2) const {
    int dist = 0;
    for (int i = 0; i < t1.size(); ++i) {
        if (t1[i] != t2[i]) dist++;
    }
    return dist;
}

std::vector<bool> Minimizer::glueTerms(const std::vector<bool>& t1, const std::vector<bool>& t2) const {
    std::vector<bool> result(t1);
    for (int i = 0; i < t1.size(); ++i) {
        if (t1[i] != t2[i]) {
            result[i] = false; // Помечаем различие как "не участвует"
        }
    }
    return result;
}

bool Minimizer::isCovered(const std::vector<bool>& term, const std::vector<std::vector<bool>>& implicants) const {
    for (const auto& imp : implicants) {
        bool match = true;
        for (int i = 0; i < variables; ++i) {
            if (imp[i] != term[i]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

// 1. Расчетный метод для СДНФ
std::string Minimizer::minimizeDNFCalculation() {
    std::stringstream ss;
    ss << "Расчетный метод для СДНФ:\nИсходная СДНФ: ";
    for (const auto& term : minterms) {
        ss << "(" << termToString(term, true) << ") | "; // | вместо ∨
    }
    ss.seekp(-3, std::ios_base::end); // Удаляем последний " | "
    ss << "\nЭтап склеивания:\n";

    std::vector<std::vector<bool>> implicants = minterms;
    std::vector<std::vector<bool>> nextImplicants;
    bool glued;

    do {
        glued = false;
        std::vector<bool> used(implicants.size(), false);
        for (size_t i = 0; i < implicants.size(); ++i) {
            for (size_t j = i + 1; j < implicants.size(); ++j) {
                if (hammingDistance(implicants[i], implicants[j]) == 1) {
                    nextImplicants.push_back(glueTerms(implicants[i], implicants[j]));
                    ss << termToString(implicants[i], true) << " | " << termToString(implicants[j], true)
                        << " -> " << termToString(nextImplicants.back(), true) << "\n"; // | и ->
                    used[i] = used[j] = true;
                    glued = true;
                }
            }
        }
        for (size_t i = 0; i < implicants.size(); ++i) {
            if (!used[i]) nextImplicants.push_back(implicants[i]);
        }
        implicants = nextImplicants;
        nextImplicants.clear();
    } while (glued);

    ss << "Результат: ";
    for (size_t i = 0; i < implicants.size(); ++i) {
        ss << termToString(implicants[i], true);
        if (i < implicants.size() - 1) ss << " | "; // | вместо ∨
    }
    ss << "\n";
    return ss.str();
}

// 2. Расчетный метод для СКНФ
std::string Minimizer::minimizeCNFCalculation() {
    std::stringstream ss;
    ss << "Расчетный метод для СКНФ:\nИсходная СКНФ: ";
    for (const auto& term : maxterms) {
        ss << "(" << termToString(term, false) << ") & "; // & вместо ∧
    }
    ss.seekp(-3, std::ios_base::end); // Удаляем последний " & "
    ss << "\nЭтап склеивания:\n";

    std::vector<std::vector<bool>> implicants = maxterms;
    std::vector<std::vector<bool>> nextImplicants;
    bool glued;

    do {
        glued = false;
        std::vector<bool> used(implicants.size(), false);
        for (size_t i = 0; i < implicants.size(); ++i) {
            for (size_t j = i + 1; j < implicants.size(); ++j) {
                if (hammingDistance(implicants[i], implicants[j]) == 1) {
                    nextImplicants.push_back(glueTerms(implicants[i], implicants[j]));
                    ss << termToString(implicants[i], false) << " & " << termToString(implicants[j], false)
                        << " -> " << termToString(nextImplicants.back(), false) << "\n"; // & и ->
                    used[i] = used[j] = true;
                    glued = true;
                }
            }
        }
        for (size_t i = 0; i < implicants.size(); ++i) {
            if (!used[i]) nextImplicants.push_back(implicants[i]);
        }
        implicants = nextImplicants;
        nextImplicants.clear();
    } while (glued);

    ss << "Результат: ";
    for (size_t i = 0; i < implicants.size(); ++i) {
        ss << "(" << termToString(implicants[i], false) << ")";
        if (i < implicants.size() - 1) ss << " & "; // & вместо ∧
    }
    ss << "\n";
    return ss.str();
}

// 3. Расчетно-табличный метод для СДНФ
std::string Minimizer::minimizeDNFCalcTable() {
    std::stringstream ss;
    ss << "Расчетно-табличный метод для СДНФ:\nЭтап склеивания:\n";

    std::vector<std::vector<bool>> implicants = minterms;
    std::vector<std::vector<bool>> nextImplicants;
    bool glued;

    do {
        glued = false;
        std::vector<bool> used(implicants.size(), false);
        for (size_t i = 0; i < implicants.size(); ++i) {
            for (size_t j = i + 1; j < implicants.size(); ++j) {
                if (hammingDistance(implicants[i], implicants[j]) == 1) {
                    nextImplicants.push_back(glueTerms(implicants[i], implicants[j]));
                    ss << termToString(implicants[i], true) << " | " << termToString(implicants[j], true)
                        << " -> " << termToString(nextImplicants.back(), true) << "\n"; // | и ->
                    used[i] = used[j] = true;
                    glued = true;
                }
            }
        }
        for (size_t i = 0; i < implicants.size(); ++i) {
            if (!used[i]) nextImplicants.push_back(implicants[i]);
        }
        implicants = nextImplicants;
        nextImplicants.clear();
    } while (glued);

    ss << "\nТаблица покрытия:\n";
    ss << std::setw(10) << "Импликанты";
    for (const auto& term : minterms) {
        ss << std::setw(10) << termToString(term, true);
    }
    ss << "\n";
    for (const auto& imp : implicants) {
        ss << std::setw(10) << termToString(imp, true);
        for (const auto& term : minterms) {
            bool covers = true;
            for (int i = 0; i < variables; ++i) {
                if (imp[i] && !term[i]) {
                    covers = false;
                    break;
                }
            }
            ss << std::setw(10) << (covers ? "X" : " ");
        }
        ss << "\n";
    }

    ss << "Результат: ";
    for (size_t i = 0; i < implicants.size(); ++i) {
        ss << termToString(implicants[i], true);
        if (i < implicants.size() - 1) ss << " | "; // | вместо ∨
    }
    ss << "\n";
    return ss.str();
}

// 4. Расчетно-табличный метод для СКНФ
std::string Minimizer::minimizeCNFCalcTable() {
    std::stringstream ss;
    ss << "Расчетно-табличный метод для СКНФ:\nЭтап склеивания:\n";

    std::vector<std::vector<bool>> implicants = maxterms;
    std::vector<std::vector<bool>> nextImplicants;
    bool glued;

    do {
        glued = false;
        std::vector<bool> used(implicants.size(), false);
        for (size_t i = 0; i < implicants.size(); ++i) {
            for (size_t j = i + 1; j < implicants.size(); ++j) {
                if (hammingDistance(implicants[i], implicants[j]) == 1) {
                    nextImplicants.push_back(glueTerms(implicants[i], implicants[j]));
                    ss << termToString(implicants[i], false) << " & " << termToString(implicants[j], false)
                        << " -> " << termToString(nextImplicants.back(), false) << "\n"; // & и ->
                    used[i] = used[j] = true;
                    glued = true;
                }
            }
        }
        for (size_t i = 0; i < implicants.size(); ++i) {
            if (!used[i]) nextImplicants.push_back(implicants[i]);
        }
        implicants = nextImplicants;
        nextImplicants.clear();
    } while (glued);

    ss << "\nТаблица покрытия:\n";
    ss << std::setw(10) << "Импликанты";
    for (const auto& term : maxterms) {
        ss << std::setw(10) << termToString(term, false);
    }
    ss << "\n";
    for (const auto& imp : implicants) {
        ss << std::setw(10) << termToString(imp, false);
        for (const auto& term : maxterms) {
            bool covers = true;
            for (int i = 0; i < variables; ++i) {
                if (!imp[i] && term[i]) {
                    covers = false;
                    break;
                }
            }
            ss << std::setw(10) << (covers ? "X" : " ");
        }
        ss << "\n";
    }

    ss << "Результат: ";
    for (size_t i = 0; i < implicants.size(); ++i) {
        ss << "(" << termToString(implicants[i], false) << ")";
        if (i < implicants.size() - 1) ss << " & "; // & вместо ∧
    }
    ss << "\n";
    return ss.str();
}

// 5. Табличный метод (Карно) для СДНФ
std::string Minimizer::minimizeDNFKarnaugh() {
    std::stringstream ss;
    ss << "Табличный метод (Карно) для СДНФ:\nКарта Карно:\n";
    int map[2][4] = { 0 }; // Карта для 3 переменных (a, bc)

    for (const auto& term : minterms) {
        int row = term[0] ? 1 : 0;
        int col = (term[1] ? 2 : 0) + (term[2] ? 1 : 0);
        map[row][col] = 1;
    }

    ss << std::setw(8) << " " << std::setw(8) << "bc=00" << std::setw(8) << "bc=01" << std::setw(8) << "bc=11" << std::setw(8) << "bc=10\n";
    ss << std::setw(8) << "a=0" << std::setw(8) << map[0][0] << std::setw(8) << map[0][1] << std::setw(8) << map[0][3] << std::setw(8) << map[0][2] << "\n";
    ss << std::setw(8) << "a=1" << std::setw(8) << map[1][0] << std::setw(8) << map[1][1] << std::setw(8) << map[1][3] << std::setw(8) << map[1][2] << "\n";

    ss << "Результат: ";
    if (map[1][0] && map[1][1] && map[1][2] && map[1][3]) ss << "a";
    if (map[0][3] && map[1][3]) {
        if (!ss.str().empty()) ss << " | "; // | вместо ∨
        ss << "b&c"; // & вместо ∧
    }
    ss << "\n";
    return ss.str();
}

// 6. Табличный метод (Карно) для СКНФ
std::string Minimizer::minimizeCNFKarnaugh() {
    std::stringstream ss;
    ss << "Табличный метод (Карно) для СКНФ:\nКарта Карно:\n";
    int map[2][4] = { 1 }; // Карта для 3 переменных (a, bc), изначально все 1

    for (const auto& term : maxterms) {
        int row = term[0] ? 1 : 0;
        int col = (term[1] ? 2 : 0) + (term[2] ? 1 : 0);
        map[row][col] = 0;
    }

    ss << std::setw(8) << " " << std::setw(8) << "bc=00" << std::setw(8) << "bc=01" << std::setw(8) << "bc=11" << std::setw(8) << "bc=10\n";
    ss << std::setw(8) << "a=0" << std::setw(8) << map[0][0] << std::setw(8) << map[0][1] << std::setw(8) << map[0][3] << std::setw(8) << map[0][2] << "\n";
    ss << std::setw(8) << "a=1" << std::setw(8) << map[1][0] << std::setw(8) << map[1][1] << std::setw(8) << map[1][3] << std::setw(8) << map[1][2] << "\n";

    ss << "Результат: ";
    if (!map[0][0]) ss << "(!a|!b|!c)"; // ! и | вместо ¬ и ∨
    if (!map[0][1]) {
        if (!ss.str().empty()) ss << " & "; // & вместо ∧
        ss << "(!a|!b|c)"; // ! и | вместо ¬ и ∨
    }
    ss << "\n";
    return ss.str();
}
