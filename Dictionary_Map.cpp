#include <iostream>
#include <map>
#include <fstream> // Include for file operations

using namespace std;

// Function to display the menu
void displayMenu() {
    cout << "\nDictionary Menu:\n";
    cout << "1. Add Word\n";
    cout << "2. Search Word\n";
    cout << "3. Edit Meaning\n";
    cout << "4. Delete Word\n";
    cout << "5. Display Dictionary\n";
    cout << "6. Save to File\n";
    cout << "7. Load from File\n";
    cout << "8. Exit\n";
}

// Function to save the dictionary to a file
void saveToFile(const map<string, string>& dictionary, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& entry : dictionary) {
            file << entry.first << ": " << entry.second << endl;
        }

        cout << "Dictionary saved to file: " << filename << endl;
        file.close();
    } else {
        cerr << "Error opening file for writing: " << filename << endl;
    }
}

// Function to load the dictionary from a file
void loadFromFile(map<string, string>& dictionary, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        dictionary.clear(); // Clear existing dictionary

        string line;
        while (getline(file, line)) {
            size_t pos = line.find(": ");
            if (pos != string::npos) {
                string word = line.substr(0, pos);
                string meaning = line.substr(pos + 2);
                dictionary[word] = meaning;
            }
        }

        cout << "Dictionary loaded from file: " << filename << endl;
        file.close();
    } else {
        cerr << "Error opening file for reading: " << filename << endl;
    }
}

int main() {
    map<string, string> dictionary;
    string filename = "dictionary.txt";

    while (true) {
        displayMenu();

        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add Word
                string word, meaning;
                cout << "Enter the word: ";
                cin >> word;
                cout << "Enter the meaning: ";
                cin.ignore(); // Clear the newline character from the buffer
                getline(cin, meaning);
                dictionary[word] = meaning;
                cout << "Word added to the dictionary.\n";
                break;
            }

            case 2: {
                // Search Word
                string word;
                cout << "Enter the word to search: ";
                cin >> word;
                auto it = dictionary.find(word);
                if (it != dictionary.end()) {
                    cout << "Meaning: " << it->second << endl;
                } else {
                    cout << "Word not found in the dictionary.\n";
                }
                break;
            }

            case 3: {
                // Edit Meaning
                string word, newMeaning;
                cout << "Enter the word to edit: ";
                cin >> word;
                auto it = dictionary.find(word);
                if (it != dictionary.end()) {
                    cout << "Enter the new meaning: ";
                    cin.ignore();
                    getline(cin, newMeaning);
                    it->second = newMeaning;
                    cout << "Meaning updated.\n";
                } else {
                    cout << "Word not found in the dictionary.\n";
                }
                break;
            }

            case 4: {
                // Delete Word
                string word;
                cout << "Enter the word to delete: ";
                cin >> word;
                auto it = dictionary.find(word);
                if (it != dictionary.end()) {
                    dictionary.erase(it);
                    cout << "Word deleted from the dictionary.\n";
                } else {
                    cout << "Word not found in the dictionary.\n";
                }
                break;
            }

            case 5: {
                // Display Dictionary
                cout << "\nDictionary:\n";
                for (const auto& entry : dictionary) {
                    cout << entry.first << ": " << entry.second << endl;
                }
                break;
            }

              case 6: {
                // Save to File
                saveToFile(dictionary, filename);
                break;
            }

            case 7: {
                // Load from File
                loadFromFile(dictionary, filename);
                break;
            }

            case 8:
                // Exit
                cout << "Exiting the program. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
