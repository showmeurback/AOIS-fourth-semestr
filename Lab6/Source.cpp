#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct HashEntry {
    string ID;
    int C;
    int U;
    int T;
    int L;
    int D;
    string P0;
    string Pi;
};

class HashTable {
public:
    int size;
    int expand_step;
    vector<HashEntry> table;

    HashTable(int initial_size = 20, int step = 3) : size(initial_size), expand_step(step) {
        HashEntry emptyEntry = { "", 0, 0, 0, 0, 0, "", "" };
        table = vector<HashEntry>(size, emptyEntry);
    }

    int hash(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash += static_cast<int>(c);
        }
        return hash % size;
    }

    void expand_table() {
        HashEntry emptyEntry = { "", 0, 0, 0, 0, 0, "", "" };
        table.resize(size + expand_step, emptyEntry);
        size += expand_step;
        cout << " Таблица расширена на " << expand_step << " ячеек. Новый размер: " << size << endl;
    }

    void insert(const string& key, const string& data) {
        int h = hash(key);
        for (int i = 0; i < size; ++i) {
            int index = (h + i) % size;
            if (table[index].U == 0 || table[index].D == 1) {
                table[index] = { key, (i > 0) ? 1 : 0, 1, 0, 0, 0, "", data };
                cout << " " << key << " добавлен в ячейку " << index << endl;
                return;
            }
        }
        expand_table();
        insert(key, data);
    }

    void search(const string& key) {
        vector<pair<int, string>> results;
        for (int i = 0; i < size; ++i) {
            if (table[i].U == 1 && table[i].ID == key && table[i].D == 0) {
                results.push_back(make_pair(i, table[i].Pi));
            }
        }
        if (!results.empty()) {
            cout << " Найдено " << results.size() << " записей с фамилией " << key << ":" << endl;
            for (size_t j = 0; j < results.size(); ++j) {
                cout << "   - Ячейка " << results[j].first << ": " << results[j].second << endl;
            }
        }
        else {
            cout << " Не найдено" << endl;
        }
    }

    void deleteEntry(const string& key) {
        int deleted_count = 0;
        for (int i = 0; i < size; ++i) {
            if (table[i].U == 1 && table[i].ID == key) {
                table[i] = { "", 0, 0, 0, 0, 0, "", "" };
                deleted_count++;
                cout << " " << key << " удалён из ячейки " << i << endl;
            }
        }
        if (deleted_count == 0) {
            cout << " " << key << " не найден" << endl;
        }
        else {
            cout << " Удалено " << deleted_count << " записей с фамилией " << key << endl;
        }
    }

    void display() const {
        cout << "\n№   ID        C  U  T  L  D  P0  Pi" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < size; ++i) {
            cout << i << "   ";
            cout << (table[i].ID.empty() ? "-" : table[i].ID) << "   ";
            cout << table[i].C << "  ";
            cout << table[i].U << "  ";
            cout << table[i].T << "  ";
            cout << table[i].L << "  ";
            cout << table[i].D << "  ";
            cout << (table[i].P0.empty() ? "-" : table[i].P0) << "  ";
            cout << (table[i].Pi.empty() ? "-" : table[i].Pi) << endl;
        }
        cout << "----------------------------------------" << endl;
    }
};

void showMenu() {
    HashTable ht;

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Найти запись" << endl;
        cout << "3. Удалить запись" << endl;
        cout << "4. Показать таблицу" << endl;
        cout << "5. Выйти" << endl;

        cout << "Выберите действие: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            cout << "Введите фамилию: ";
            string key;
            getline(cin, key);
            cout << "Введите данные (например, имя): ";
            string data;
            getline(cin, data);
            ht.insert(key, data);
        }
        else if (choice == "2") {
            cout << "Введите фамилию для поиска: ";
            string key;
            getline(cin, key);
            ht.search(key);
        }
        else if (choice == "3") {
            cout << "Введите фамилию для удаления: ";
            string key;
            getline(cin, key);
            ht.deleteEntry(key);
        }
        else if (choice == "4") {
            ht.display();
        }
        else if (choice == "5") {
            cout << "Выход..." << endl;
            break;
        }
        else {
            cout << "Неверный ввод, попробуйте снова." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    showMenu();
    return 0;
}