#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

int timeToMinutes(const string &time) {
    int hours, minutes;
    char colon;
    stringstream timeStream(time);
    timeStream >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

int calculateTimeDifference(const string &starttime, const string &endtime) {
    int startMinutes = timeToMinutes(starttime);
    int endMinutes = timeToMinutes(endtime);
    if (endMinutes < startMinutes) {
        endMinutes += 24 * 60;
    }
    return endMinutes - startMinutes;
}

pair<string, string> generatetime() {
    int firsthour = rand() % 24;
    int firstminutes = rand() % 60;
    int lasthour = (firsthour + rand() % 12) % 24; 
    int lastminutes = rand() % 60;

    char checkin[6];
    snprintf(checkin, sizeof(checkin), "%02d:%02d", firsthour, firstminutes);

    char checkout[6];
    snprintf(checkout, sizeof(checkout), "%02d:%02d", lasthour, lastminutes);
    return {string(checkin), string(checkout)};
}

class RandomEmployeeGenerator {
private:
    string names[20] = {"Alice", "Bob", "Charlie", "David", "Emma", "Frank", "Grace", "Hannah", "Ivy", "Jack", "Katie", "Liam", "Mia", "Nathan", "Olivia", "Paul", "Quinn", "Rachel", "Sam", "Tina"};
    int id[20];
    int payment[20]; 
    string departments[3] = {"HR", "IT", "Finance"};
    string roles_it[5] = {"Entry-level IT support", "Network Administrator", "Software Developer", "Software Engineer", "IT Manager"};
    string roles_HR[3] = {"Entry-level HR assistant", "HR Specialist", "HR Manager"};
    string roles_Finance[4] = {"Entry-level Finance analyst", "Accountant", "Senior Financial Analyst", "Finance Director"};
    string employeeDepartments[20];
    string employeeRoles[20];
    string checkin[20];
    string checkout[20];
    int diff[20];  

public:
    RandomEmployeeGenerator() {
        srand(time(0));

        for (int i = 0; i < 20; ++i) {
            id[i] = rand() % 20; // Ensure unique IDs
            int depIndex = rand() % 3; 
            employeeDepartments[i] = departments[depIndex];
            switch (depIndex) {
                case 0: // HR
                    employeeRoles[i] = roles_HR[rand() % 3];
                    if (employeeRoles[i] == "Entry-level HR assistant") {
                        payment[i] = rand() % 11 + 15; // 15-25
                    } else if (employeeRoles[i] == "HR Specialist") {
                        payment[i] = rand() % 11 + 25; // 25-35
                    } else if (employeeRoles[i] == "HR Manager") {
                        payment[i] = rand() % 21 + 35; // 35-55
                    }
                    break;
                case 1: // IT
                    employeeRoles[i] = roles_it[rand() % 5];
                    if (employeeRoles[i] == "Entry-level IT support") {
                        payment[i] = rand() % 11 + 20; // 20-30
                    } else if (employeeRoles[i] == "Network Administrator") {
                        payment[i] = rand() % 16 + 30; // 30-45
                    } else if (employeeRoles[i] == "Software Developer") {
                        payment[i] = rand() % 26 + 35; // 35-60
                    } else if (employeeRoles[i] == "Software Engineer") {
                        payment[i] = rand() % 26 + 35; // 35-60
                    } else if (employeeRoles[i] == "IT Manager") {
                        payment[i] = rand() % 31 + 50; // 50-80
                    }
                    break;
                case 2: // Finance
                    employeeRoles[i] = roles_Finance[rand() % 4];
                    if (employeeRoles[i] == "Entry-level Finance analyst") {
                        payment[i] = rand() % 11 + 25; // 25-35
                    } else if (employeeRoles[i] == "Accountant") {
                        payment[i] = rand() % 16 + 30; // 30-45
                    } else if (employeeRoles[i] == "Senior Financial Analyst") {
                        payment[i] = rand() % 26 + 45; // 45-70
                    } else if (employeeRoles[i] == "Finance Director") {
                        payment[i] = rand() % 51 + 70; // 70-120
                    }
                    break;
            }
            auto times = generatetime();
            checkin[i] = times.first;
            checkout[i] = times.second;
            diff[i] = calculateTimeDifference(checkin[i], checkout[i]);
        }
    }

    void print(std::ostream &out = cout) {
        for (int i = 0; i < 20; ++i) {
            int hoursWorked = diff[i] / 60;
            int money = hoursWorked * payment[i];
            int minutesWorked = diff[i] % 60;
            out << "Employee name: " << names[i] << endl;
            out << "Employee ID: " << id[i] << endl;
            out << "Department: " << employeeDepartments[i] << endl;
            out << "Department work role: " << employeeRoles[i] << endl;
            out << "Check-in time: " << checkin[i] << endl;
            out << "Check-out time: " << checkout[i] << endl;
            out << "Worked for: " << hoursWorked << " hours and " << minutesWorked << " minutes" << endl;
            out << "Payment per hour: " << payment[i] << "$" << endl;
            out << "Total profit made: " << money << "$" << endl;
            out << "-------------------------" << endl;
        }
    }

    void printEmployeeById(int employeeId, std::ostream &out = cout) {
        for (int i = 0; i < 20; ++i) {
            if (id[i] == employeeId) {
                int hoursWorked = diff[i] / 60;
                int minutesWorked = diff[i] % 60;
                int money = hoursWorked * payment[i];
                out << "Employee name: " << names[i] << endl;
                out << "Employee ID: " << id[i] << endl;
                out << "Department: " << employeeDepartments[i] << endl;
                out << "Department work role: " << employeeRoles[i] << endl;
                out << "Check-in time: " << checkin[i] << endl;
                out << "Check-out time: " << checkout[i] << endl;
                out << "Worked for: " << hoursWorked << " hours and " << minutesWorked << " minutes" << endl;
                out << "Payment per hour: " << payment[i] << "$" << endl;
                out << "Total profit made: " << money << "$" << endl;
                out << "-------------------------" << endl;
                return;
            }
        }
        out << "Employee with ID " << employeeId << " not found." << endl;
    }
};

void inspectEmployeeById(const string &filename, int employeeId) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Unable to open file" << endl;
        return;
    }

    string line;
    bool employeeFound = false;
    while (getline(inFile, line)) {
        if (line.find("Employee ID: " + to_string(employeeId)) != string::npos) {
            employeeFound = true;
            cout << line << endl;
            for (int i = 0; i < 8; ++i) { // Reading 8 lines including separators
                getline(inFile, line);
                cout << line << endl;
            }
            break;
        }
    }

    if (!employeeFound) {
        cout << "Employee with ID " << employeeId << " not found in file." << endl;
    }
    inFile.close();
}

int main() {
    RandomEmployeeGenerator reg;
    reg.print();

    ofstream employeefile("employee.txt");
    if (employeefile.is_open()) {
        reg.print(employeefile);
        employeefile.close();
        cout << "Successfully wrote to the file." << endl;
    } else {
        cerr << "Unable to open file" << endl;
    }

    int employeeId;
    cout << "Which one would you want to inspect (ID number)? ";
    cin >> employeeId;
    system("CLS");
    inspectEmployeeById("employee.txt", employeeId);

    string ans2;
    cout << "Would you want to run a simulation? ";
    cin >> ans2;
    if (ans2 == "yes") {
        // call function for simulating
    } else {
        cout << "Exiting program." << endl;
    }

    return 0;
}
