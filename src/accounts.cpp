#include <iostream>
#include <string>
#include <fstream>
#include "../include/accounts.h"
#include "../include/sha256.h"

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

// Returns: 0 - Success, 1 - Error
bool registerUser(string username, string password) {
    if (userExists(username)) return 1;

    ofstream outFile(getFileName(username));
    if (!outFile.is_open()) return 1;

    password = hash_sha256(password.c_str());
    outFile << password << "\n";
    outFile << 1 << "\n";
    outFile << 0 << "\n";
    outFile.close();
    return 0;
}

// Returns: 0 - Success, 1 - Error
bool loginUser(string username, string inputPassword, int& task, int& avg) {
    ifstream inFile(getFileName(username));
    if (!inFile.is_open()) return 1;

    string savedPassword;
    if (!getline(inFile, savedPassword)) {
        inFile.close();
        return 1;
    }

    inputPassword = hash_sha256(inputPassword.c_str());
    if (inputPassword != savedPassword) {
        inFile.close();
        return 1;
    }

    if (!(inFile >> task)) task = 1;
    if (!(inFile >> avg)) avg = 0;

    inFile.close();
    return 0;
}

// Returns: 0 - Success, 1 - Error
bool updateInfo(string username, string password, int task, int avg) {
    ofstream outFile(getFileName(username));
    if (!outFile.is_open()) return 1;

    outFile << password << "\n";
    outFile << task << "\n";
    outFile << avg << "\n";
    outFile.close();
    return 0;
}