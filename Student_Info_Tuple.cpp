#include <iostream>
#include <fstream>
#include <tuple>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Function to add a student
void addStudent(vector<tuple<string, string, string, string>>& students) {
    string name, className, roll, phoneNumber;

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter Class: ";
    cin >> className;

    cout << "Enter Roll: ";
    cin >> roll;

    cout << "Enter Phone Number: ";
    cin >> phoneNumber;

    students.push_back(make_tuple(name, className, roll, phoneNumber));
    cout << "Student added successfully!" << endl;
}

// Function to remove a student
void removeStudent(vector<tuple<string, string, string, string>>& students) {
    string name;

    cout << "Enter the name of the student to remove: ";
    cin >> name;

    auto it = find_if(students.begin(), students.end(), [name](const auto& student) {
        return get<0>(student) == name;
    });

    if (it != students.end()) {
        students.erase(it);
        cout << "Student removed successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

// Function to edit a student
void editStudent(vector<tuple<string, string, string, string>>& students) {
    string name;

    cout << "Enter the name of the student to edit: ";
    cin >> name;

    auto it = find_if(students.begin(), students.end(), [name](const auto& student) {
        return get<0>(student) == name;
    });

    if (it != students.end()) {
        string newName, newClass, newRoll, newPhoneNumber;

        cout << "Enter new Name: ";
        cin >> newName;

        cout << "Enter new Class: ";
        cin >> newClass;

        cout << "Enter new Roll: ";
        cin >> newRoll;

        cout << "Enter new Phone Number: ";
        cin >> newPhoneNumber;

        *it = make_tuple(newName, newClass, newRoll, newPhoneNumber);
        cout << "Student edited successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

// Function to save students to a file
void saveToFile(const vector<tuple<string, string, string, string>>& students) {
    ofstream file("students.txt");

    for (const auto& student : students) {
        file << get<0>(student) << " " << get<1>(student) << " " << get<2>(student) << " " << get<3>(student) << endl;
    }

    cout << "Students saved to file!" << endl;
}

// Function to load students from a file
void loadFromFile(vector<tuple<string, string, string, string>>& students) {
    ifstream file("students.txt");

    if (file.is_open()) {
        string name, className, roll, phoneNumber;

        while (file >> name >> className >> roll >> phoneNumber) {
            students.push_back(make_tuple(name, className, roll, phoneNumber));
        }

        cout << "Students loaded from file!" << endl;
    } else {
        cout << "Unable to open file!" << endl;
    }
}

int main() {
    vector<tuple<string, string, string, string>> students;

    loadFromFile(students);

    int choice;

    do {
        cout << "\n1. Add Student\n2. Remove Student\n3. Edit Student\n4. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                removeStudent(students);
                break;
            case 3:
                editStudent(students);
                break;
            case 4:
                saveToFile(students);
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
}
