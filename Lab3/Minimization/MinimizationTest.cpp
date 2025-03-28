#include "pch.h"
#include <gtest/gtest.h>
#include <sstream>
#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 3\AOIS-LR-3\Minimization.h"
#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 3\AOIS-LR-3\Minimization.cpp"

// Тестовый класс
class MinimizerTest : public ::testing::Test {
protected:
    Minimizer minimizer;

    void SetUp() override {
        // Инициализация с 3 переменными по умолчанию
        minimizer = Minimizer(3);
    }
};

TEST_F(MinimizerTest, AddMinterm_ValidInput) {
    std::vector<bool> term = { true, false, true };
    minimizer.addMinterm(term);
    EXPECT_EQ(1, minimizer.minimizeDNFCalculation().find("a&!b&c") != std::string::npos ? 1 : 0);
}

TEST_F(MinimizerTest, AddMaxterm_ValidInput) {
    std::vector<bool> term = { false, true, false };
    minimizer.addMaxterm(term);
    EXPECT_EQ(1, minimizer.minimizeCNFCalculation().find("!a|b|!c") != std::string::npos ? 1 : 0);
}

TEST_F(MinimizerTest, TermToString_DNF) {
    std::vector<bool> term = { true, false, true };
    minimizer.addMinterm(term);
    EXPECT_NE(std::string::npos, minimizer.minimizeDNFCalculation().find("a&!b&c"));
}

TEST_F(MinimizerTest, TermToString_CNF) {
    std::vector<bool> term = { false, true, false };
    minimizer.addMaxterm(term);
    EXPECT_NE(std::string::npos, minimizer.minimizeCNFCalculation().find("(!a|b|!c)"));
}

TEST_F(MinimizerTest, MinimizeDNFCalculation_ThreeTerms) {
    minimizer.addMinterm({ true, false, false });
    minimizer.addMinterm({ true, true, false });
    minimizer.addMinterm({ false, true, false });
    std::string result = minimizer.minimizeDNFCalculation();
    EXPECT_NE(std::string::npos, result.find("b&!c"));
}

TEST_F(MinimizerTest, MinimizeDNFKarnaugh_Simple) {
    minimizer.addMinterm({ true, false, false });
    minimizer.addMinterm({ true, true, false });
    std::string result = minimizer.minimizeDNFKarnaugh();
    EXPECT_NE(std::string::npos, result.find("a"));
}

TEST_F(MinimizerTest, MinimizeCNFCalculation_Simple) {
    minimizer.addMaxterm({ false, true, true });
    minimizer.addMaxterm({ true, true, true });
    std::string result = minimizer.minimizeCNFCalculation();
    EXPECT_NE(std::string::npos, result.find("!a"));
}

TEST_F(MinimizerTest, MinimizeCNFCalculation_ThreeTerms) {
    minimizer.addMaxterm({ false, true, true });
    minimizer.addMaxterm({ true, true, true });
    minimizer.addMaxterm({ true, false, true });
    std::string result = minimizer.minimizeCNFCalculation();
    EXPECT_NE(std::string::npos, result.find("c"));
}

TEST_F(MinimizerTest, MinimizeCNFCalcTable_Simple) {
    minimizer.addMaxterm({ false, false, true });
    minimizer.addMaxterm({ true, false, true });
    std::string result = minimizer.minimizeCNFCalcTable();
    EXPECT_NE(std::string::npos, result.find("!b"));
}

TEST_F(MinimizerTest, MinimizeCNFKarnaugh_Simple) {
    minimizer.addMaxterm({ false, false, true });
    minimizer.addMaxterm({ true, false, true });
    std::string result = minimizer.minimizeCNFKarnaugh();
    EXPECT_NE(std::string::npos, result.find("!b"));
}

// Дополнительные тесты для различных случаев
TEST_F(MinimizerTest, MinimizeDNFCalculation_FullCoverage) {
    minimizer.addMinterm({ true, true, true });
    minimizer.addMinterm({ true, true, false });
    minimizer.addMinterm({ true, false, true });
    minimizer.addMinterm({ true, false, false });
    std::string result = minimizer.minimizeDNFCalculation();
    EXPECT_NE(std::string::npos, result.find("a"));
}

TEST_F(MinimizerTest, MinimizeCNFCalculation_FullCoverage) {
    minimizer.addMaxterm({ false, false, false });
    minimizer.addMaxterm({ false, false, true });
    minimizer.addMaxterm({ false, true, false });
    minimizer.addMaxterm({ false, true, true });
    std::string result = minimizer.minimizeCNFCalculation();
    EXPECT_NE(std::string::npos, result.find("!a"));
}

// Тест на склеивание 4 минтермов в один импликант
TEST_F(MinimizerTest, GlueFourMinterms_DNF) {
    minimizer.addMinterm({ false, false, false });
    minimizer.addMinterm({ false, false, true });
    minimizer.addMinterm({ false, true, false });
    minimizer.addMinterm({ false, true, true });
    std::string result = minimizer.minimizeDNFCalculation();
    EXPECT_NE(std::string::npos, result.find("!a"));
}

// Тест на склеивание 4 макстермов в один импликант
TEST_F(MinimizerTest, GlueFourMaxterms_CNF) {
    minimizer.addMaxterm({ true, false, false });
    minimizer.addMaxterm({ true, false, true });
    minimizer.addMaxterm({ true, true, false });
    minimizer.addMaxterm({ true, true, true });
    std::string result = minimizer.minimizeCNFCalculation();
    EXPECT_NE(std::string::npos, result.find("a"));
}

// Тест на проверку таблицы покрытия для СДНФ
TEST_F(MinimizerTest, CoverageTable_DNF) {
    minimizer.addMinterm({ true, false, false });
    minimizer.addMinterm({ true, true, false });
    std::string result = minimizer.minimizeDNFCalcTable();
    EXPECT_NE(std::string::npos, result.find("Таблица покрытия"));
    EXPECT_NE(std::string::npos, result.find("X")); // Проверяем наличие отметок покрытия
}

// Тест на проверку таблицы покрытия для СКНФ
TEST_F(MinimizerTest, CoverageTable_CNF) {
    minimizer.addMaxterm({ false, true, true });
    minimizer.addMaxterm({ true, true, true });
    std::string result = minimizer.minimizeCNFCalcTable();
    EXPECT_NE(std::string::npos, result.find("Таблица покрытия"));
    EXPECT_NE(std::string::npos, result.find("X")); // Проверяем наличие отметок покрытия
}

// Тест на карту Карно для СКНФ с двумя соседними нулями
TEST_F(MinimizerTest, KarnaughMapTwoAdjacent_CNF) {
    minimizer.addMaxterm({ false, false, false });
    minimizer.addMaxterm({ false, false, true });
    std::string result = minimizer.minimizeCNFKarnaugh();
    EXPECT_NE(std::string::npos, result.find("Карта Карно"));
    EXPECT_NE(std::string::npos, result.find("!a|!b")); // Ожидаемый результат
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
