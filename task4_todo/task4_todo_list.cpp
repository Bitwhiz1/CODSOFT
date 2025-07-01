#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
using namespace std;

struct Task {
    string description;
    bool completed;
    string timestamp;
};

string getTime() {
    time_t now = time(0);
    tm* local = localtime(&now);
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", local);
    return string(buf);
}

void loadTasks(vector<Task>& tasks, const string& file) {
    ifstream in(file);
    if (!in.is_open()) return;
    string line;
    while (getline(in, line)) {
        size_t a = line.find('|');
        size_t b = line.find('|', a + 1);
        if (a == string::npos || b == string::npos) continue;
        Task t;
        t.completed = line.substr(0, a) == "1";
        t.description = line.substr(a + 1, b - a - 1);
        t.timestamp = line.substr(b + 1);
        tasks.push_back(t);
    }
    in.close();
}

void saveTasks(const vector<Task>& tasks, const string& file) {
    ofstream out(file);
    for (const auto& t : tasks)
        out << (t.completed ? "1" : "0") << "|" << t.description << "|" << t.timestamp << "\n";
    out.close();
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks yet.\n";
        return;
    }
    int done = 0;
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "x" : " ") << "] " << tasks[i].description
             << " (" << tasks[i].timestamp << ")\n";
        if (tasks[i].completed) done++;
    }
    cout << "Total: " << tasks.size() << " | Done: " << done << " | Left: " << (tasks.size() - done) << "\n";
}

void addTask(vector<Task>& tasks) {
    cout << "Write your task: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string d;
    getline(cin, d);
    if (d.empty()) {
        cout << "Can't add empty task.\n";
        return;
    }
    for (auto& t : tasks)
        if (t.description == d) {
            cout << "Task already exists.\n";
            return;
        }
    tasks.push_back({d, false, getTime()});
    cout << "Task added.\n";
}

void markDone(vector<Task>& tasks) {
    if (tasks.empty()) return;
    viewTasks(tasks);
    cout << "Which task to mark done? ";
    int i;
    cin >> i;
    if (cin.fail() || i < 1 || i > tasks.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number.\n";
        return;
    }
    if (tasks[i - 1].completed) {
        cout << "Already marked.\n";
        return;
    }
    tasks[i - 1].completed = true;
    cout << "Marked as done.\n";
}

void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) return;
    viewTasks(tasks);
    cout << "Which task to delete? ";
    int i;
    cin >> i;
    if (cin.fail() || i < 1 || i > tasks.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number.\n";
        return;
    }
    cout << "Deleted: " << tasks[i - 1].description << "\n";
    tasks.erase(tasks.begin() + i - 1);
}

void menu() {
    cout << "\n1. View Tasks\n2. Add Task\n3. Mark Done\n4. Delete Task\n5. Save & Exit\nPick: ";
}

int main() {
    vector<Task> tasks;
    string file = "tasks.txt";
    loadTasks(tasks, file);
    int ch;
    do {
        menu();
        cin >> ch;
        switch (ch) {
            case 1: viewTasks(tasks); break;
            case 2: addTask(tasks); break;
            case 3: markDone(tasks); break;
            case 4: deleteTask(tasks); break;
            case 5: saveTasks(tasks, file); cout << "Saved. Goodbye.\n"; break;
            default: cout << "Wrong option.\n";
        }
    } while (ch != 5);
    return 0;
}
