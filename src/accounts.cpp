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

    password = hash_sha256(password);
    outFile << password << "\n";
    outFile << 1 << "\n";
    outFile.close();
    return true;
}

// Returns: 0 - Success, 1 - Error
bool loginUser(string username, string inputPassword, int& task) {
    ifstream inFile(getFileName(username));
    if (!inFile.is_open()) return false;

    string savedPassword;
    if (!getline(inFile, savedPassword)) {
        inFile.close();
        return false;
    }

    inputPassword = hash_sha256(password);
    if (inputPassword != savedPassword) {
        inFile.close();
        return false;
    }

    if (!(inFile >> task)) {
        task = 1;
    }

    inFile.close();
    return true;
}

// Returns: 0 - Success, 1 - Error
bool updateInfo(string username, string password, int task) {
    ofstream outFile(getFileName(username));
    if (!outFile.is_open()) return false;

    outFile << password << "\n";
    outFile << task << "\n";
    outFile.close();
    return true;
}