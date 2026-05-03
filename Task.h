#ifndef TASK_H
#define TASK_H

#include <iostream>
using namespace std;

class Task {
private:
    int id;
    string title;
    int rating;
    bool completed;

public:
    Task() {}

    Task(int i, string t, int r) {
        id = i;
        title = t;
        rating = r;
        completed = false;
    }

    int calculatePoints() {
        return 10 * rating;
    }

    void markComplete() {
        completed = true;
    }

    bool isCompleted() {
        return completed;
    }

    int getId() {
        return id;
    }

    int getPoints() {
        return calculatePoints();
    }

    string getTitle() {
        return title;
    }

   

    int getRating() {
        return rating;
    }
};

#endif