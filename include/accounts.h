#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <string>
#include <vector>

using namespace std;

string getFileName(string username);
bool registerUser(string username, string password);
bool loginUser(string username, string inputPassword, int& task, double& avg, bool& hw, bool& test);
bool updateInfo(string username, int task, double avg, bool hw, bool test);
bool restoreSession(string& username, int& task, double& avg, bool& hw, bool& test);
void loadLeaderboard(vector<string>& names, vector<double>& avgs);
void logoutUser();

extern int currTopic;
extern bool hasHomeworkPending;
extern bool hasTestPending;
extern bool loggedIn;
extern double currAvg;

#endif
