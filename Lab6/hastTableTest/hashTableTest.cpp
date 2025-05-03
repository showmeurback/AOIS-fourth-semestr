#include "pch.h"
#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 6\AOIS-LR-6\hashTable.h"
#include "D:\BSUIR\2 курс\4 семестр\АОИС\ЛР 6\AOIS-LR-6\hashTable.cpp"
#include <gtest/gtest.h>

class HashTableTest : public ::testing::Test {
protected:
    HashTable ht;

    void SetUp() override {
        ht = HashTable(5, 2); // Маленький размер для тестирования коллизий
    }
};

TEST_F(HashTableTest, Initialization) {
    EXPECT_EQ(ht.size, 5);
    EXPECT_EQ(ht.table.size(), 5);
    EXPECT_TRUE(ht.table[0].isEmpty());
}

TEST_F(HashTableTest, InsertAndSearch) {
    ht.insert("Ivanov", "Ivan");
    ht.insert("Petrov", "Petr");

    auto results = ht.search("Ivanov");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].second, "Ivan");

    results = ht.search("Petrov");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].second, "Petr");
}

TEST_F(HashTableTest, HandleCollisions) {
    // Эти имена специально подобраны для коллизии при размере таблицы 5
    ht.insert("abc", "Data1");
    ht.insert("fgh", "Data2"); // Должно вызвать коллизию

    auto results = ht.search("abc");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].second, "Data1");

    results = ht.search("fgh");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].second, "Data2");
}

TEST_F(HashTableTest, AutoExpand) {
    // Вставляем больше элементов, чем начальный размер
    ht.insert("1", "a");
    ht.insert("2", "b");
    ht.insert("3", "c");
    ht.insert("4", "d");
    ht.insert("5", "e");
    ht.insert("6", "f"); // Должно вызвать расширение

    EXPECT_GT(ht.size, 5); // Проверяем что таблица расширилась
    EXPECT_EQ(ht.search("6").size(), 1);
}

TEST_F(HashTableTest, DeleteEntries) {
    ht.insert("Ivanov", "Ivan");
    ht.insert("Petrov", "Petr");

    int deleted = ht.remove("Ivanov");
    EXPECT_EQ(deleted, 1);
    EXPECT_EQ(ht.search("Ivanov").size(), 0);
    EXPECT_EQ(ht.search("Petrov").size(), 1);
}

TEST_F(HashTableTest, DeleteNonExistent) {
    int deleted = ht.remove("NonExistent");
    EXPECT_EQ(deleted, 0);
}

TEST_F(HashTableTest, MultipleEntriesSameKey) {
    ht.insert("Ivanov", "Ivan1");
    ht.insert("Ivanov", "Ivan2");

    auto results = ht.search("Ivanov");
    ASSERT_EQ(results.size(), 2);
}

TEST_F(HashTableTest, DisplayEmptyTable) {
    testing::internal::CaptureStdout();
    ht.display();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("ID"), std::string::npos);
    EXPECT_NE(output.find("-"), std::string::npos);
}