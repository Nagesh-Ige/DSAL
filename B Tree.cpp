#include <iostream>
using namespace std;

class BTreeNode {
public:
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;

    BTreeNode(int _t, bool _leaf);

    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    BTreeNode* search(int k);

    friend class BTree;
};

class BTree {
    BTreeNode *root;
    int t;

public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
        cout << endl;
    }

    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2*t - 1];
    C = new BTreeNode *[2*t];
    n = 0;
}

void BTreeNode::traverse() {
    for (int i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf)
        C[n]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (i < n && keys[i] == k)
        return this;

    if (leaf)
        return nullptr;

    return C[i]->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2*t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i+1]->n == 2*t - 1) {
            splitChild(i+1, C[i+1]);

            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

int main() {
    int t;
    cout << "Enter minimum degree (t) of B-Tree: ";
    cin >> t;

    BTree tree(t);

    int n;
    cout << "Enter number of elements to insert: ";
    cin >> n;

    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        tree.insert(k);
    }

    int choice;
    do {
        cout << "\n--- B-Tree Menu ---\n";
        cout << "1. Insert element\n";
        cout << "2. Search element\n";
        cout << "3. Display tree\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int val;
            cout << "Enter element to insert: ";
            cin >> val;
            tree.insert(val);
        } else if (choice == 2) {
            int val;
            cout << "Enter element to search: ";
            cin >> val;
            BTreeNode* found = tree.search(val);
            if (found)
                cout << "Element " << val << " found in B-Tree.\n";
            else
                cout << "Element not found.\n";
        } else if (choice == 3) {
            cout << "B-Tree in-order traversal: ";
            tree.traverse();
        } else if (choice == 4) {
            cout << "Exiting program.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
