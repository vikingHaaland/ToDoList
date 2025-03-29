#include "task.h"
#include <sstream>
using namespace std;

Task::Task(const string &desc, TaskPriority prio, const string &date, bool complete)
    : description(desc), priority(prio), dueDate(date), isComplete(complete) {}

string Task::toString() const {
    return description + "|" + to_string(priority) + "|" + dueDate + "|" + (isComplete ? "1" : "0");
}

Task Task::fromString(const string &data) {
    size_t pos1 = data.find("|");
    size_t pos2 = data.find("|", pos1 + 1);
    size_t pos3 = data.find("|", pos2 + 1);

    string desc = data.substr(0, pos1);
    int prio = stoi(data.substr(pos1 + 1, pos2 - pos1 - 1));
    string date = data.substr(pos2 + 1, pos3 - pos2 - 1);
    bool complete = (data.substr(pos3 + 1) == "1");

    return Task(desc, static_cast<TaskPriority>(prio), date, complete);
}

string Task::getDescription() const {
    return description;
}

TaskPriority Task::getPriority() const {
    return priority;
}

string Task::getDueDate() const {
    return dueDate;
}

bool Task::getStatus() const {
    return isComplete;
}

void Task::markComplete() {
    isComplete = true;
}

void Task::markIncomplete() {
    isComplete = false;
}