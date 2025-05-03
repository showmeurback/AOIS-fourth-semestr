#include "hashTable.h"
#include <iostream>

HashEntry::HashEntry() : id(""), c(0), u(0), t(0), l(0), d(0), p0(""), pi("") {}

std::string HashEntry::getID() const { return id; }
int HashEntry::getC() const { return c; }
int HashEntry::getU() const { return u; }
int HashEntry::getT() const { return t; }
int HashEntry::getL() const { return l; }
int HashEntry::getD() const { return d; }
std::string HashEntry::getP0() const { return p0; }
std::string HashEntry::getPi() const { return pi; }

void HashEntry::setData(const std::string& newId, const std::string& newPi) {
    id = newId;
    pi = newPi;
    u = 1;
    d = 0;
}

void HashEntry::markDeleted() {
    id = "";
    c = u = t = l = d = 0;
    p0 = pi = "";
}

bool HashEntry::isOccupied() const { return u == 1 && d == 0; }
bool HashEntry::isDeleted() const { return d == 1; }
bool HashEntry::isEmpty() const { return u == 0; }

HashTable::HashTable(int initial_size, int step) : size(initial_size), expand_step(step) {
    table.resize(size);
}

void HashTable::insert(const std::string& key, const std::string& data) {
    int h = 0;
    for (char c : key) {
        h += static_cast<int>(c);
    }
    h %= size;

    for (int i = 0; i < size; ++i) {
        int index = (h + i) % size;
        if (table[index].isEmpty() || table[index].isDeleted()) {
            table[index].setData(key, data);
            std::cout << " " << key << " добавлен в €чейку " << index << std::endl;
            return;
        }
    }
    table.resize(size + expand_step);
    size += expand_step;
    std::cout << " “аблица расширена на " << expand_step << " €чеек. Ќовый размер: " << size << std::endl;
    insert(key, data);
}

std::vector<std::pair<int, std::string>> HashTable::search(const std::string& key) const {
    std::vector<std::pair<int, std::string>> results;
    for (int i = 0; i < size; ++i) {
        if (table[i].isOccupied() && table[i].getID() == key) {
            results.emplace_back(i, table[i].getPi());
        }
    }
    return results;
}

int HashTable::remove(const std::string& key) {
    int deleted_count = 0;
    for (int i = 0; i < size; ++i) {
        if (table[i].isOccupied() && table[i].getID() == key) {
            table[i].markDeleted();
            deleted_count++;
            std::cout << " " << key << " удалЄн из €чейки " << i << std::endl;
        }
    }
    return deleted_count;
}

void HashTable::display() const {
    std::cout << "\nє   ID        C  U  T  L  D  P0  Pi" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << i << "   ";
        std::cout << (table[i].getID().empty() ? "-" : table[i].getID()) << "   ";
        std::cout << table[i].getC() << "  ";
        std::cout << table[i].getU() << "  ";
        std::cout << table[i].getT() << "  ";
        std::cout << table[i].getL() << "  ";
        std::cout << table[i].getD() << "  ";
        std::cout << (table[i].getP0().empty() ? "-" : table[i].getP0()) << "  ";
        std::cout << (table[i].getPi().empty() ? "-" : table[i].getPi()) << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}