#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <string>

using namespace std;

string getFileName(string username);
bool registerUser(string username, string password);
bool loginUser(string username, string inputPassword, int& task);
bool updateInfo(string username, int task, double avg, bool hw, bool test);
bool restoreSession(string& username, int& task, double& avg, bool& hw, bool& test);

extern int currTopic;
extern bool hasHomeworkPending;
extern bool hasTestPending;
extern bool loggedIn;
extern double currAvg;

#endif
