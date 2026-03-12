#include <iostream>
#include <string>
#include <fstream>

#include "../include/accounts.h"

using namespace std;

// Returns the filename
string getFileName(string username) {
    return "accounts/" + username + ".txt";
}

// Checks if a user file exists
bool userExists(string username) {
    ifstream f(getFileName(username));
    return f.good();
}