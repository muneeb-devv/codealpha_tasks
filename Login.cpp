#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to register new user
void registerUser() {
    string username, password;
    
    cout << "\n===== Registration =====\n";
    cout << "Create Username: ";
    cin >> username;
    cout << "Create Password: ";
    cin >> password;

    // Check if username already exists
    ifstream checkFile("users.txt");
    string line;
    while(getline(checkFile, line)) {
        if(line.find(username + "|") == 0) {
            cout << "Sorry! Username already taken.\n";
            return;
        }
    }
    checkFile.close();

    // Save new user
    ofstream file("users.txt", ios::app);
    file << username << "|" << password << endl;
    file.close();

    cout << "Registration Successful! You can now login.\n";
}

// Function to login
bool loginUser() {
    string username, password;
    
    cout << "\n===== Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("users.txt");
    string line;
    
    while(getline(file, line)) {
        int pos = line.find('|');
        string storedUser = line.substr(0, pos);
        string storedPass = line.substr(pos + 1);

        if(storedUser == username && storedPass == password) {
            cout << "Login Successful! Welcome " << username << " :)\n";
            return true;
        }
    }
    
    cout << "Invalid Username or Password!\n";
    return false;
}

int main() {
    int choice;
    
    cout << "=== Login & Registration System ===\n";

    while(true) {
        cout << "\n1. Register New Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1) 
            registerUser();
        else if(choice == 2) 
            loginUser();
        else if(choice == 3) {
            cout << "Thank you! Goodbye.\n";
            break;
        }
        else 
            cout << "Invalid option. Try again.\n";
    }
    return 0;
}