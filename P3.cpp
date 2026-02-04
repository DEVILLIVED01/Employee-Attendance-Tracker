#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>
using namespace std;
const string EMPLOYEE_FILE = "employees.txt";
const string ATTENDANCE_FILE = "attendance.txt";
map<string, string> loadEmployees() {
    map<string, string> employees;
    ifstream file(EMPLOYEE_FILE);
    string id, name;
    while (file >> id) {
        getline(file, name);
        if (!name.empty() && name[0] == ' ') name = name.substr(1);
        employees[id] = name;
    }
    file.close();
    return employees;
}
void saveEmployee(const string& id, const string& name) {
    ofstream file(EMPLOYEE_FILE, ios::app);
    file << id << " " << name << endl;
    file.close();
}
void markAttendance(const string& id) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    ofstream file(ATTENDANCE_FILE, ios::app);
    file << id << " "
         << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-"
         << ltm->tm_mday << " "
         << ltm->tm_hour << ":"
         << ltm->tm_min << ":"
         << ltm->tm_sec << endl;

    file.close();
    cout << "Attendance marked successfully.\n";
}
void viewAttendance() {
    ifstream file(ATTENDANCE_FILE);
    string id, date, time;
    cout << "\n--- Attendance Records ---\n";
    while (file >> id >> date >> time) {
        cout << "Employee ID: " << id << " | Date: " << date << " | Time: " << time << endl;
    }
    file.close();
}
int main() {
    int choice;
    string emp_id, emp_name;
    map<string, string> employees;
    do {
        cout << "\n===== Employee Attendance Tracker =====\n";
        cout << "1. Add New Employee\n";
        cout << "2. Mark Attendance\n";
        cout << "3. View Attendance\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter Employee ID: ";
                getline(cin, emp_id);
                cout << "Enter Employee Name: ";
                getline(cin, emp_name);
                saveEmployee(emp_id, emp_name);
                cout << "Employee added successfully.\n";
                break;
            case 2:
                cout << "Enter Employee ID: ";
                getline(cin, emp_id);
                employees = loadEmployees();
                if (employees.find(emp_id) != employees.end()) {
                    markAttendance(emp_id);
                } else {
                    cout << "Employee ID not found. Please add the employee first.\n";
                }
                break;

            case 3:
                viewAttendance();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}
