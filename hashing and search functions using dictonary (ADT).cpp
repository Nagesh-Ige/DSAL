#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct Node {
    string fruit;
    float rate;
    Node* next;
};

class Dictionary {
    Node* table[TABLE_SIZE];

    int hashFunction(string key) {
        int sum = 0;
        for (char ch : key) {
            sum += int(ch);
        }
        return sum % TABLE_SIZE;
    }

public:
    Dictionary() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insert(string fruit, float rate) {
        int index = hashFunction(fruit);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->fruit == fruit) {
                cout << "Fruit already exists. Updating rate.\n";
                current->rate = rate;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node{fruit, rate, table[index]};
        table[index] = newNode;
        cout << "Inserted at hash index " << index << ": (" << fruit << ", ₹" << rate << ")\n";
    }

    void find(string fruit) {
        int index = hashFunction(fruit);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->fruit == fruit) {
                cout << "Found at index " << index << ": (" << fruit << ", ₹" << current->rate << ")\n";
                return;
            }
            current = current->next;
        }

        cout << "Fruit \"" << fruit << "\" not found.\n";
    }

    void remove(string fruit) {
        int index = hashFunction(fruit);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->fruit == fruit) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Deleted fruit \"" << fruit << "\" from index " << index << "\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Fruit not found.\n";
    }

    void display() {
        cout << "\nHash Table (Index → Fruit → Rate):\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            Node* current = table[i];
            if (!current) {
                cout << "Empty";
            }
            while (current != nullptr) {
                cout << "(" << current->fruit << ", ₹" << current->rate << ")";
                if (current->next != nullptr)
                    cout << " → ";
                current = current->next;
            }
            cout << "\n";
        }
    }
};

int main() {
    Dictionary dict;
    int choice;
    string fruit;
    float rate;
    char more;

    do {
        cout << "\n--- Fruit Rate Dictionary Menu ---\n";
        cout << "1. Insert Fruit and Rate\n";
        cout << "2. Find Fruit Rate\n";
        cout << "3. Delete Fruit\n";
        cout << "4. Display All\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                do {
                    cout << "\nEnter fruit name: ";
                    cin >> fruit;
                    cout << "Enter rate: ₹";
                    cin >> rate;
                    dict.insert(fruit, rate);
                    cout << "Do you want to add more fruits (y/n)? ";
                    cin >> more;
                } while (more == 'y' || more == 'Y');
                break;

            case 2:
                cout << "Enter fruit name to find: ";
                cin >> fruit;
                dict.find(fruit);
                break;

            case 3:
                cout << "Enter fruit name to delete: ";
                cin >> fruit;
                dict.remove(fruit);
                break;

            case 4:
                dict.display();
                break;

            case 5:
                cout << "Thank you for using the Fruit Dictionary.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
