#include <iostream>
#include <vector>
#include <string>

using namespace std;

class QuadraticProbingHashmap {
private:
    int size;
    vector<pair<string, string>> table;

public:
    QuadraticProbingHashmap(int size) : size(size), table(size) {}

    int _hash(const string& key) {
        return hash<string>{}(key) % size;
    }

    bool find(const string& key) {
        int index = _hash(key);
        int i = 1;
        while (table[index].first != "" && table[index].first != key) {
            index = (index + i * i) % size;
            i++;
        }
        return table[index].first == key;
    }

    void insert(const string& key, const string& value) {
        int index = _hash(key);
        int i = 1;
        while (table[index].first != "" && table[index].first != key) {
            index = (index + i * i) % size;
            i++;
        }
        table[index] = make_pair(key, value);
    }

    void remove(const string& key) {
        int index = _hash(key);
        int i = 1;
        while (table[index].first != key && table[index].first != "") {
            index = (index + i * i) % size;
            i++;
        }
        if (table[index].first == key) {
            table[index] = make_pair("", "");
        }
    }
};

int main() {
    QuadraticProbingHashmap hashmap(10);
    hashmap.insert("key1", "value1");
    hashmap.insert("key2", "value2");
    cout << (hashmap.find("key1") ? "True" : "False") << endl;  // True
    cout << (hashmap.find("key3") ? "True" : "False") << endl;  // False
    hashmap.remove("key1");
    cout << (hashmap.find("key1") ? "True" : "False") << endl;  // False
    return 0;
}