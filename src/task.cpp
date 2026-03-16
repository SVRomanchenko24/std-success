#include <string>
#include "../include/task.h"
#include "../include/utils.h"

const task taskList[] = {
	// text												  lesson
	{ "John had @ apples and lost @. How much he has left?", 1 }
};

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
			while ((args[0] = RANDOM_DECIMAL(0, 100, 2))<solution);
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
