#include "User.h"
#include <ctime>

User::User(string u, string p) {
    username = u;
    password = p;
    xp = 0;
    level = 1;
    streak = 0;
    rank = "Recruit";
}

// for streak


string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return to_string(1900 + ltm->tm_year) + "-" +
           to_string(1 + ltm->tm_mon) + "-" +
           to_string(ltm->tm_mday);
}

void User::updateDailyProgress() {
    string today = getCurrentDate();

    if (lastActiveDate == "") {
        // First time ever
        lastActiveDate = today;
        completedToday = false;
        return;
    }

    if (today != lastActiveDate) {
        // Day has changed

        if (completedToday) {
            streak++;  // ✅ increase streak
        } else {
            streak = 0; // ❌ missed day → reset
        }

        completedToday = false; // reset for new day
        lastActiveDate = today;

        updateRank();
    }
}

bool User::checkPassword(string p) {
    return password == p;
}

bool User::isTaskIdUnique(int id) {
    for (auto &t : tasks) {
        if (t.getId() == id) {
            return false;
        }
    }
    return true;
}

void User::addTask(Task t) {
    if (!isTaskIdUnique(t.getId())) {
        cout<<"\n---------------------------------------------\n";
        cout << "Error: Task ID already exists. Try again.\n";
        cout<<"---------------------------------------------\n";
        return;
    }
    tasks.push_back(t);
    save();
}

void User::showTasks() {
    for (auto &t : tasks) {
        cout<<".........................................\n";
        cout << "ID: " << t.getId()<<endl
             << "Task: " << t.getTitle()<<endl
             << "Points: " << t.getPoints()<<endl
             << "Status: " << (t.isCompleted() ? "Done" : "Pending")
             << endl;
            cout<<".........................................\n";
    }
}

void User::completeTask(int id) {
    updateDailyProgress(); // check day first

    for (auto &t : tasks) {
        if (t.getId() == id && !t.isCompleted()) {
            t.markComplete();

            int pts = t.getPoints();
            updateXP(pts);

            completedToday = true; // ✅ mark today done

            save();

            cout << "Task completed! +" << pts << " XP\n";
            return;
        }
    }
}

void User::updateXP(int points) {
    xp += points;
    updateLevel();
}

void User::updateLevel() {
    int required = 100 + level * 20;
    if (xp >= required) {
        xp -= required;
        level++;
        cout << "Level Up! Now Level " << level << endl;
    }
}

void User::updateRank() {
    if (streak >= 365) rank = "Conqueror";
    else if (streak >= 180) rank = "Commander";
    else if (streak >= 90) rank = "Knight";
    else if (streak >= 60) rank = "Elite";
    else if (streak >= 30) rank = "Warrior";
    else if (streak >= 15) rank = "Soldier";
    else if (streak >= 7) rank = "Cadet";
    else rank = "Recruit";
}

void User::save() {
    ofstream file(username + ".txt");

    file << xp << " " << level << " " << streak << " " << rank << endl;
    file << lastActiveDate << " " << completedToday << endl;
    file << tasks.size() << endl; // VERY IMPORTANT

    for (auto &t : tasks) {
        file << t.getId() << " "
             << t.getTitle() << " "
             << t.getRating() << " "
             << t.isCompleted() << endl;
    }
}

void User::load() {
    ifstream file(username + ".txt");
    if (!file) return;

    tasks.clear();

    int taskCount;
    file >> xp >> level >> streak >> rank;
    file >> lastActiveDate >> completedToday;
    file >> taskCount;

    for (int i = 0; i < taskCount; i++) {
        int id, r, completed;
        string title;

        file >> id >> title >> r >> completed;

        Task t(id, title, r);
        if (completed) t.markComplete();

        tasks.push_back(t);
    }
}

void User::showStats() {
    cout << "\nXP: " << xp
         << " | Level: " << level
         << " | Streak: " << streak
         << " | Rank: " << rank << endl;
}

void User::reset() {
    xp = 0;
    level = 1;
    streak = 0;
    rank = "Recruit";
    tasks.clear();

    save();
}

string User::getUsername() {
    return username;
}