#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../include/accounts.h"
#include "../include/sha256.h"

int currTopic;
bool hasHomeworkPending;
bool hasTestPending;
double currAvg;
bool loggedIn;

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
    outFile << false << "\n";
    outFile << false << "\n";
    outFile.close();

    addToRegistry(username);
    return 0;
}
bool loginUser(string username, string inputPassword, int& task, double& avg, bool& hw, bool& test) {
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

    if (!(inFile >> task)) {
        task = 0;
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
    saveSession(username);
    return 0;
}

bool updateInfo(string username, int task, double avg, bool hw, bool test) {
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
    outFile << hw << "\n";
    outFile << test << "\n";
    outFile.close();
    saveSession(username);
    return 0;
}

void loadLeaderboard(vector<string>& names, vector<double>& avgs) {
    ifstream users("data/users.txt");
    string currentName;

    while (getline(users, currentName)) {
        if (currentName.empty()) continue;
        ifstream userFile(getFileName(currentName));
        string pass;
        int task;
		double avg;

        if (getline(userFile, pass) && userFile >> task && userFile >> avg) {
            names.push_back(currentName);
            avgs.push_back(avg);
        }
    }
}

// Login for last logged in user 
bool restoreSession(string& username, int& task, double& avg, bool& hw, bool& test) {
    ifstream sessionFile("data/session.txt");
    if (!sessionFile.is_open()) {
        return 1;
    }

    if (!(sessionFile >> username)) {
        sessionFile.close();
        return 1;
    }
    sessionFile.close();

    ifstream userFile(getFileName(username));
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

void logoutUser()
{
	ofstream sessionFile("data/session.txt");
	sessionFile.close();
}
