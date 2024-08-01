#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = nullptr;
    }

    int getHeight(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* node) {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    Node* leftRotate(Node* node) {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    Node* insertNode(Node* node, int key) {
        if (node == nullptr) {
            node = new Node();
            node->key = key;
            node->left = nullptr;
            node->right = nullptr;
            node->height = 1;
            return node;
        }

        if (key < node->key) node->left = insertNode(node->left, key);
        else if (key > node->key) node->right = insertNode(node->right, key);
        else return node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) return rightRotate(node);
        if (balance < -1 && key > node->right->key) return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(int key) {
        root = insertNode(root, key);
    }

    void inorder() {
        inorder(root);
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }
};

int main() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Inorder traversal of the AVL tree is: ";
    tree.inorder();

    return 0;
}