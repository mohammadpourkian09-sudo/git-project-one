#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int studentID;
    int units;
    double GPA;
    int securityCode;
    Student* next;
};

Student* createStudent(string name, int id, int units, double gpa, int securityCode) {
    Student* newStudent = new Student;
    newStudent->name = name;
    newStudent->studentID = id;
    newStudent->units = units;
    newStudent->GPA = gpa;
    newStudent->securityCode = securityCode;
    newStudent->next = nullptr;
    return newStudent;
}

void addStudent(Student*& head, string name, int id, int units, double gpa, int securityCode) {
    Student* newStudent = createStudent(name, id, units, gpa, securityCode);
    if (head == nullptr) {
        head = newStudent;
        cout << "New student record added (first in the list)\n";
        return;
    }
    Student* current = head;
    while (current->next != nullptr)
        current = current->next;
    current->next = newStudent;
    cout << "New student record added at the end of the list.\n";
}

bool deleteStudent(Student*& head, int id) {
    if (head == nullptr) return false;
    if (head->studentID == id) {
        Student* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    Student* current = head;
    while (current->next != nullptr && current->next->studentID != id)
        current = current->next;
    if (current->next == nullptr)
        return false;
    Student* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;
    return true;
}

Student* searchStudent(Student* head, int id) {
    Student* current = head;
    while (current != nullptr) {
        if (current->studentID == id)
            return current;
        current = current->next;
    }
    return nullptr;
}

bool updateStudent(Student* head, int id, int newUnits, double newGPA) {
    Student* s = searchStudent(head, id);
    if (s == nullptr) return false;
    s->units = newUnits;
    s->GPA = newGPA;
    return true;
}

void displayAll(Student* head) {
    if (head == nullptr) {
        cout << "The student record list is empty.\n";
        return;
    }
    Student* current = head;
    cout << "\n📋 Student Record List:\n";
    while (current != nullptr) {
        cout << "------------------------------\n";
        cout << "Name: " << current->name << endl;
        cout << "Student ID: " << current->studentID << endl;
        cout << "Units: " << current->units << endl;
        cout << "GPA: " << current->GPA << endl;
        cout << "Security Code: " << current->securityCode << endl;
        current = current->next;
    }
    cout << "------------------------------\n";
}

void freeMemory(Student*& head) {
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Student* head = nullptr;
    int choice;
    do {
        cout << "\n========== Student Record Management System ==========\n";
        cout << "1. Add new record\n";
        cout << "2. Delete record\n";
        cout << "3. Search student\n";
        cout << "4. Update grades\n";
        cout << "5. Display all records\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int id, units, code;
            double gpa;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter student ID: ";
            cin >> id;
            cout << "Enter total units: ";
            cin >> units;
            cout << "Enter GPA: ";
            cin >> gpa;
            cout << "Enter 4-digit security code: ";
            cin >> code;
            addStudent(head, name, id, units, gpa, code);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter student ID to delete: ";
            cin >> id;
            if (deleteStudent(head, id))
                cout << "Record deleted successfully.\n";
            else
                cout << "Record not found.\n";
        }
        else if (choice == 3) {
            int id;
            cout << "Enter student ID to search: ";
            cin >> id;
            Student* s = searchStudent(head, id);
            if (s != nullptr) {
                cout << "\nSearch Result:\n";
                cout << "Name: " << s->name << endl;
                cout << "Student ID: " << s->studentID << endl;
                cout << "Units: " << s->units << endl;
                cout << "GPA: " << s->GPA << endl;
                cout << "Security Code: " << s->securityCode << endl;
            } else {
                cout << "Record not found.\n";
            }
        }
        else if (choice == 4) {
            int id, units;
            double gpa;
            cout << "Enter student ID to update: ";
            cin >> id;
            cout << "Enter new units: ";
            cin >> units;
            cout << "Enter new GPA: ";
            cin >> gpa;
            if (updateStudent(head, id, units, gpa))
                cout << "Record updated successfully.\n";
            else
                cout << "Record not found.\n";
        }
        else if (choice == 5) {
            displayAll(head);
        }

    } while (choice != 0);

    freeMemory(head);
    cout << "Exiting the program...\n";
    return 0;
}
