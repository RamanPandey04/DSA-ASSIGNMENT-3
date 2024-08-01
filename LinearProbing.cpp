#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LinearProbingHashmap {
private:
    int size;
    vector<pair<string, string>> table;

public:
    LinearProbingHashmap(int size) : size(size), table(size) {}

    int _hash(const string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % size;
    }

    bool find(const string& key) {
        int index = _hash(key);
        while (table[index].first != "") {
            if (table[index].first == key) {
                return true;
            }
            index = (index + 1) % size;
        }
        return false;
    }

    void insert(const string& key, const string& value) {
        int index = _hash(key);
        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
        }
        table[index] = make_pair(key, value);
    }

    void remove(const string& key) {
        int index = _hash(key);
        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
        }
        if (table[index].first == key) {
            table[index] = make_pair("", "");
        }
    }
};

int main() {
    LinearProbingHashmap hashmap(10);
    hashmap.insert("key1", "value1");
    hashmap.insert("key2", "value2");
    cout << (hashmap.find("key1") ? "True" : "False") << endl;  // True
    cout << (hashmap.find("key3") ? "True" : "False") << endl;  // False
    hashmap.remove("key1");
    cout << (hashmap.find("key1") ? "True" : "False") << endl;  // False
    return 0;
}