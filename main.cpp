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

int main() {
    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string u, p;
            cout<<"Username: ";
            cin>>u;
            cout<<"Enter Password: ";
            cin>>p;
            registerUser(u, p);
        }

        else if (choice == 2) {
            string u, p;
            cout<<"Username: ";
            cin>>u;
            cout<<"Enter Password: ";
            cin>>p;

            User user = loginUser(u, p);

            if (user.getUsername() == "") {
                cout << "Login failed!\n";
                continue;
            }

            int ch;
            while (true) {
                cout << "\n1.Add Task\n2.Show Tasks\n3.Complete Task\n4.Stats\n5.Reset\n6.Logout\nChoice: ";
                cin >> ch;

                if (ch == 1) {
                    int id, d, r;
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
                    user.showTasks();
                }

                else if (ch == 3) {
                    int id;
                    cin >> id;
                    user.completeTask(id);
                }

                else if (ch == 4) {
                    user.showStats();
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