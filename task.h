#ifndef TASK_H
#define TASK_H
#include <string>
using namespace std;

enum TaskPriority { LOW, MEDIUM, HIGH };

class Task {
    string description;
    TaskPriority priority;
    string dueDate;  
    bool isComplete;      

public:
    Task(const string &desc, TaskPriority prio, const string &date, bool complete = false);
    string getDescription() const;
    TaskPriority getPriority() const;
    string getDueDate() const;  
    bool getStatus() const;          
    void markComplete();             
    void markIncomplete();           
    string toString() const;
    static Task fromString(const string &data);
};

#endif