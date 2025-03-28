#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <vector>
#include <string>

class Minimizer {
private:
    std::vector<std::vector<bool>> minterms; 
    std::vector<std::vector<bool>> maxterms; 
    int variables; 

    // Âñïîìîãàòåëüíûå ìåòîäû
    std::string termToString(const std::vector<bool>& term, bool isDNF) const;
    int hammingDistance(const std::vector<bool>& t1, const std::vector<bool>& t2) const;
    std::vector<bool> glueTerms(const std::vector<bool>& t1, const std::vector<bool>& t2) const;
    bool isCovered(const std::vector<bool>& term, const std::vector<std::vector<bool>>& implicants) const;

public:
    Minimizer(int vars = 3); // Ïî óìîë÷àíèþ 3 ïåðåìåííûå (a, b, c)
    void addMinterm(const std::vector<bool>& term); // Äîáàâèòü íàáîð äëÿ ÑÄÍÔ
    void addMaxterm(const std::vector<bool>& term); // Äîáàâèòü íàáîð äëÿ ÑÊÍÔ

    // Ìåòîäû ìèíèìèçàöèè
    std::string minimizeDNFCalculation(); // Ðàñ÷åòíûé ìåòîä äëÿ ÑÄÍÔ
    std::string minimizeCNFCalculation(); // Ðàñ÷åòíûé ìåòîä äëÿ ÑÊÍÔ
    std::string minimizeDNFCalcTable();   // Ðàñ÷åòíî-òàáëè÷íûé äëÿ ÑÄÍÔ
    std::string minimizeCNFCalcTable();   // Ðàñ÷åòíî-òàáëè÷íûé äëÿ ÑÊÍÔ
    std::string minimizeDNFKarnaugh();    // Òàáëè÷íûé (êàðòà Êàðíî) äëÿ ÑÄÍÔ
    std::string minimizeCNFKarnaugh();    // Òàáëè÷íûé (êàðòà Êàðíî) äëÿ ÑÊÍÔ
};

#endif
