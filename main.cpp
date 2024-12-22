#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    int age;
    string grade;
    string contact;

public:
    // Function to input student details
    void inputDetails() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore(); // Clear newline character in input buffer
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Grade: ";
        getline(cin, grade);
        cout << "Enter Contact: ";
        getline(cin, contact);
    }

    // Function to display student details
    void displayDetails() const {
        cout << setw(10) << rollNumber
             << setw(20) << name
             << setw(10) << age
             << setw(10) << grade
             << setw(15) << contact << endl;
    }

    // Getters
    int getRollNumber() const { return rollNumber; }

    // Save student record to a file
    void saveToFile(fstream &file) const {
        file << rollNumber << "\n"
             << name << "\n"
             << age << "\n"
             << grade << "\n"
             << contact << "\n";
    }

    // Load student record from a file
    void loadFromFile(fstream &file) {
        file >> rollNumber;
        file.ignore();
        getline(file, name);
        file >> age;
        file.ignore();
        getline(file, grade);
        getline(file, contact);
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\n=== Student Record Management System ===\n";
    cout << "1. Add New Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Roll Number\n";
    cout << "4. Update Student Record\n";
    cout << "5. Delete Student Record\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

// Function to update a student's record
void updateStudentRecord() {
    int rollToUpdate;
    cout << "Enter Roll Number to Update: ";
    cin >> rollToUpdate;

    fstream inFile("students.txt", ios::in);
    fstream tempFile("temp.txt", ios::out);

    if (!inFile || !tempFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    bool found = false;

    while (!inFile.eof()) {
        student.loadFromFile(inFile);
        if (inFile.eof()) break;

        if (student.getRollNumber() == rollToUpdate) {
            cout << "Enter new details for the student:\n";
            student.inputDetails();
            found = true;
        }
        student.saveToFile(tempFile);
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Record updated successfully.\n";
    } else {
        remove("temp.txt");
        cout << "No student found with Roll Number " << rollToUpdate << endl;
    }
}

// Function to delete a student's record
void deleteStudentRecord() {
    int rollToDelete;
    cout << "Enter Roll Number to Delete: ";
    cin >> rollToDelete;

    fstream inFile("students.txt", ios::in);
    fstream tempFile("temp.txt", ios::out);

    if (!inFile || !tempFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    bool found = false;

    while (!inFile.eof()) {
        student.loadFromFile(inFile);
        if (inFile.eof()) break;

        if (student.getRollNumber() == rollToDelete) {
            found = true;
            continue; // Skip saving this record to the temp file
        }
        student.saveToFile(tempFile);
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Record deleted successfully.\n";
    } else {
        remove("temp.txt");
        cout << "No student found with Roll Number " << rollToDelete << endl;
    }
}

// Main function
int main() {
    int choice;
    Student student;
    fstream file;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add new student
            file.open("students.txt", ios::out | ios::app); // Open file in append mode
            if (!file) {
                cerr << "Error opening file!" << endl;
                break;
            }
            student.inputDetails();
            student.saveToFile(file);
            file.close();
            cout << "Student added successfully.\n";
            break;
        }
        case 2: {
            // Display all students
            file.open("students.txt", ios::in); // Open file in read mode
            if (!file) {
                cerr << "Error opening file or no records found!" << endl;
                break;
            }
            cout << setw(10) << "Roll No"
                 << setw(20) << "Name"
                 << setw(10) << "Age"
                 << setw(10) << "Grade"
                 << setw(15) << "Contact" << endl;
            cout << string(65, '-') << endl;

            while (!file.eof()) {
                student.loadFromFile(file);
                if (file.eof()) break; // Avoid printing last empty line
                student.displayDetails();
            }
            file.close();
            break;
        }
        case 3: {
            // Search for a student
            int rollToSearch;
            cout << "Enter Roll Number to Search: ";
            cin >> rollToSearch;

            file.open("students.txt", ios::in);
            if (!file) {
                cerr << "Error opening file or no records found!" << endl;
                break;
            }
            bool found = false;
            while (!file.eof()) {
                student.loadFromFile(file);
                if (file.eof()) break;
                if (student.getRollNumber() == rollToSearch) {
                    cout << "Student Found:\n";
                    student.displayDetails();
                    found = true;
                    break;
                }
            }
            file.close();
            if (!found)
                cout << "No student found with Roll Number " << rollToSearch << endl;
            break;
        }
        case 4:
            // Update a student's record
            updateStudentRecord();
            break;

        case 5:
            // Delete a student's record
            deleteStudentRecord();
            break;

        case 6:
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
