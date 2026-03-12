#ifndef accounts_h
#define accounts_h

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string getFileName(string username);
bool registerUser(string username, string password);
bool loginUser(string username, string inputPassword, int& task);
bool updateInfo(string username, string password, int task);

#endif