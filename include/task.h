#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
using namespace std;

typedef struct {
	string task;
	int topicId;
	bool canBeDecimal;
} task;

string generateTask(int taskId, double solution);
vector<int> getTasksAtLevel(int level);
int getRandomTaskIdAtLevel(int level);

#endif
