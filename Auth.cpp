#include "Auth.h"
#include <fstream>
#include <conio.h>

bool registerUser(string username, string password) {
    try {
     

        ofstream file("users.txt", ios::app);

        if (!file.is_open()) {
            cout << "Error opening file\n";
            return false;
        }

        file << username << " " << password << endl;

        file.close();

        cout << "\nRegistration successful!\n";
        return true;
    }
    catch (...) {
        cout << "Error registering user\n";
        return false;
    }
}

User loginUser(string username, string password) {
    try {
        ifstream file("users.txt");

        if (!file.is_open()) {
            cout << "Error opening file\n";
            return User();
        }

        string u, p;

        while (file >> u >> p) {
            if (u == username) {
                if (p == password) {
                    User user(u, p);
                    user.load();
                    return user;
                }
                else {
                    cout << "\nWrong password!\n";
                    return User(); // invalid login
                }
            }
        }

        cout << "User not found!\n";
        return User();
    }
    catch (...) {
        cout << "Login error\n";
        return User();
    }
}


// Unique username
bool isUsernameTaken(string username) {
    try {
        ifstream file("users.txt");

        if (!file.is_open()) return false;

        string u, p;

        while (file >> u >> p) {
            if (u == username) {
                return true;
            }
        }

        file.close();
    }
    catch (...) {
        cout << "Error checking username\n";
    }

    return false;
}




string getHiddenPassword() {
    string password = "";
    char ch;

    

    while (true) {
        ch = _getch();

        if (ch == 13) { // Enter key
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << "*";
        }
    }

    cout << endl;
    return password;
}