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

string User::getRank() {
    return rank;
}

int User::getLevel(){
    return level;
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
    if (tasks.empty()) {
        cout << "\nNo task added...\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";
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
    updateDailyProgress();

    for (auto it = tasks.begin(); it != tasks.end(); ) {
        if (it->getId() == id && !it->isCompleted()) {

            int pts = it->getPoints();

            it->markComplete();

            updateXP(pts);
            completedToday = true;

            cout << "Task completed! +" << pts << " XP\n";

            // REMOVE TASK FROM LIST
            it = tasks.erase(it);

            save();
            return;
        }
        else {
            ++it;
        }
    }

    cout << "Task not found!\n";
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
        levelUpFlag = true;
    }
}

void User::updateRank() {
    string newRank;

    if (streak >= 365) newRank = "Conqueror";
    else if (streak >= 180) newRank = "Commander";
    else if (streak >= 90) newRank = "Knight";
    else if (streak >= 60) newRank = "Elite";
    else if (streak >= 30) newRank = "Warrior";
    else if (streak >= 15) newRank = "Soldier";
    else if (streak >= 7) newRank = "Cadet";
    else newRank = "Recruit";

    // CHECK IF RANK CHANGED
    if (newRank != rank) {
        previousRank = rank;
        rank = newRank;
        rankUpFlag = true;
    }
}

void User::save() {
    try {
        ofstream file(username + ".txt");

        if (!file.is_open()) {
            cout << "Error opening file for saving\n";
            return;
        }

        file << xp << " " << level << " " << streak << " " << rank << endl;
        file << lastActiveDate << " " << completedToday << endl;

        // ALWAYS WRITE TASK COUNT (even if 0)
        file << tasks.size() << endl;

        for (auto &t : tasks) {
            file << t.getId() << " "
                 << t.getTitle() << " "
                 << t.getRating() << " "
                 << t.isCompleted() << endl;
        }

        file.close();
    }
    catch (...) {
        cout << "Error saving file\n";
    }
}

void User::load() {
    try {
        ifstream file(username + ".txt");

        if (!file.is_open()) {
            cout << "No previous data found\n";
            return;
        }

        tasks.clear();

        file >> xp >> level >> streak >> rank;
        file >> lastActiveDate >> completedToday;

        int taskCount = 0;

        // 🔥 SAFE READ
        if (!(file >> taskCount)) {
            taskCount = 0;
        }

        for (int i = 0; i < taskCount; i++) {
            int id, d, r, completed;
            string title;

            if (!(file >> id >> title >> d >> r >> completed)) {
                break; // prevents garbage values
            }

            Task t(id, title, r);
            if (completed) t.markComplete();

            tasks.push_back(t);
        }

        file.close();
    }
    catch (...) {
        cout << "Error loading file\n";
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

    lastActiveDate = "";
    completedToday = false;

    tasks.clear();

    save();
}

string User::getUsername() {
    return username;
}