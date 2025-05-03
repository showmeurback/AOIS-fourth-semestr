#include "hashTable.h"
#include <iostream>
#include <string>

class HashTableUI {
    HashTable hashTable;

    void showSearchResults(const std::string& key) const {
        auto results = hashTable.search(key);
        if (!results.empty()) {
            std::cout << " Найдено " << results.size() << " записей с фамилией " << key << ":" << std::endl;
            for (const auto& result : results) {
                std::cout << "   - Ячейка " << result.first << ": " << result.second << std::endl;
            }
        }
        else {
            std::cout << " Не найдено" << std::endl;
        }
    }

public:
    void run() {
        while (true) {
            std::cout << "\nМеню:" << std::endl;
            std::cout << "1. Добавить запись" << std::endl;
            std::cout << "2. Найти запись" << std::endl;
            std::cout << "3. Удалить запись" << std::endl;
            std::cout << "4. Показать таблицу" << std::endl;
            std::cout << "5. Выйти" << std::endl;

            std::cout << "Выберите действие: ";
            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "1") {
                std::cout << "Введите фамилию: ";
                std::string key;
                std::getline(std::cin, key);
                std::cout << "Введите данные (например, имя): ";
                std::string data;
                std::getline(std::cin, data);
                hashTable.insert(key, data);
            }
            else if (choice == "2") {
                std::cout << "Введите фамилию для поиска: ";
                std::string key;
                std::getline(std::cin, key);
                showSearchResults(key);
            }
            else if (choice == "3") {
                std::cout << "Введите фамилию для удаления: ";
                std::string key;
                std::getline(std::cin, key);
                int deleted = hashTable.remove(key);
                if (deleted == 0) {
                    std::cout << " " << key << " не найден" << std::endl;
                }
                else {
                    std::cout << " Удалено " << deleted << " записей с фамилией " << key << std::endl;
                }
            }
            else if (choice == "4") {
                hashTable.display();
            }
            else if (choice == "5") {
                std::cout << "Выход..." << std::endl;
                break;
            }
            else {
                std::cout << "Неверный ввод, попробуйте снова." << std::endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    HashTableUI ui;
    ui.run();
    return 0;
}