#ifndef AUTH_H
#define AUTH_H

#include "User.h"

bool registerUser(string username, string password);
User loginUser(string username, string password);
bool isUsernameTaken(string username);

#endif