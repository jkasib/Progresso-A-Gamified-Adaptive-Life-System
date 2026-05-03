#include <iostream>
#include "Auth.h"
using namespace std;

// TEMPLATE (requirement)
template <typename T>
void printVector(vector<T> v) {
    for (auto &x : v) cout << x << endl;
}

// POLYMORPHISM
class Reward {
public:
    virtual int bonus(int xp) = 0;
};

class RankBonus : public Reward {
public:
    int bonus(int xp) {
        return xp + 50;
    }
};


void wait() {
    cout << "\nPress Enter to get back to main menu...";
    cin.ignore();
    cin.get();
}


void clearScreen() {
    system("cls"); // Windows
    // system("clear"); // Linux/Mac
}

void showHeader(string username = "", string rank = "", int level=0) {
    cout << "\n";
    cout << "========================================================================================================================\n";
    
    cout << "\n";
    cout << "                                                    PROGRESSO \n\n";
    cout << "========================================================================================================================\n";

    if (username != "") {
        cout << "\n------------------------------------------------------\n";
        cout << "User: " << username << " | Rank: " << rank << " | Level: "<<level<< "\n";
        cout << "------------------------------------------------------\n";
    }

    cout << endl;
}




int main() {
    int choice;

    while (true) {
        clearScreen();
        showHeader();

        cout << "1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string u, p, cp;

            while (true) {

                cout << "Enter username: ";
                cin >> u;

                if (isUsernameTaken(u)) {
                    cout << "Username already exists! Try again.\n\n";
                    continue;
                }

                // PASSWORD INPUT
                cout << "Enter password: ";
                p = getHiddenPassword();

                // CONFIRM PASSWORD INPUT
                cout << "Confirm password: ";
                cp = getHiddenPassword();

                if (p != cp) {
                    cout << "Passwords do not match! Try again.\n\n";
                    continue; // restart registration loop
                }

                break; // everything OK
            }

            registerUser(u, p);

            // cout << "\nRegistration successful!\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();

        }

        else if (choice == 2) {
                string u, p;
                User user;

                while (true) {

                    cout << "Enter username: ";
                    cin >> u;

                    cout << "Enter password: ";
                    p = getHiddenPassword();

                    user = loginUser(u, p);

                    // CHECK SUCCESS
                    if (user.getUsername() != "") {
                        cout << "\nLogin successful!\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break; // exit login loop
                    }

                    // ❌ FAILED LOGIN
                    cout << "\nLogin failed! Try again.\n\n";
                }


            int ch;
            while (true) {
                clearScreen();
                showHeader(user.getUsername(), user.getRank(), user.getLevel());

                cout << "1. Add Task\n";
                cout << "2. Show Tasks\n";
                cout << "3. Complete Task\n";
                cout << "4. Stats\n";
                cout << "5. Reset\n";
                cout << "6. Logout\n";
                cout << "Choice: ";
                cin >> ch;

                if (ch == 1) {
                    int id, r;
                    string title;
                    while (true) {
                        cout << "Enter Task ID: ";
                        cin >> id;

                        if (user.isTaskIdUnique(id)) break;

                        cout << "ID already exists! Enter a different ID.\n";
                    }
                    cout<<"Name of the task: ";
                    cin>>title;
                    cout<<"Rate the task out of 10: ";
                    cin>>r;

                    user.addTask(Task(id, title, r));
                }

                else if (ch == 2) {
                    cout << "\n===== TASK LIST =====\n";
                    user.showTasks();
                    wait();
                }

                else if (ch == 3) {
                    cout << "\n===== AVAILABLE TASKS =====\n";
                    user.showTasks();

                    if (user.isTaskListEmpty()) {
                        cout << "No tasks available!\n";
                        cin.ignore();
                        cin.get();
                        continue;
                    }

                    int id;

                    cout << "\nEnter the ID of the completed task: ";
                    cin >> id;

                    bool found = user.completeTask(id);

                    if (found) {
                        cout << "\nTask " << id << " is completed!\n";
                    } else {
                        cout << "\nInvalid Task ID!\n";
                    }

                    cout << "\nPress Enter to return to main menu...";
                    cin.ignore();
                    cin.get();

                    // LEVEL UP MESSAGE CHECK (STEP 4C)
                    if (user.levelUpFlag) {
                        cout << "LEVEL UP! Upgraded to Level " << user.getLevel() << endl;
                        user.levelUpFlag = false;
                        wait();
                    }
                    else {
                        wait();
                    }
                }

                else if (ch == 4) {
                    user.showStats();
                    wait();
                }

                else if (ch == 5) {
                    user.reset();
                }

                else if (ch == 6) {
                    user.save();
                    break;
                }
            }
        }

        else break;
    }
}