#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// Structure to hold course details
struct Course {
    string courseName;
    char grade;
    float credits;
};

// Function to convert grade to points
float getGradePoints(char g) {
    g = toupper(g);
    if(g == 'A') return 4.0;
    else if(g == 'B') return 3.0;
    else if(g == 'C') return 2.0;
    else if(g == 'D') return 1.0;
    else if(g == 'F') return 0.0;
    else return -1;   // Invalid grade
}

int main() {
    vector<Course> courses;
    int numberOfCourses;
    float totalGradePoints = 0.0;
    float totalCredits = 0.0;

    cout << "========== Welcome to CGPA Calculator ==========\n\n";
    cout << "How many courses did you take this semester? ";
    cin >> numberOfCourses;

    for(int i = 0; i < numberOfCourses; i++) {
        Course c;
        cout << "\n--- Course " << (i+1) << " ---\n";
        
        cout << "Enter Course Name: ";
        cin.ignore();                    // To handle newline after cin
        getline(cin, c.courseName);
        
        cout << "Enter Grade (A/B/C/D/F): ";
        cin >> c.grade;
        
        cout << "Enter Credit Hours: ";
        cin >> c.credits;

        float points = getGradePoints(c.grade);
        
        if(points == -1) {
            cout << "Invalid grade! Please try again.\n";
            i--;        // Ask same course again
            continue;
        }

        courses.push_back(c);
        totalGradePoints += points * c.credits;
        totalCredits += c.credits;
    }

    float gpa = (totalCredits > 0) ? totalGradePoints / totalCredits : 0.0;

    // Final Output
    cout << "\n==========================================\n";
    cout << "               YOUR RESULT\n";
    cout << "==========================================\n";
    
    for(auto &c : courses) {
        cout << left << setw(35) << c.courseName 
             << "Grade: " << c.grade 
             << "   Credits: " << c.credits << endl;
    }
    
    cout << "------------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Total Credits     : " << totalCredits << endl;
    cout << "Your Semester GPA : " << gpa << endl;
    cout << "==========================================\n";

    return 0;
}