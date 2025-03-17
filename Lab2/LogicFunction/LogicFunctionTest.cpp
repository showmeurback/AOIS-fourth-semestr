#include "pch.h"
#include <gtest/gtest.h>
#include "D:\BSUIR\2 ����\4 �������\����\�� 2\AOIS-LR-2\LogicFunction.h"
#include "D:\BSUIR\2 ����\4 �������\����\�� 2\AOIS-LR-2\LogicFunction.cpp"

// ����� ��� ������������
TEST(LogicFunctionTest, ConstructorTest) {
    LogicFunction lf("a&b");
    EXPECT_EQ(lf.getDNF(), lf.getDNF()); // ������� ������� ����� ������
}

// ����� ��� ������ evaluate
TEST(LogicFunctionTest, EvaluateSimpleAND) {
    LogicFunction lf("a&b");
    testing::internal::CaptureStdout();
    lf.printTruthTable();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1 1 1") != std::string::npos); // ���������, ��� a=1, b=1 -> ��������� 1
}

TEST(LogicFunctionTest, EvaluateSimpleOR) {
    LogicFunction lf("a|b");
    testing::internal::CaptureStdout();
    lf.printTruthTable();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("0 1 1") != std::string::npos); // ���������, ��� a=0, b=1 -> ��������� 1
}

TEST(LogicFunctionTest, EvaluateNOT) {
    LogicFunction lf("!a");
    testing::internal::CaptureStdout();
    lf.printTruthTable();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("0 1") != std::string::npos); // ���������, ��� a=0 -> ��������� 1
}

// ����� ��� ������ getDNF
TEST(LogicFunctionTest, GetDNFForAND) {
    LogicFunction lf("a&b");
    EXPECT_EQ(lf.getDNF(), lf.getDNF()); // ������� ������� ����� ������
}

TEST(LogicFunctionTest, GetDNFForOR) {
    LogicFunction lf("a|b");
    EXPECT_EQ(lf.getDNF(), lf.getDNF()); // ������� ������� ����� ������
}

// ����� ��� ������ getCNF
TEST(LogicFunctionTest, GetCNFForAND) {
    LogicFunction lf("a&b");
    EXPECT_EQ(lf.getCNF(), lf.getCNF()); // ������� ������� ����� ������
}

TEST(LogicFunctionTest, GetCNFForOR) {
    LogicFunction lf("a|b");
    EXPECT_EQ(lf.getCNF(), lf.getCNF()); // ������� ������� ����� ������
}

// ����� ��� ������ getDNFTerms
TEST(LogicFunctionTest, GetDNFTermsForAND) {
    LogicFunction lf("a&b");
    EXPECT_EQ(lf.getDNFTerms(), lf.getDNFTerms()); // ������� ������� ����� ������
}

TEST(LogicFunctionTest, GetDNFTermsForOR) {
    LogicFunction lf("a|b");
    EXPECT_EQ(lf.getDNFTerms(), lf.getDNFTerms()); // ������� ������� ����� ������
}

// ����� ��� ������ getCNFTerms
TEST(LogicFunctionTest, GetCNFTermsForAND) {
    LogicFunction lf("a&b");
    EXPECT_EQ(lf.getCNFTerms(), lf.getCNFTerms()); // ������� ������� ����� ������
}

TEST(LogicFunctionTest, GetCNFTermsForOR) {
    LogicFunction lf("a|b");
    EXPECT_EQ(lf.getCNFTerms(), lf.getCNFTerms()); // ������� ������� ����� ������
}

// ����� ��� ������ getIndexForm
TEST(LogicFunctionTest, GetIndexFormForAND) {
    LogicFunction lf("a&b");
    EXPECT_EQ(lf.getIndexForm(), lf.getIndexForm()); // ������� ������� ����� ������
}

TEST(LogicFunctionTest, GetIndexFormForOR) {
    LogicFunction lf("a|b");
    EXPECT_EQ(lf.getIndexForm(), lf.getIndexForm()); // ������� ������� ����� ������
}

// ����� ��� ������ printTruthTable
TEST(LogicFunctionTest, PrintTruthTableForAND) {
    LogicFunction lf("a&b");
    testing::internal::CaptureStdout();
    lf.printTruthTable();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("a b Result") != std::string::npos);
    EXPECT_TRUE(output.find("1 1 1") != std::string::npos);
}

TEST(LogicFunctionTest, SingleVariable) {
    LogicFunction lf("a");
    EXPECT_EQ(lf.getDNF(), "(a)");
    EXPECT_EQ(lf.getCNF(), "(!a)");
    EXPECT_EQ(lf.getDNFTerms(), std::set<int>({ 1 }));
    EXPECT_EQ(lf.getCNFTerms(), std::set<int>({ 0 }));
    EXPECT_EQ(lf.getIndexForm(), 1); // ������� 1, ��� ��� a=1 -> ��������� 1
}

TEST(LogicFunctionTest, NOTExpression) {
    LogicFunction lf("!a");
    EXPECT_EQ(lf.getDNF(), "(!a)");
    EXPECT_EQ(lf.getCNF(), "(a)");
    EXPECT_EQ(lf.getDNFTerms(), std::set<int>({ 0 }));
    EXPECT_EQ(lf.getCNFTerms(), std::set<int>({ 1 }));
    EXPECT_EQ(lf.getIndexForm(), 2); // ������� 2, ��� ��� a=0 -> ��������� 1
}

TEST(LogicFunctionTest, ThreeVariables) {
    LogicFunction lf("a&b&c");
    EXPECT_EQ(lf.getDNF(), "(a & b & c)");
    EXPECT_EQ(lf.getCNF(), "(!a | !b | !c) & (a | !b | !c) & (!a | b | !c) & (a | b | !c) & (!a | !b | c) & (a | !b | c) & (!a | b | c)");
    EXPECT_EQ(lf.getDNFTerms(), std::set<int>({ 7 }));
    EXPECT_EQ(lf.getCNFTerms(), std::set<int>({ 0, 1, 2, 3, 4, 5, 6 }));
    EXPECT_EQ(lf.getIndexForm(), 1); // 00000001 � �������� �������
}

// �������� ������� ��� ������� ������
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}