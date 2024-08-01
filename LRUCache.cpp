#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            _remove(node);
            _add(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            _remove(cache[key]);
        }
        Node* node = new Node(key, value);
        _add(node);
        cache[key] = node;
        if (cache.size() > capacity) {
            Node* lru_node = head->next;
            _remove(lru_node);
            cache.erase(lru_node->key);
            delete lru_node;
        }
    }

private:
    void _remove(Node* node) {
        Node* prev_node = node->prev;
        Node* next_node = node->next;
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }

    void _add(Node* node) {
        Node* prev_node = tail->prev;
        prev_node->next = node;
        tail->prev = node;
        node->prev = prev_node;
        node->next = tail;
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;  // 1
    cache.put(3, 3);  // evicts key 2
    cout << cache.get(2) << endl;  // -1
    cache.put(4, 4);  // evicts key 1
    cout << cache.get(1) << endl;  // -1
    cout << cache.get(3) << endl;  // 3
    cout << cache.get(4) << endl;  // 4
    return 0;
}