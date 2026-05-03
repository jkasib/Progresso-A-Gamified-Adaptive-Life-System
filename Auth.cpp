#include "Auth.h"
#include <fstream>

bool registerUser(string username, string password) {
    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    return true;
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