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
    std::string expression; // ���������� ���������
    std::vector<char> variables; // ������ ����������
    std::vector<std::map<char, bool>> truthTable; // ������� ����������

    // ��������������� ������
    bool evaluate(const std::string& expr, const std::map<char, bool>& values) const;
    void generateTruthTable();
    std::string getTerm(const std::map<char, bool>& row, bool isDNF) const;

public:
    // �����������
    LogicFunction(const std::string& expr);

    // ���������� ����
    std::string getDNF() const;

    // ���������� ����
    std::string getCNF() const;

    // �������� ����� ��� ����
    std::set<int> getDNFTerms() const;

    // �������� ����� ��� ����
    std::set<int> getCNFTerms() const;

    // ��������� �����
    int getIndexForm() const;

    // ����� ������� ����������
    void printTruthTable() const;
};

#endif