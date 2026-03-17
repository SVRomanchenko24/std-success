#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
using namespace std;

typedef struct {
	string task;
	int topicId;
} task;

string generateTask(int taskId, double solution);
vector<int> getTaskAtLevel(int level);
string getRandomTaskAtLevel(int level, double solution);

#endif
