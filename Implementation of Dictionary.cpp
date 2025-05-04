#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    char keyword[20];
    char meaning[50];
    Node* left;
    Node* right;

    Node(const char* k, const char* m) {
        strcpy(keyword, k);
        strcpy(meaning, m);
        left = right = NULL;
    }
};

class Dictionary {
private:
    Node* root;

    Node* insert(Node* root, const char* k, const char* m) {
        if (root == NULL)
            return new Node(k, m);

        if (strcmp(k, root->keyword) < 0)
            root->left = insert(root->left, k, m);
        else if (strcmp(k, root->keyword) > 0)
            root->right = insert(root->right, k, m);
        else
            cout << "\nKeyword already exists. Skipping insert.";

        return root;
    }

    void displayAsc(Node* root) {
        if (root != NULL) {
            displayAsc(root->left);
            cout << "Keyword: " << root->keyword << " | Meaning: " << root->meaning << endl;
            displayAsc(root->right);
        }
    }

    void displayDesc(Node* root) {
        if (root != NULL) {
            displayDesc(root->right);
            cout << "Keyword: " << root->keyword << " | Meaning: " << root->meaning << endl;
            displayDesc(root->left);
        }
    }

    int search(Node* root, const char* k, int& comparisons) {
        while (root != NULL) {
            comparisons++;
            if (strcmp(k, root->keyword) == 0)
                return 1;
            else if (strcmp(k, root->keyword) < 0)
                root = root->left;
            else
                root = root->right;
        }
        return 0;
    }

    int update(Node* root, const char* k, const char* newMeaning) {
        while (root != NULL) {
            if (strcmp(k, root->keyword) == 0) {
                strcpy(root->meaning, newMeaning);
                return 1;
            } else if (strcmp(k, root->keyword) < 0)
                root = root->left;
            else
                root = root->right;
        }
        return 0;
    }

    Node* findMin(Node* root) {
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    Node* deleteNode(Node* root, const char* k) {
        if (root == NULL)
            return NULL;

        if (strcmp(k, root->keyword) < 0)
            root->left = deleteNode(root->left, k);
        else if (strcmp(k, root->keyword) > 0)
            root->right = deleteNode(root->right, k);
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
                Node* temp = findMin(root->right);
                strcpy(root->keyword, temp->keyword);
                strcpy(root->meaning, temp->meaning);
                root->right = deleteNode(root->right, temp->keyword);
            }
        }
        return root;
    }

    int height(Node* root) {
        if (root == NULL)
            return -1;
        int left = height(root->left);
        int right = height(root->right);
        return 1 + max(left, right);
    }

public:
    Dictionary() {
        root = NULL;
    }

    void addEntry() {
        char k[20], m[50];
        cout << "Enter keyword: ";
        cin >> k;
        cout << "Enter meaning: ";
        cin.ignore();
        cin.getline(m, 50);
        root = insert(root, k, m);
    }

    void displayAscending() {
        if (root == NULL)
            cout << "Dictionary is empty.\n";
        else
            displayAsc(root);
    }

    void displayDescending() {
        if (root == NULL)
            cout << "Dictionary is empty.\n";
        else
            displayDesc(root);
    }

    void searchKeyword() {
        char k[20];
        int comparisons = 0;
        cout << "Enter keyword to search: ";
        cin >> k;

        if (search(root, k, comparisons))
            cout << "Keyword found in " << comparisons << " comparisons.\n";
        else
            cout << "Keyword not found.\n";
    }

    void updateMeaning() {
        char k[20], newMeaning[50];
        cout << "Enter keyword to update: ";
        cin >> k;
        cout << "Enter new meaning: ";
        cin.ignore();
        cin.getline(newMeaning, 50);

        if (update(root, k, newMeaning))
            cout << "Meaning updated successfully.\n";
        else
            cout << "Keyword not found.\n";
    }

    void deleteKeyword() {
        char k[20];
        cout << "Enter keyword to delete: ";
        cin >> k;
        root = deleteNode(root, k);
        cout << "If keyword existed, it has been deleted.\n";
    }

    void maxComparisons() {
        int h = height(root);
        cout << "Maximum comparisons required (worst-case): " << h + 1 << endl;
    }
};

int main() {
    Dictionary dict;
    int choice;

    do {
        cout << "\n=== DICTIONARY MENU ===\n";
        cout << "1. Add Keyword\n2. Display Ascending\n3. Display Descending\n";
        cout << "4. Search\n5. Update\n6. Delete\n7. Max Comparisons\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: dict.addEntry(); break;
            case 2: dict.displayAscending(); break;
            case 3: dict.displayDescending(); break;
            case 4: dict.searchKeyword(); break;
            case 5: dict.updateMeaning(); break;
            case 6: dict.deleteKeyword(); break;
            case 7: dict.maxComparisons(); break;
            case 8: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
