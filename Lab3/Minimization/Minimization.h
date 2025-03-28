#ifndef MINIMIZER_H
#define MINIMIZER_H

#include <vector>
#include <string>

class Minimizer {
private:
    std::vector<std::vector<bool>> minterms; // ������ ��� ����
    std::vector<std::vector<bool>> maxterms; // ������ ��� ����
    int variables; // ���������� ���������� (a, b, c)

    // ��������������� ������
    std::string termToString(const std::vector<bool>& term, bool isDNF) const;
    int hammingDistance(const std::vector<bool>& t1, const std::vector<bool>& t2) const;
    std::vector<bool> glueTerms(const std::vector<bool>& t1, const std::vector<bool>& t2) const;
    bool isCovered(const std::vector<bool>& term, const std::vector<std::vector<bool>>& implicants) const;

public:
    Minimizer(int vars = 3); // �� ��������� 3 ���������� (a, b, c)
    void addMinterm(const std::vector<bool>& term); // �������� ����� ��� ����
    void addMaxterm(const std::vector<bool>& term); // �������� ����� ��� ����

    // ������ �����������
    std::string minimizeDNFCalculation(); // ��������� ����� ��� ����
    std::string minimizeCNFCalculation(); // ��������� ����� ��� ����
    std::string minimizeDNFCalcTable();   // ��������-��������� ��� ����
    std::string minimizeCNFCalcTable();   // ��������-��������� ��� ����
    std::string minimizeDNFKarnaugh();    // ��������� (����� �����) ��� ����
    std::string minimizeCNFKarnaugh();    // ��������� (����� �����) ��� ����
};

#endif