#include <iostream>
using namespace std;

struct node {
    int value;
    node* next;
} *Hashtable[10];

class hashing {
public:
    hashing() {
        for (int i = 0; i < 10; i++) {
            Hashtable[i] = NULL;
        }
    }

    int Hashfunction(int value) {
        return value % 10;
    }

    node* create_node(int x) {
        node* temp = new node;
        temp->value = x;
        temp->next = NULL;
        return temp;
    }

    void display() {
        for (int i = 0; i < 10; i++) {
            cout << "Bucket [" << i << "]: ";
            node* temp = Hashtable[i];
            while (temp != NULL) {
                cout << temp->value;
                if (temp->next != NULL) cout << " -> ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    int search(int value) {
        bool flag = false;
        int hash_val = Hashfunction(value);
        node* entry = Hashtable[hash_val];
        while (entry != NULL) {
            if (entry->value == value) {
                cout << "\nElement found at Bucket " << hash_val << ": " << entry->value << endl;
                flag = true;
                break;
            }
            entry = entry->next;
        }
        if (!flag) {
            return -1;
        }
        return hash_val;
    }

    void delete_element(int value) {
        int hash_val = Hashfunction(value);
        node* entry = Hashtable[hash_val];
        node* prev = NULL;

        if (entry == NULL) {
            cout << "Element is not present!" << endl;
            return;
        }

        while (entry != NULL && entry->value != value) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == NULL) {
            cout << "Element not found." << endl;
            return;
        }

        if (prev == NULL) {
            Hashtable[hash_val] = entry->next;
        } else {
            prev->next = entry->next;
        }

        delete entry;
        cout << "Element " << value << " deleted successfully." << endl;
    }

    void insertelement(int value) {
        int hash_val = Hashfunction(value);
        node* head = create_node(value);
        node* temp = Hashtable[hash_val];

        if (temp == NULL) {
            Hashtable[hash_val] = head;
        } else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = head;
        }
    }
};

int main() {
    int ch, data, search_val, del, flag = 0, n;
    char a;
    hashing h;

    do {
        cout << "\n------TELEPHONE DIRECTORY--------" << endl;
        cout << "1. INSERT" << endl;
        cout << "2. DISPLAY" << endl;
        cout << "3. SEARCH" << endl;
        cout << "4. DELETE" << endl;
        cout << "5. EXIT" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "How many phone numbers do you want to insert? ";
                cin >> n;
                cout << "Enter " << n << " phone numbers:" << endl;
                for (int i = 0; i < n; i++) {
                    cin >> data;
                    h.insertelement(data);
                }
                break;

            case 2:
                h.display();
                break;

            case 3:
                cout << "Enter the number to search: ";
                cin >> search_val;
                if (h.search(search_val) == -1) {
                    cout << "Element is not present!" << endl;
                }
                break;

            case 4:
                cout << "Enter the phone number to delete: ";
                cin >> del;
                h.delete_element(del);
                break;

            case 5:
                cout << "Do you want to exit (y/n)? ";
                cin >> a;
                if (a == 'y' || a == 'Y') {
                    flag = 1;
                }
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (!flag);

    return 0;
}
