#include <iostream>
#include <cstring>
using namespace std;

class Flight {
    int am[10][10] = {0};
    char city_index[10][10];
    int city_count = 0;

public:
    Flight() {
        for (int i = 0; i < 10; i++)
            strcpy(city_index[i], "xx");
    }

    void create();
    void display();
};

void Flight::create() {
    char s[10], d[10], c;
    int si, di, wt;

    do {
        cout << "\nEnter Source City Name: ";
        cin >> s;
        cout << "Enter Destination City Name: ";
        cin >> d;

        si = di = -1;
        for (int i = 0; i < city_count; i++) {
            if (strcmp(city_index[i], s) == 0)
                si = i;
            if (strcmp(city_index[i], d) == 0)
                di = i;
        }

        if (si == -1) {
            strcpy(city_index[city_count], s);
            si = city_count++;
        }

        if (di == -1) {
            strcpy(city_index[city_count], d);
            di = city_count++;
        }

        cout << "Enter Distance between " << s << " and " << d << ": ";
        cin >> wt;

        am[si][di] = wt;

        cout << "Do you want to add more cities? (y/n): ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
}

void Flight::display() {
    cout << "\nAdjacency Matrix (Distances between Cities):\n\n";
    cout << "\t";
    for (int i = 0; i < city_count; i++)
        cout << city_index[i] << "\t";
    cout << "\n";
    for (int i = 0; i < city_count; i++) {
        cout << city_index[i] << "\t";
        for (int j = 0; j < city_count; j++)
            cout << am[i][j] << "\t";
        cout << "\n";
    }
}

int main() {
    Flight f;
    int choice;
    do {
        cout << "\n=== FLIGHT ROUTE MENU ===\n";
        cout << "1. Create Flight Routes\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                f.create();
                break;
            case 2:
                f.display();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
