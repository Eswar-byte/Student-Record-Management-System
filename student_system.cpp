#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    float marks;

public:
    Student(int r, string n, float m) : rollNo(r), name(n), marks(m) {}

    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    float getMarks() const { return marks; }

    void update(string newName, float newMarks) {
        name = newName;
        marks = newMarks;
    }

    void display() const {
        cout << "Roll No: " << rollNo << ", Name: " << name << ", Marks: " << marks << endl;
    }
};

class StudentSystem {
private:
    vector<Student> students;

    Student* findStudent(int rollNo) {
        for (auto& student : students) {
            if (student.getRollNo() == rollNo)
                return &student;
        }
        return nullptr;
    }

public:
    void addStudent() {
        int rollNo;
        string name;
        float marks;
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
        students.emplace_back(rollNo, name, marks);
        cout << "Student added!\n";
    }

    void viewStudents() {
        if (students.empty()) {
            cout << "No students found.\n";
            return;
        }
        for (const auto& student : students)
            student.display();
    }

    void updateStudent() {
        int rollNo;
        cout << "Enter Roll No to update: ";
        cin >> rollNo;
        Student* student = findStudent(rollNo);
        if (!student) {
            cout << "Student not found.\n";
            return;
        }
        string newName;
        float newMarks;
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, newName);
        cout << "Enter New Marks: ";
        cin >> newMarks;
        student->update(newName, newMarks);
        cout << "Student updated.\n";
    }

    void deleteStudent() {
        int rollNo;
        cout << "Enter Roll No to delete: ";
        cin >> rollNo;
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getRollNo() == rollNo) {
                students.erase(it);
                cout << "Student deleted.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void showStats() {
        if (students.empty()) {
            cout << "No data available.\n";
            return;
        }

        float total = 0;
        float maxMarks = -1;
        string topStudent;

        for (const auto& student : students) {
            total += student.getMarks();
            if (student.getMarks() > maxMarks) {
                maxMarks = student.getMarks();
                topStudent = student.getName();
            }
        }

        cout << "Total Students: " << students.size() << endl;
        cout << "Average Marks: " << total / students.size() << endl;
        cout << "Top Scorer: " << topStudent << " (" << maxMarks << " marks)\n";
    }

    void menu() {
        while (true) {
            cout << "\n--- Student Record System ---\n";
            cout << "1. Add Student\n2. View Students\n3. Update Student\n4. Delete Student\n5. View Stats\n6. Exit\n";
            cout << "Choose option: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: addStudent(); break;
                case 2: viewStudents(); break;
                case 3: updateStudent(); break;
                case 4: deleteStudent(); break;
                case 5: showStats(); break;
                case 6: cout << "Exiting...\n"; return;
                default: cout << "Invalid option!\n";
            }
        }
    }
};

int main() {
    StudentSystem system;
    system.menu();
    return 0;
}
