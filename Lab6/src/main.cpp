#include "hashTable.h"
#include <iostream>
#include <string>

class HashTableUI {
    HashTable hashTable;

    void showSearchResults(const std::string& key) const {
        auto results = hashTable.search(key);
        if (!results.empty()) {
            std::cout << " ������� " << results.size() << " ������� � �������� " << key << ":" << std::endl;
            for (const auto& result : results) {
                std::cout << "   - ������ " << result.first << ": " << result.second << std::endl;
            }
        }
        else {
            std::cout << " �� �������" << std::endl;
        }
    }

public:
    void run() {
        while (true) {
            std::cout << "\n����:" << std::endl;
            std::cout << "1. �������� ������" << std::endl;
            std::cout << "2. ����� ������" << std::endl;
            std::cout << "3. ������� ������" << std::endl;
            std::cout << "4. �������� �������" << std::endl;
            std::cout << "5. �����" << std::endl;

            std::cout << "�������� ��������: ";
            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "1") {
                std::cout << "������� �������: ";
                std::string key;
                std::getline(std::cin, key);
                std::cout << "������� ������ (��������, ���): ";
                std::string data;
                std::getline(std::cin, data);
                hashTable.insert(key, data);
            }
            else if (choice == "2") {
                std::cout << "������� ������� ��� ������: ";
                std::string key;
                std::getline(std::cin, key);
                showSearchResults(key);
            }
            else if (choice == "3") {
                std::cout << "������� ������� ��� ��������: ";
                std::string key;
                std::getline(std::cin, key);
                int deleted = hashTable.remove(key);
                if (deleted == 0) {
                    std::cout << " " << key << " �� ������" << std::endl;
                }
                else {
                    std::cout << " ������� " << deleted << " ������� � �������� " << key << std::endl;
                }
            }
            else if (choice == "4") {
                hashTable.display();
            }
            else if (choice == "5") {
                std::cout << "�����..." << std::endl;
                break;
            }
            else {
                std::cout << "�������� ����, ���������� �����." << std::endl;
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