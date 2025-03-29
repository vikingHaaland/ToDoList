#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "task.h"

using namespace std;

vector<Task> tasks;

void displayMenu() {
    cout<<"\n===== To-Do List App ====="<<endl;
    cout<<"1. Add Task"<<endl;
    cout<<"2. View Tasks"<<endl;
    cout<<"3. Edit Task"<<endl;
    cout<<"4. Mark Task as Complete"<<endl;
    cout<<"5. Delete Task"<<endl;
    cout<<"6. Save & Exit"<<endl;
    cout<<"Select an option: ";
}

void loadTasksFromFile() {
    ifstream file("tasks.txt");
    if(!file) return;  
    string line;
    while(getline(file, line)) tasks.push_back(Task::fromString(line));
    file.close();
}

void saveTasksToFile() {
    ofstream file("tasks.txt");
    for(const auto &task : tasks) file << task.toString()<<"\n"; 
    file.close();
}

void addTask() {
    string title, dueDate;
    int priority;

    cout<<"Enter task title: ";
    cin.ignore();
    getline(cin, title);

    cout<<"Enter task priority (0: LOW, 1: MEDIUM, 2: HIGH): ";
    cin>>priority;

    cout<<"Enter due date (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, dueDate);

    tasks.emplace_back(title, static_cast<TaskPriority>(priority), dueDate, false); 
    cout<<"Task added successfully!"<<endl;
}

// View all tasks
void viewTasks() {
    if(tasks.empty()) {
        cout<<"No tasks available."<<endl;
        return;
    }

    cout<< "\nYour Tasks:"<<endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        cout<<i + 1<<". "<<tasks[i].getDescription()<<" [";
        cout<<(tasks[i].getPriority() == LOW ? "LOW" : tasks[i].getPriority() == MEDIUM ? "MEDIUM" : "HIGH")<<"]";
        cout<<" Due: "<<tasks[i].getDueDate()<<" ["<<(tasks[i].getStatus() ? "Completed" : "Pending")<<"]"<<endl;
    }
}

void editTask() {
    viewTasks();
    if(tasks.empty()) return;

    int index;
    cout<<"Enter task number to edit: ";
    cin>>index;

    if(index < 1 || index > tasks.size()) {
        cout<<"Invalid task number."<<endl;
        return;
    }

    string newTitle, newDueDate;
    int newPriority;
    char changeCompletion;

    cout<<"Enter new title (leave empty to keep current): ";
    cin.ignore();
    getline(cin, newTitle);

    cout<<"Enter new priority (0: LOW, 1: MEDIUM, 2: HIGH, -1 to keep current): ";
    cin>>newPriority;

    cout<<"Enter new due date (YYYY-MM-DD, leave empty to keep current): ";
    cin.ignore();
    getline(cin, newDueDate);

    Task &task = tasks[index - 1];

    cout<<"Task is currently marked as "<<(task.getStatus() ? "Completed" : "Pending")<<". Change status? (y/n): ";
    cin>>changeCompletion;

    if(changeCompletion == 'y' || changeCompletion == 'Y') {
        if(task.getStatus()) {
            task.markIncomplete();
            cout<<"Task marked as incomplete."<<endl;
        } else {
            task.markComplete();
            cout<<"Task marked as complete."<<endl;
        }
    }

    if(!newTitle.empty()) task = Task(newTitle, (newPriority >= 0) ? static_cast<TaskPriority>(newPriority) : task.getPriority(), newDueDate.empty() ? task.getDueDate() : newDueDate, task.getStatus());

    cout<<"Task updated successfully!"<<endl;
}


void markTaskComplete() {
    viewTasks();
    if(tasks.empty()) return;

    int index;
    cout<<"Enter task number to mark as complete: ";
    cin>>index;

    if(index > 0 && index <= tasks.size()) {
        tasks[index - 1].markComplete(); 
        cout<<"Task marked as complete!"<<endl;
    } else cout<<"Invalid task number."<<endl;
}

void deleteTask() {
    viewTasks();
    if(tasks.empty()) return;

    int index;
    cout<<"Enter task number to delete: ";
    cin>>index;

    if(index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout<<"Task deleted successfully!"<<endl;
    } else cout<<"Invalid task number."<<endl;
}

int main() {
    loadTasksFromFile();  

    int choice;
    do{
        displayMenu();
        cin>>choice;

        switch(choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: editTask(); break;
            case 4: markTaskComplete(); break;
            case 5: deleteTask(); break;
            case 6: 
                saveTasksToFile();
                cout<<"Saving and Exiting..."<<endl; 
                break;
            default: cout<<"Invalid option. Try again."<<endl;
        }

    } while(choice != 6);
    return 0;
}