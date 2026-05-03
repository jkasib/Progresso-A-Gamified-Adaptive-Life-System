#ifndef USER_H
#define USER_H

#include "Task.h"
#include <vector>
#include <fstream>

class User {
private:
    string username;
    string password;
    int xp;
    int level;
    int streak;
    string rank;
    string lastActiveDate;
    bool completedToday;
    string previousRank;
    vector<Task> tasks;

public:
    bool levelUpFlag = false;
    bool rankUpFlag = false;
    User() {}

    User(string u, string p);

    bool checkPassword(string p);
    bool isTaskIdUnique(int id);

    void addTask(Task t);
    void showTasks();
    bool isTaskListEmpty();
    bool completeTask(int id);

    void updateXP(int points);
    void updateLevel();
    void updateRank();
    void updateDailyProgress();

    void save();
    void load();

    string getRank();
    int getLevel();
    void showStats();
    void reset();

    string getUsername();
};

#endif