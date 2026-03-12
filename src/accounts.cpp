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

// 0 - Success, 1 - Error
bool registerUser(string username, string password) {
    if (userExists(username)) return false;

    ofstream outFile(getFileName(username));
    if (!outFile.is_open()) return false;

    // TODO: pass hash
    outFile << password << "\n";
    outFile << 1 << "\n";
    outFile.close();
    return true;
}