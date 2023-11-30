#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

class ToDoList {
private:
    queue<string> tasks;
    const string filename = "tasks.txt";

public:
    ToDoList() {
        loadTasks();
    }

    ~ToDoList() {
        saveTasks();
    }

    void addTask(const string& task) {
        tasks.push(task);
        cout << "Task added: " << task << endl;
        saveTasks();
    }

    void completeTask() {
        if (!tasks.empty()) {
            cout << "Completed task: " << tasks.front() << endl;
            tasks.pop();
            saveTasks();
        } else {
            cout << "No tasks to complete." << endl;
        }
    }

    void viewTasks() {
        if (!tasks.empty()) {
            cout << "Tasks in the To-Do List:" << endl;
            queue<string> temp = tasks;
            while (!temp.empty()) {
                cout << "- " << temp.front() << endl;
                temp.pop();
            }
        } else {
            cout << "No tasks in the To-Do List." << endl;
        }
    }

    void loadTasks() {
        ifstream file(filename);
        if (file.is_open()) {
            string task;
            while (getline(file, task)) {
                tasks.push(task);
            }
            file.close();
        }
    }

    void saveTasks() {
        ofstream file(filename);
        if (file.is_open()) {
            queue<string> temp = tasks;
            while (!temp.empty()) {
                file << temp.front() << endl;
                temp.pop();
            }
            file.close();
        }
    }
};

int main() {
    ToDoList toDoList;
    int choice;

    do {
        cout << "\nTo-Do List Program\n";
        cout << "1. Add Task\n";
        cout << "2. Complete Task\n";
        cout << "3. View Tasks\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore(); // Clear the newline character from the buffer
                string task;
                cout << "Enter the task: ";
                getline(cin, task);
                toDoList.addTask(task);
                break;
            }
            case 2:
                toDoList.completeTask();
                break;
            case 3:
                toDoList.viewTasks();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
