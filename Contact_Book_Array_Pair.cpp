#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

using namespace std;

// Define a pair for contact information (name, number)
using Contact = pair<string, string>;

const string FILENAME = "contacts.txt";
const int MAX_CONTACTS = 1000;

// Function to save contacts to a file
void saveContacts(const array<Contact, MAX_CONTACTS>& contacts, int contactCount) {
    ofstream outFile(FILENAME);

    if (outFile.is_open()) {
        for (int i = 0; i < contactCount; ++i) {
            outFile << contacts[i].first << "," << contacts[i].second << "\n";
        }
        outFile.close();
        cout << "Contacts saved to " << FILENAME << endl;
    } else {
        cout << "Unable to open file for saving contacts.\n";
    }
}

// Function to load contacts from a file
int loadContacts(array<Contact, MAX_CONTACTS>& contacts) {
    ifstream inFile(FILENAME);
    int contactCount = 0;

    if (inFile.is_open()) {
        while (contactCount < MAX_CONTACTS && getline(inFile, contacts[contactCount].first, ',') &&
               getline(inFile, contacts[contactCount].second)) {
            ++contactCount;
        }
        inFile.close();
    } else {
        cout << "Unable to open file for loading contacts.\n";
    }

    return contactCount;
}

int main() {
    // Define an array of pairs to store contacts
    array<Contact, MAX_CONTACTS> contacts;

    int contactCount = loadContacts(contacts);

    while (true) {
        cout << "\nContact Book\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Save Contacts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                if (contactCount < MAX_CONTACTS) {
                    cin.ignore(); // Clear the newline character from the buffer

                    string name, number;
                    cout << "Enter contact name: ";
                    getline(cin, name);

                    cout << "Enter contact number: ";
                    getline(cin, number);

                    contacts[contactCount++] = make_pair(name, number);

                    // Sort the contacts array by names
                    sort(contacts.begin(), contacts.begin() + contactCount, [](const Contact& a, const Contact& b) {
                        return a.first < b.first;
                    });

                    cout << "Contact added successfully!\n";
                } else {
                    cout << "Contact book is full.\n";
                }
                break;
            }
            case 2:
                if (contactCount > 0) {
                    cout << "\nContacts:\n";
                    for (int i = 0; i < contactCount; ++i) {
                        cout << i + 1 << ". " << contacts[i].first << ": " << contacts[i].second << endl;
                    }
                } else {
                    cout << "No contacts available.\n";
                }
                break;
            case 3:
                saveContacts(contacts, contactCount);
                break;
            case 0:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
