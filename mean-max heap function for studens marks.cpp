#include <iostream>
using namespace std;
#define MAX 20

class StudentHeap {
    int marks[MAX]{};

public:
    void insertHeap(int n);
    void displayHeap(int n);
    void showMax(int n);
    void showMin() { cout << "Min marks: " << marks[1] << endl; }
};

void StudentHeap::insertHeap(int n) {
    for (int i = 1; i <= n; i++) {
        cout << "Enter marks: ";
        cin >> marks[i];
        int j = i, parent = j / 2;
        while (j > 1 && marks[j] < marks[parent]) {
            swap(marks[j], marks[parent]);
            j = parent;
            parent = j / 2;
        }
    }
}

void StudentHeap::displayHeap(int n) {
    cout << "\nHeap Structure:\n";
    for (int i = 1, level = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) cout << endl;
        cout << marks[i] << " ";
    }
    cout << endl;
}

void StudentHeap::showMax(int n) {
    int maxMark = marks[1];
    for (int i = 2; i <= n; i++)
        maxMark = max(maxMark, marks[i]);
    cout << "Max marks: " << maxMark << endl;
}

int main() {
    StudentHeap heap;
    int choice, n;

    // Show menu once at the beginning
    cout << "\n1. Insert Marks\n2. Display Min Heap\n3. Find Max Marks\n4. Find Min Marks\n5. Exit\n";

    do {
        cout << "\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Number of students: ";
            cin >> n;
            heap.insertHeap(n);
        } else if (choice == 2) heap.displayHeap(n);
        else if (choice == 3) heap.showMax(n);
        else if (choice == 4) heap.showMin();
    } while (choice != 5);
    
    return 0;
}
