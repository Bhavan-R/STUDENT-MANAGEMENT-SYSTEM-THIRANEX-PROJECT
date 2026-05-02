#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <limits>
#include <cctype>

using namespace std;

struct StudentRecord {
    int id;
    string name;
    string email;
    int age;
    int semester;
    double gpa;
    string course;
    string createdDate;
    string lastUpdated;
};

class StudentManagementSystem {
private:
    vector<StudentRecord> studentDatabase;
    unordered_map<int, size_t> studentIndex;
    const string DATA_FILE = "student_database.dat";
    const int MAX_CAPACITY = 1000000;

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool isValidEmail(const string& email) {
        if (email.empty() || email.size() > 100) return false;
        
        size_t atPos = email.find('@');
        if (atPos == string::npos || atPos == 0 || atPos == email.size() - 1) return false;
        
        size_t dotPos = email.find('.', atPos + 1);
        return dotPos != string::npos && dotPos < email.size() - 1;
    }

    bool isValidName(const string& name) {
        if (name.empty() || name.size() > 50) return false;
        for (char c : name) {
            if (!isalpha(c) && !isspace(c)) return false;
        }
        return true;
    }

    bool isValidCourse(const string& course) {
        if (course.empty() || course.size() > 30) return false;
        return true;
    }

    void buildIndex() {
        studentIndex.clear();
        for (size_t i = 0; i < studentDatabase.size(); i++) {
            studentIndex[studentDatabase[i].id] = i;
        }
    }

    string formatTimestamp(const chrono::system_clock::time_point& time) {
        auto time_t = chrono::system_clock::to_time_t(time);
        stringstream ss;
        ss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M");
        return ss.str();
    }

    StudentRecord parseStudentData(const string& line) {
        StudentRecord record;
        stringstream ss(line);
        string field;

        getline(ss, field, '|'); record.id = stoi(field);
        getline(ss, record.name, '|');
        getline(ss, record.email, '|');
        getline(ss, field, '|'); record.age = stoi(field);
        getline(ss, field, '|'); record.semester = stoi(field);
        getline(ss, field, '|'); record.gpa = stod(field);
        getline(ss, record.course, '|');
        getline(ss, record.createdDate, '|');
        getline(ss, record.lastUpdated, '|');

        return record;
    }

    string serializeStudent(const StudentRecord& record) {
        stringstream ss;
        ss << record.id << "|" << record.name << "|" << record.email << "|"
           << record.age << "|" << record.semester << "|" << fixed << setprecision(2) << record.gpa << "|"
           << record.course << "|" << record.createdDate << "|" << record.lastUpdated;
        return ss.str();
    }

    void saveDatabase() {
        ofstream file(DATA_FILE);
        if (file.is_open()) {
            for (const auto& record : studentDatabase) {
                file << serializeStudent(record) << endl;
            }
            file.close();
        }
    }

    void loadDatabase() {
        studentDatabase.clear();
        ifstream file(DATA_FILE);
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                if (!line.empty()) {
                    studentDatabase.push_back(parseStudentData(line));
                }
            }
            file.close();
            buildIndex();
        }
    }

