#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class SeparateChainingHashmap {
private:
    int size;
    vector<list<pair<string, string>>> table;

public:
    SeparateChainingHashmap(int size) : size(size), table(size) {}

    int _hash(const string& key) {
        return hash<string>{}(key) % size;
    }

    bool find(const string& key) {
        int index = _hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    void insert(const string& key, const string& value) {
        int index = _hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    void remove(const string& key) {
        int index = _hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return;
            }
        }
    }
};

int main() {
    SeparateChainingHashmap hashmap(10);
    hashmap.insert("key1", "value1");
    hashmap.insert("key2", "value2");
    cout << (hashmap.find("key1") ? "True" : "False") << endl;  // True
    cout << (hashmap.find("key3") ? "True" : "False") << endl;  // False
    hashmap.remove("key1");
    cout << (hashmap.find("key1") ? "True" : "False") << endl;  // False
    return 0;
}