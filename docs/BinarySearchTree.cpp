#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;

    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        insert(root, value);
    }

    bool search(int value) {
        return search(root, value);
    }

    void traverse() {
        traverse(root);
    }

    bool del(int value) {
        return del(root, value);
    }
private:
    void insert(Node*& rt, int value) {
        if (rt == nullptr) {
            rt = new Node(value);
            return;
        }

        // ignore the equal value
        if (value < rt->data) insert(rt->left, value);
        else if (value > rt->data) insert(rt->right, value);
    }

    bool search(Node* rt, int value) {
        if (rt == nullptr) return false;
        if (rt->data == value) return true;

        if (value < rt->data) return search(rt->left, value);
        else return search(rt->right, value);
    }

    void traverse(Node*& rt) {
        if (rt == nullptr) return;
        traverse(rt->left);
        cout << rt->data << " ";
        traverse(rt->right);
    }

    bool del(Node*& rt, int value) {
        
    }

    Node* root;
};

int main() {
    BinarySearchTree bst;

    bst.insert(8);
    bst.insert(3);
    bst.insert(1);
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(10);
    bst.insert(14);
    bst.insert(13);

    for (int i=1; i<=10; i++) {
        cout << i << ": " << bst.search(i) << "\n";
    }

    bst.traverse();

    return 0;
}