public:
    StudentManagementSystem() {
        loadDatabase();
        cout << "Student Management System initialized. Records loaded: " << studentDatabase.size() << endl;
    }

    ~StudentManagementSystem() {
        saveDatabase();
    }

    int generateStudentID() {
        return studentDatabase.empty() ? 1001 : studentDatabase.back().id + 1;
    }

    bool addStudentRecord() {
        if (studentDatabase.size() >= MAX_CAPACITY) {
            cout << "Database capacity reached. Cannot add more students." << endl;
            return false;
        }

        StudentRecord newRecord;
        newRecord.id = generateStudentID();
        auto now = chrono::system_clock::now();
        newRecord.createdDate = formatTimestamp(now);
        newRecord.lastUpdated = newRecord.createdDate;

        cout << "\n=== Add New Student ===" << endl;
        cout << "Student ID: " << newRecord.id << endl << endl;

        // Validate Name
        string nameInput;
        do {
            cout << "Full Name (letters only, max 50 chars): ";
            getline(cin, nameInput);
            if (!isValidName(nameInput)) {
                cout << "Invalid name. Use letters only (A-Z, a-z, spaces)." << endl;
            }
        } while (!isValidName(nameInput));
        newRecord.name = nameInput;

        // Validate Email
        string emailInput;
        do {
            cout << "Email Address (must contain @ and .): ";
            getline(cin, emailInput);
            if (!isValidEmail(emailInput)) {
                cout << "Invalid email. Must contain '@' and '.' (e.g., user@domain.com)" << endl;
            }
        } while (!isValidEmail(emailInput));
        newRecord.email = emailInput;

        // Validate Age
        do {
            cout << "Age (13-100): ";
            while (!(cin >> newRecord.age)) {
                cout << "Invalid age. Enter a number (13-100): ";
                clearInputBuffer();
            }
            clearInputBuffer();
            if (newRecord.age < 13 || newRecord.age > 100) {
                cout << "Age must be between 13 and 100." << endl;
            }
        } while (newRecord.age < 13 || newRecord.age > 100);

        // Validate Semester
        do {
            cout << "Semester (1-8): ";
            while (!(cin >> newRecord.semester)) {
                cout << "Invalid semester. Enter a number (1-8): ";
                clearInputBuffer();
            }
            clearInputBuffer();
            if (newRecord.semester < 1 || newRecord.semester > 8) {
                cout << "Semester must be between 1 and 8." << endl;
            }
        } while (newRecord.semester < 1 || newRecord.semester > 8);

        // Validate GPA (0-10 scale)
        do {
            cout << "GPA (0.0-10.0): ";
            while (!(cin >> newRecord.gpa)) {
                cout << "Invalid GPA. Enter a number (0.0-10.0): ";
                clearInputBuffer();
            }
            clearInputBuffer();
            if (newRecord.gpa < 0.0 || newRecord.gpa > 10.0) {
                cout << "GPA must be between 0.0 and 10.0." << endl;
            }
        } while (newRecord.gpa < 0.0 || newRecord.gpa > 10.0);

        // Validate Course
        string courseInput;
        do {
            cout << "Course/Program (max 30 chars): ";
            getline(cin, courseInput);
            if (!isValidCourse(courseInput)) {
                cout << "Course name too long or empty. Max 30 characters." << endl;
            }
        } while (!isValidCourse(courseInput));
        newRecord.course = courseInput;

        studentDatabase.push_back(newRecord);
        studentIndex[newRecord.id] = studentDatabase.size() - 1;
        
        cout << "\nStudent record added successfully." << endl;
        return true;
    }

    bool updateStudentRecord(int studentID) {
        auto indexIt = studentIndex.find(studentID);
        if (indexIt == studentIndex.end()) {
            cout << "Student ID not found in database." << endl;
            return false;
        }

        size_t recordIndex = indexIt->second;
        StudentRecord& record = studentDatabase[recordIndex];
        record.lastUpdated = formatTimestamp(chrono::system_clock::now());

        clearInputBuffer();
        cout << "\n=== Update Student ID: " << studentID << " ===" << endl;
        cout << "Current: " << record.name << " | Leave blank to keep current value" << endl << endl;

        string input;
        cout << "Name [" << record.name << "] (letters only): ";
        getline(cin, input);
        if (!input.empty() && isValidName(input)) {
            record.name = input;
        } else if (!input.empty()) {
            cout << "Invalid name format. Keeping original." << endl;
        }

        cout << "Email [" << record.email << "] (@ required): ";
        getline(cin, input);
        if (!input.empty() && isValidEmail(input)) {
            record.email = input;
        } else if (!input.empty()) {
            cout << "Invalid email format. Keeping original." << endl;
        }

        cout << "Age [" << record.age << "] (13-100): ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                int newAge = stoi(input);
                if (newAge >= 13 && newAge <= 100) {
                    record.age = newAge;
                } else {
                    cout << "Age must be 13-100. Keeping original." << endl;
                }
            } catch (...) {
                cout << "Invalid age. Keeping original." << endl;
            }
        }

        cout << "Semester [" << record.semester << "] (1-8): ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                int newSem = stoi(input);
                if (newSem >= 1 && newSem <= 8) {
                    record.semester = newSem;
                } else {
                    cout << "Semester must be 1-8. Keeping original." << endl;
                }
            } catch (...) {
                cout << "Invalid semester. Keeping original." << endl;
            }
        }

        cout << "GPA [" << fixed << setprecision(2) << record.gpa << "] (0.0-10.0): ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                double newGPA = stod(input);
                if (newGPA >= 0.0 && newGPA <= 10.0) {
                    record.gpa = newGPA;
                } else {
                    cout << "GPA must be 0.0-10.0. Keeping original." << endl;
                }
            } catch (...) {
                cout << "Invalid GPA. Keeping original." << endl;
            }
        }

        cout << "Course [" << record.course << "] (max 30 chars): ";
        getline(cin, input);
        if (!input.empty() && isValidCourse(input)) {
            record.course = input;
        } else if (!input.empty()) {
            cout << "Invalid course name. Keeping original." << endl;
        }

        cout << "\nStudent record updated successfully." << endl;
        return true;
    }

    bool removeStudentRecord(int studentID) {
        auto indexIt = studentIndex.find(studentID);
        if (indexIt == studentIndex.end()) {
            cout << "Student ID not found in database." << endl;
            return false;
        }

        cout << "Confirm deletion of Student ID " << studentID << "? (y/n): ";
        char confirm;
        cin >> confirm;
        clearInputBuffer();

        if (confirm == 'y' || confirm == 'Y') {
            size_t recordIndex = indexIt->second;
            studentDatabase.erase(studentDatabase.begin() + recordIndex);
            studentIndex.erase(indexIt);
            buildIndex();
            cout << "Student record removed successfully." << endl;
            return true;
        }
        cout << "Deletion cancelled." << endl;
        return false;
    }

    void viewStudentRecord(int studentID) {
        auto indexIt = studentIndex.find(studentID);
        if (indexIt == studentIndex.end()) {
            cout << "Student record not found." << endl;
            return;
        }

        const StudentRecord& record = studentDatabase[indexIt->second];
        cout << "\n" << string(70, '=') << endl;
        cout << "STUDENT RECORD DETAILS" << endl;
        cout << string(70, '=') << endl;
        cout << left << setw(15) << "ID:" << record.id << endl;
        cout << left << setw(15) << "Name:" << record.name << endl;
        cout << left << setw(15) << "Email:" << record.email << endl;
        cout << left << setw(15) << "Age:" << record.age << endl;
        cout << left << setw(15) << "Semester:" << record.semester << endl;
        cout << left << setw(15) << "GPA:" << fixed << setprecision(2) << record.gpa << endl;
        cout << left << setw(15) << "Course:" << record.course << endl;
        cout << left << setw(15) << "Created:" << record.createdDate << endl;
        cout << left << setw(15) << "Updated:" << record.lastUpdated << endl;
        cout << string(70, '=') << endl;
    }

    void displayAllRecords() {
        if (studentDatabase.empty()) {
            cout << "No student records in database." << endl;
            return;
        }

        cout << "\n" << string(130, '=') << endl;
        cout << "STUDENT DATABASE" << endl;
        cout << string(130, '=') << endl;
        cout << left << setw(6)  << "ID" 
             << setw(25) << "Name" 
             << setw(30) << "Email" 
             << setw(6)  << "Age" 
             << setw(8)  << "Sem" 
             << setw(8)  << "GPA" 
             << setw(20) << "Course" 
             << setw(18) << "Last Updated" << endl;
        cout << string(130, '-') << endl;

        for (const auto& record : studentDatabase) {
            cout << left << setw(6)  << record.id
                 << setw(25) << record.name.substr(0, 24)
                 << setw(30) << record.email.substr(0, 29)
                 << setw(6)  << record.age
                 << setw(8)  << record.semester
                 << setw(8)  << fixed << setprecision(2) << record.gpa
                 << setw(20) << record.course.substr(0, 19)
                 << setw(18) << record.lastUpdated.substr(0, 17) << endl;
        }
        cout << string(130, '=') << endl;
        cout << "Total Records: " << studentDatabase.size() << endl;
    }

    void searchRecords() {
        clearInputBuffer();
        cout << "\n=== Search Options ===" << endl;
        cout << "1. Search by Name" << endl;
        cout << "2. Search by Course" << endl;
        cout << "3. Search by GPA Range" << endl;
        cout << "Choice (1-3): ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 3) {
            clearInputBuffer();
            cout << "Invalid choice. Enter 1, 2, or 3: ";
        }
        clearInputBuffer();

        if (choice == 1) {
            string searchName;
            cout << "Enter name to search: ";
            getline(cin, searchName);
            
            int found = 0;
            for (const auto& record : studentDatabase) {
                if (record.name.find(searchName) != string::npos) {
                    cout << record.id << " - " << record.name << " (Sem " << record.semester << ", GPA " << fixed << setprecision(2) << record.gpa << ")" << endl;
                    found++;
                }
            }
            cout << "Found " << found << " matching records." << endl;
        }
    }

    void showStatistics() {
        if (studentDatabase.empty()) {
            cout << "No data available for statistics." << endl;
            return;
        }

        double totalGPA = 0;
        double maxGPA = 0, minGPA = 10.0;
        int totalAge = 0;
        unordered_map<string, int> courseStats;
        unordered_map<int, int> semesterStats;

        for (const auto& record : studentDatabase) {
            totalGPA += record.gpa;
            totalAge += record.age;
            maxGPA = max(maxGPA, record.gpa);
            minGPA = min(minGPA, record.gpa);
            courseStats[record.course]++;
            semesterStats[record.semester]++;
        }

        cout << "\n=== Database Statistics ===" << endl;
        cout << "Total Students: " << studentDatabase.size() << endl;
        cout << "Average GPA: " << fixed << setprecision(2) << (totalGPA / studentDatabase.size()) << endl;
        cout << "GPA Range: " << fixed << setprecision(2) << minGPA << " - " << maxGPA << endl;
        cout << "Average Age: " << (totalAge / studentDatabase.size()) << endl;
        cout << "\nSemester Distribution:" << endl;
        for (const auto& stat : semesterStats) {
            cout << "  Semester " << stat.first << ": " << stat.second << " students" << endl;
        }
        cout << "\nCourse Enrollment:" << endl;
        for (const auto& stat : courseStats) {
            cout << "  " << stat.first << ": " << stat.second << " students" << endl;
        }
    }

    void displayMainMenu() {
        cout << "\n" << string(50, '=') << endl;
        cout << "    STUDENT MANAGEMENT SYSTEM" << endl;
        cout << string(50, '=') << endl;
        cout << "1.  Add New Student" << endl;
        cout << "2.  Update Student Record" << endl;
        cout << "3.  Delete Student Record" << endl;
        cout << "4.  View Student Record" << endl;
        cout << "5.  View All Records" << endl;
        cout << "6.  Search Records" << endl;
        cout << "7.  Database Statistics" << endl;
        cout << "8.  Database Status" << endl;
        cout << "0.  Exit System" << endl;
        cout << string(50, '=') << endl;
        cout << "Enter choice: ";
    }

    void run() {
        int choice;
        while (true) {
            displayMainMenu();
            while (!(cin >> choice) || choice < 0 || choice > 8) {
                clearInputBuffer();
                cout << "Invalid input. Enter a number (0-8): ";
            }
            clearInputBuffer();

            switch (choice) {
                case 1:
                    addStudentRecord();
                    break;
                case 2: {
                    int id;
                    cout << "Enter Student ID: ";
                    while (!(cin >> id)) {
                        clearInputBuffer();
                        cout << "Invalid ID. Enter a number: ";
                    }
                    clearInputBuffer();
                    updateStudentRecord(id);
                    break;
                }
                case 3: {
                    int id;
                    cout << "Enter Student ID: ";
                    while (!(cin >> id)) {
                        clearInputBuffer();
                        cout << "Invalid ID. Enter a number: ";
                    }
                    clearInputBuffer();
                    removeStudentRecord(id);
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter Student ID: ";
                    while (!(cin >> id)) {
                        clearInputBuffer();
                        cout << "Invalid ID. Enter a number: ";
                    }
                    clearInputBuffer();
                    viewStudentRecord(id);
                    break;
                }
                case 5:
                    displayAllRecords();
                    break;
                case 6:
                    searchRecords();
                    break;
                case 7:
                    showStatistics();
                    break;
                case 8:
                    cout << "\nDatabase Status:" << endl;
                    cout << "Total Records: " << studentDatabase.size() << "/" << MAX_CAPACITY << endl;
                    cout << "Data File: " << DATA_FILE << endl;
                    cout << "Status: Active" << endl;
                    break;
                case 0:
                    cout << "\nShutting down system. All data saved." << endl;
                    return;
                default:
                    cout << "Invalid selection. Please try again." << endl;
            }
        }
    }
};

int main() {
    StudentManagementSystem system;
    system.run();
    return 0;
}