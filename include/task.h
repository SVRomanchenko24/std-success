#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

typedef struct {
	string task;
	int topicId;
} task;

string generateTask(int taskId, double solution);

#endif
