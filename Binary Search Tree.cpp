#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = NULL;
    }
};

Node* insert(Node* root, int key) {
    if (root == NULL)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int height(Node* root) {
    if (root == NULL)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + max(leftHeight, rightHeight);
}

int findMin(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return -1;
    }
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findMax(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return -1;
    }
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

bool search(Node* root, int key) {
    if (root == NULL)
        return false;

    if (root->data == key)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void mirror(Node* root) {
    if (root == NULL)
        return;

    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

int main() {
    Node* root = NULL;
    int choice, value, nodes;

    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Insert Nodes\n";
        cout << "2. Display Traversals\n";
        cout << "3. Find Largest Element\n";
        cout << "4. Find Smallest Element\n";
        cout << "5. Find Height of Tree\n";
        cout << "6. Search Element\n";
        cout << "7. Mirror the Tree\n";
        cout << "8. Delete Node\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "How many nodes do you want to insert? ";
                cin >> nodes;
                for (int i = 0; i < nodes; i++) {
                    cout << "Enter value: ";
                    cin >> value;
                    root = insert(root, value);
                }
                break;

            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << "\nPreorder Traversal: ";
                preorder(root);
                cout << "\nPostorder Traversal: ";
                postorder(root);
                cout << endl;
                break;

            case 3:
                cout << "Largest element: " << findMax(root) << endl;
                break;

            case 4:
                cout << "Smallest element: " << findMin(root) << endl;
                break;

            case 5:
                cout << "Height of tree: " << height(root) << endl;
                break;

            case 6:
                cout << "Enter element to search: ";
                cin >> value;
                if (search(root, value))
                    cout << value << " is found in the tree.\n";
                else
                    cout << value << " is not found in the tree.\n";
                break;

            case 7:
                cout << "Before Mirroring (Inorder): ";
                inorder(root);
                mirror(root);
                cout << "\nAfter Mirroring (Inorder): ";
                inorder(root);
                cout << endl;
                break;

            case 8:
                cout << "Enter node value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Inorder traversal after deletion: ";
                inorder(root);
                cout << endl;
                break;

            case 9:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
