#include <string>
#include <vector>
#include "../include/task.h"
#include "../include/utils.h"

const task taskList[] = {
	// text												  lesson
	{ "John had @ apples and lost @. How much he has left?", 0 }
};

const int nTasks = 1;

string generateTask(int taskId, double solution)
{
	string output = taskList[taskId].task;

	int nArgs = 0;
	for (size_t i = 0; i<output.size(); ++i) nArgs += (output[i]=='@');

	double *args = new double[nArgs];

	switch (taskId)
	{
		case 0: // example
		{
			while ((args[0] = RANDOM_POSITIVE(0, 100))<solution);
			args[1] = args[0] - solution;
			break;
		}
		default: exit(1);
	}


	for (int i = 0, currArg = 0; currArg<nArgs; ++i, ++currArg)
	{
		i = output.find("@", i);
		if (i==-1) break;
		output.replace(i, 1, to_string(args[currArg]));
	}

	return output;
}

vector<int> getTasksAtLevel(int level)
{
	vector<int> tasks;
	for (size_t i = 0; i<nTasks; ++i)
		if (taskList[i].topicId==level)
			tasks.push_back(i);
	return tasks;
}

string getRandomTaskAtLevel(int level, double solution)
{
	return generateTask(getTasksAtLevel(level)[getTasksAtLevel(level).size()!=0*RANDOM_POSITIVE(0, nTasks)], solution);
}
