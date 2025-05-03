#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <utility>

class HashEntry {
    std::string id;
    int c;
    int u;
    int t;
    int l;
    int d;
    std::string p0;
    std::string pi;

public:
    HashEntry();
    std::string getID() const;
    int getC() const;
    int getU() const;
    int getT() const;
    int getL() const;
    int getD() const;
    std::string getP0() const;
    std::string getPi() const;
    void setData(const std::string& newId, const std::string& newPi);
    void markDeleted();
    bool isOccupied() const;
    bool isDeleted() const;
    bool isEmpty() const;
};

class HashTable {
public:
    int size;
    int expand_step;
    std::vector<HashEntry> table;

    HashTable(int initial_size = 20, int step = 3);
    void insert(const std::string& key, const std::string& data);
    std::vector<std::pair<int, std::string>> search(const std::string& key) const;
    int remove(const std::string& key);
    void display() const;
};

#endif // HASH_TABLE_H