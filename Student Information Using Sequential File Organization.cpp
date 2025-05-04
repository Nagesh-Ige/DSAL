#include <iostream>
#include <vector>
#include <limits>  // For clearing input buffer
using namespace std;

struct Student {
    int rollNo;
    string name, division, address;
};

vector<Student> students;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addStudent() {
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    clearInput();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Division: ";
    getline(cin, s.division);

    cout << "Enter Address: ";
    getline(cin, s.address);

    students.push_back(s);
    cout << "✔ Student added successfully.\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    cout << "\n--- Student Records ---\n";
    for (const auto& s : students) {
        cout << "Roll No: " << s.rollNo
             << ", Name: " << s.name
             << ", Division: " << s.division
             << ", Address: " << s.address << "\n";
    }
}

void searchStudent(int rollNo) {
    for (const auto& s : students) {
        if (s.rollNo == rollNo) {
            cout << "\n Student Found:\n"
                 << "Roll No: " << s.rollNo
                 << "\nName: " << s.name
                 << "\nDivision: " << s.division
                 << "\nAddress: " << s.address << "\n";
            return;
        }
    }
    cout << " Student not found.\n";
}

void deleteStudent(int rollNo) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNo == rollNo) {
            students.erase(it);
            cout << "✔ Student deleted successfully.\n";
            return;
        }
    }
    cout << " Student not found.\n";
}

int main() {
    int choice, rollNo;
    do {
        cout << "\n==== Student Record Menu ====\n"
             << "1. Add Student\n"
             << "2. Display All\n"
             << "3. Search Student\n"
             << "4. Delete Student\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                searchStudent(rollNo);
                break;
            case 4:
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 5:
                cout << " Exiting the program. Goodbye!\n";
                break;
            default:
                cout << " Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
