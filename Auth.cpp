#include "Auth.h"
#include <fstream>

bool registerUser(string username, string password) {
    try {
     

        ofstream file("users.txt", ios::app);

        if (!file.is_open()) {
            cout << "Error opening file\n";
            return false;
        }

        file << username << " " << password << endl;

        file.close();

        cout << "Registration successful!\n";
        return true;
    }
    catch (...) {
        cout << "Error registering user\n";
        return false;
    }
}

User loginUser(string username, string password) {
    ifstream file("users.txt");
    string u, p;

    while (file >> u >> p) {
        if (u == username && p == password) {
            User user(u, p);
            user.load();
            return user;
        }
    }
    cout<<"\n-------------------------------------\n";
    cout << "Invalid login. Try Again.....\n";
    cout<<"-------------------------------------\n";
    return User();
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