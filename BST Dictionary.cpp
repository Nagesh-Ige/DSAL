#include <iostream>
using namespace std;
class Node {
public:
    string key, meaning;
    Node *left, *right;
    Node(string k, string m) : key(k), meaning(m), left(NULL), right(NULL) {}
};
class AVL {
    Node *root;
    int height(Node *t) { return t ? max(height(t->left), height(t->right)) + 1 : -1; }
    int balanceFactor(Node *t) { return height(t->left) - height(t->right); }
    Node* rotateLeft(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    Node* rotateRight(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    Node* balance(Node *t) {
        if (!t) return t;
        int bf = balanceFactor(t);
        if (bf > 1) return (balanceFactor(t->left) < 0) ? rotateLeft(t->left), rotateRight(t) : rotateRight(t);
        if (bf < -1) return (balanceFactor(t->right) > 0) ? rotateRight(t->right), rotateLeft(t) : rotateLeft(t);
        return t;
    }
    Node* insert(Node *t, string k, string m) {
        if (!t) return new Node(k, m);
        if (k < t->key) t->left = insert(t->left, k, m);
        else t->right = insert(t->right, k, m);
        return balance(t);
    }
    void inorder(Node *t) {
        if (t) {
            inorder(t->left);
            cout << t->key << " : " << t->meaning << endl;
            inorder(t->right);
        }
    }
    bool search(Node *t, string k) {
        if (!t) return false;
        if (t->key == k) return true;
        return search(k < t->key ? t->left : t->right, k);
    }
    Node* findMin(Node *t) {
        return t->left ? findMin(t->left) : t;
    }
    Node* remove(Node *t, string k) {
        if (!t) return t;
        if (k < t->key) t->left = remove(t->left, k);
        else if (k > t->key) t->right = remove(t->right, k);
        else {
            if (!t->left || !t->right) {
                Node *temp = t->left ? t->left : t->right;
                delete t;
                return temp;
            }
            Node *temp = findMin(t->right);
            t->key = temp->key;
            t->meaning = temp->meaning;
            t->right = remove(t->right, temp->key);
        }
        return balance(t);
    }
public:
    AVL() : root(NULL) {}

    void insert() {
        string k, m;
        cout << "Enter keyword: "; cin >> k;
        cout << "Enter meaning: "; cin >> m;
        root = insert(root, k, m);
    }
    void display() {
        cout << "AVL Tree (Inorder Traversal):\n";
        inorder(root);
    }
    void search() {
        string k;
        cout << "Enter keyword to search: "; cin >> k;
        cout << (search(root, k) ? "Keyword found!" : "Keyword not found!") << endl;
    }
    void remove() {
        string k;
        cout << "Enter keyword to delete: "; cin >> k;
        root = remove(root, k);
    }
};
int main() {
    AVL tree;
    int ch;
    cout << "\n1. Insert\n2. Display\n3. Search\n4. Delete\n5. Exit\n";  // Show menu only once
    do {
        cout << "Enter choice: ";
        cin >> ch;
        if (ch == 1) tree.insert();
        else if (ch == 2) tree.display();
        else if (ch == 3) tree.search();
        else if (ch == 4) tree.remove();
    } while (ch != 5);
    return 0;
}
