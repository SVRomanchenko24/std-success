#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../include/accounts.h"
#include "../include/sha256.h"

string userName;
int currTopic;
bool hasHomeworkPending;
bool hasTestPending;
double currAvg;
bool loggedIn;

using namespace std;

string getFileName(string userName) {
    return "accounts/" + userName + ".txt";
}

void saveSession(string userName) {
    ofstream sessionFile("data/session.txt");
    if (sessionFile.is_open()) {
        sessionFile << userName;
        sessionFile.close();
    }
}

void addToRegistry(string userName) {
    ofstream users("data/users.txt", ios::app);
    if (users.is_open()) {
        users << userName << "\n";
    }
}

bool userExists(string userName) {
    ifstream f(getFileName(userName));
    return f.good();
}

bool registerUser(string userName, string password) {
    if (userExists(userName)) {
        return 1;
    }

    ofstream outFile(getFileName(userName));
    if (!outFile.is_open()) {
        return 1;
    }

    password = hash_sha256(password.c_str());
    outFile << password << "\n";
    outFile << 1 << "\n";
    outFile << 0 << "\n";
    outFile << false << "\n";
    outFile << false << "\n";
    outFile.close();

    addToRegistry(userName);
    return 0;
}

bool loginUser(string userName, string inputPassword, int& task, int& avg, bool& hw, bool& test) {
    ifstream inFile(getFileName(userName));
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

    if (!(inFile >> task)) {
        task = 1;
    }
    if (!(inFile >> avg)) {
        avg = 0;
    }
    if (!(inFile >> hw)) {
        hw = 0;
    }
    if (!(inFile >> test)) {
        test = 0;
    }

    inFile.close();
    saveSession(userName);
    return 0;
}

bool updateInfo(string userName, int task, double avg, bool hw, bool test) {
    string savedPassword;
    ifstream inFile(getFileName(userName));
    if (!inFile.is_open()) {
        return 1;
    }

    getline(inFile, savedPassword);
    inFile.close();

    ofstream outFile(getFileName(userName));
    if (!outFile.is_open()) {
        return 1;
    }

    outFile << savedPassword << "\n";
    outFile << task << "\n";
    outFile << avg << "\n";
    outFile << hw << "\n";
    outFile << test << "\n";
    outFile.close();
    saveSession(userName);
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

// Login for last logged in user 
bool restoreSession(string& userName, int& task, double& avg, bool& hw, bool& test) {
    ifstream sessionFile("data/session.txt");
    if (!sessionFile.is_open()) {
        return 1;
    }

    if (!(sessionFile >> userName)) {
        sessionFile.close();
        return 1;
    }
    sessionFile.close();

    ifstream userFile(getFileName(userName));
    if (!userFile.is_open()) {
        return 1;
    }

    string pass;
    getline(userFile, pass);

    if (!(userFile >> task)) {
        task = 1;
    }
    if (!(userFile >> avg)) {
        avg = 0;
    }
    if (!(userFile >> hw)) {
        hw = false;
    }
    if (!(userFile >> test)) {
        test = false;
    }

    userFile.close();
    return 0;
}
