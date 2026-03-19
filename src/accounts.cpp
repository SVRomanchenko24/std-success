#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../include/accounts.h"
#include "../include/sha256.h"

using namespace std;

string getFileName(string username) {
    return "accounts/" + username + ".txt";
}

void saveSession(string username) {
    ofstream sessionFile("data/session.txt");
    if (sessionFile.is_open()) {
        sessionFile << username;
        sessionFile.close();
    }
}

void addToRegistry(string username) {
    ofstream users("data/users.txt", ios::app);
    if (users.is_open()) {
        users << username << "\n";
    }
}

bool userExists(string username) {
    ifstream f(getFileName(username));
    return f.good();
}

bool registerUser(string username, string password) {
    if (userExists(username)) {
        return 1;
    }

    ofstream outFile(getFileName(username));
    if (!outFile.is_open()) {
        return 1;
    }

    password = hash_sha256(password.c_str());
    outFile << password << "\n";
    outFile << 1 << "\n";
    outFile << 0 << "\n";
    outFile.close();

    addToRegistry(username);
    return 0;
}

bool loginUser(string username, string inputPassword, int& task, int& avg) {
    ifstream inFile(getFileName(username));
    if (!inFile.is_open()) {
        return 1;
    }

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

bool updateInfo(string username, int task, int avg) {
    string savedPassword;
    ifstream inFile(getFileName(username));
    if (!inFile.is_open()) {
        return 1;
    }

    getline(inFile, savedPassword);
    inFile.close();

    ofstream outFile(getFileName(username));
    if (!outFile.is_open()) {
        return 1;
    }

    outFile << savedPassword << "\n";
    outFile << task << "\n";
    outFile << avg << "\n";
    outFile.close();
    return 0;
}

void loadLeaderboard(vector<string>& names, vector<int>& avgs) {
    ifstream users("data/users.txt");
    string currentName;

    while (getline(users, currentName)) {
        if (currentName.empty()) continue;
        ifstream userFile(getFileName(currentName));
        string pass;
        int task, avg;

        if (getline(userFile, pass) && userFile >> task && userFile >> avg) {
            names.push_back(currentName);
            avgs.push_back(avg);
        }
    }
}

void restoreSession() // add login for last logged in user