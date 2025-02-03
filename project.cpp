#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <algorithm> 
using namespace std;
struct Course {
    char CourseName[50];
    int Units;
    float Grade;
};
struct Student {
    int StID;
    char Name[50];
    char Major[50];  
    float Avg;
    vector<Course> Courses;
};
float calculateGPA(const Student& student) {
    float totalPoints = 0;
    int totalUnits = 0;

    for (const auto& course : student.Courses) {
        totalPoints += course.Grade * course.Units;
        totalUnits += course.Units;
    }

    return (totalUnits > 0) ? totalPoints / totalUnits : 0.0;
}
char Menu() {
    char ch;
    cout <<"\033[33m"<< "\nStudent's Database"<<"\033[0m"<<endl;
    cout << "------------------\n";
    cout <<"\033[1;32m"<< "\t 1) Enter New Student"<<"\033[0m"<<endl;
    cout << "\t 2) Add Courses for Student\n";
    cout <<"\033[1;34m"<< "\t 3) Show Transcript"<<"\033[0m"<<endl;
    cout << "\t 4) List Students by Major\n";
    cout << "\033[1;32m"<< "\t 5) List Students by GPA (Descending)"<<"\033[0m"<<endl;
    cout << "\t 6) List Students by Name (Alphabetical)\n";
    cout <<"\033[1;34m"<< "\t 7) List Students by Student ID (Ascending)"<<"\033[0m"<<endl;
    cout << "\t 8) Exit\n";
    cout << "\033[1;95m"<< "\t Select: "<<"\033[0m";
    cin >> ch;
    return ch;
}
void stdinput(vector<Student>& students) {
    Student temp;
    cout << "\nEnter New Student's Information:\n";
    cout << "--------------------------------\n";
    
    cout << "Name: ";
    cin.ignore();
    cin.getline(temp.Name, 50);
    
    cout << "Major: ";
    cin.getline(temp.Major, 50);
    
    cout << "ID: ";
    cin >> temp.StID;
    temp.Avg = 0.0;

    students.push_back(temp);
    cout << "\nNew student added!\n";
}
void stdAddCourses(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available. Please add a student first.\n";
        return;
    }
    int id;
    cout << "\nEnter Student ID: ";
    cin >> id;

    for (auto& student : students) {
        if (student.StID == id) {
            int numCourses;
            cout << "\nHow many courses do you want to add for " << student.Name << "? ";
            cin >> numCourses;

            for (int i = 0; i < numCourses; i++) {
                Course tempCourse;
                cout << "\nEnter Course Name: ";
                cin.ignore();
                cin.getline(tempCourse.CourseName, 50);
                cout << "Enter Number of Units: ";
                cin >> tempCourse.Units;
                cout << "Enter Grade: ";
                cin >> tempCourse.Grade;

                student.Courses.push_back(tempCourse);
            }

            student.Avg = calculateGPA(student);
            cout << "\nCourses added successfully!\n";
            return;
        }
    }

    cout << "Student not found.\n";
}
void showTranscript(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    int id;
    cout << "\nEnter Student ID to Show Transcript: ";
    cin >> id;

    for (const auto& student : students) {
        if (student.StID == id) {
            cout << "\nTranscript for " << student.Name << " (ID: " << student.StID << ", Major: " << student.Major << ")\n";
            cout <<"\033[1;32m"<< "--------------------------------------------------"<<"\033[0m"<<endl;
            cout << setw(20) << left << "Course Name" 
                 << setw(10) << "Units" 
                 << setw(10) << "Grade" << "\n";
            cout <<"\033[1;32m"<< "--------------------------------------------------"<<"\033[0m"<<endl;

            for (const auto& course : student.Courses) {
                cout << setw(20) << left << course.CourseName
                     << setw(10) << course.Units
                     << setw(10) << course.Grade << "\n";
            }
            cout <<"\033[1;32m"<< "--------------------------------------------------"<<"\033[0m"<<endl;
            cout << "Overall GPA: " << fixed << setprecision(2) << student.Avg << "\n";
            return;
        }
    }

    cout << "Student not found.\n";
}
void listStudentsByMajor(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }
    char major[50];
    cout << "\nEnter Major to List Students: ";
    cin.ignore();
    cin.getline(major, 50);
    cout << "\nStudents in " << major << ":\n";
    cout <<"\033[1;34m"<< "------------------------------------------"<<"\033[0m"<<endl;
    cout << setw(10) << left << "ID" 
         << setw(20) << "Name" 
         << setw(10) << "GPA" << "\n";
    cout <<"\033[1;34m"<< "------------------------------------------"<<"\033[0m"<<endl;
    bool found = false;
    for (const auto& student : students) {
        if (strcmp(student.Major, major) == 0) {
            cout << setw(10) << left << student.StID
                 << setw(20) << student.Name
                 << setw(10) << fixed << setprecision(2) << student.Avg << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No students found in this major.\n";
    }
}
void listStudentsByGPA(vector<Student> students) {
    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.Avg > b.Avg;
    });

    cout << "\nStudents Sorted by GPA (Descending):\n";
    cout <<"\033[1;95m"<< "------------------------------------------"<<"\033[0m"<<endl;
    cout << setw(10) << left << "ID" 
         << setw(20) << "Name" 
         << setw(20) << "Major"
         << setw(10) << "GPA" << "\n";
    cout <<"\033[1;95m"<< "------------------------------------------"<<"\033[0m"<<endl;

    for (const auto& student : students) {
        cout << setw(10) << left << student.StID
             << setw(20) << student.Name
             << setw(20) << student.Major
             << setw(10) << fixed << setprecision(2) << student.Avg << "\n";
    }
}
void listStudentsByName(vector<Student> students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return strcmp(a.Name, b.Name) < 0;
    });
    cout << "\nStudents Sorted by Name:\n";
    for (const auto& student : students) {
        cout << student.Name << " (ID: " << student.StID << ")\n";
    }
}
void listStudentsByID(vector<Student> students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.StID < b.StID;
    });

    cout << "\nStudents Sorted by Student ID:\n";
    for (const auto& student : students) {
        cout << student.StID << " - " << student.Name << "\n";
    }
}
int main() {
    vector<Student> students;
    char key;
    while ((key = Menu()) != '8') {
        switch (key) {
            case '1': stdinput(students); break;
            case '2': stdAddCourses(students); break;
            case '3': showTranscript(students); break;
            case '4': listStudentsByMajor(students); break;
            case '5': listStudentsByGPA(students); break;
            case '6': listStudentsByName(students); break;
            case '7': listStudentsByID(students); break;
        }
    }
    cout << "Exiting program...\n";
    return 0;
}