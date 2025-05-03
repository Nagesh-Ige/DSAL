#include <iostream>
#include <iomanip>
using namespace std;

class Tree {
    int a[20][20], v, e, visited[20] = {0};

public:
    void input();
    void display();
    void minimum();
};

void Tree::input() {
    cout << "\nEnter the number of branches (nodes): ";
    cin >> v;

    // Initialize adjacency matrix with 999 (representing no direct connection)
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            a[i][j] = 999;

    cout << "Enter the number of connections (edges): ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        int u, v2, cost;
        cout << "\nEnter Source Branch (1-" << v << "): ";
        cin >> u;
        cout << "Enter Destination Branch (1-" << v << "): ";
        cin >> v2;
        cout << "Enter the Charge between Branch " << u << " and Branch " << v2 << ": ";
        cin >> cost;

        a[u - 1][v2 - 1] = cost;
        a[v2 - 1][u - 1] = cost;
    }
}

void Tree::display() {
    cout << "\nAdjacency Matrix (Charge between Branches):\n\n";
    cout << setw(6) << " ";
    for (int i = 0; i < v; i++)
        cout << setw(6) << "B" << (i + 1);
    cout << "\n";

    for (int i = 0; i < v; i++) {
        cout << setw(6) << "B" << (i + 1);
        for (int j = 0; j < v; j++) {
            if (a[i][j] == 999)
                cout << setw(6) << "-";
            else
                cout << setw(6) << a[i][j];
        }
        cout << "\n";
    }
}

void Tree::minimum() {
    int total = 0;
    visited[0] = 1;
    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";

    for (int count = 0; count < v - 1; count++) {
        int min = 999, p = -1, q = -1;

        for (int i = 0; i < v; i++) {
            if (visited[i]) {
                for (int j = 0; j < v; j++) {
                    if (!visited[j] && a[i][j] < min) {
                        min = a[i][j];
                        p = i;
                        q = j;
                    }
                }
            }
        }

        visited[q] = 1;
        total += min;

        cout << "Selected Edge: Branch " << (p + 1)
             << " to Branch " << (q + 1)
             << " | Charge: " << min << "\n";
    }

    cout << "\nTotal Minimum Cost to Connect All Branches: " << total << "\n";
}

int main() {
    Tree t;
    int ch;

    do {
        cout << "\n---------- MENU ----------\n";
        cout << "1. Enter Branch Connections and Charges\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Find Minimum Connection Cost (MST)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: t.input(); break;
            case 2: t.display(); break;
            case 3: t.minimum(); break;
            case 4: cout << "Exiting the program.\n"; break;
            default: cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    } while (ch != 4);

    return 0;
}
