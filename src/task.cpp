#include <string>
#include <vector>
#include <iostream>
#include "../include/task.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/ui-common.h"
#include "../include/keycodes.h"
#include "../include/defines.h"

static task taskList[] = {
	// text												lesson	canBeDecimal
	{ "Solve for y:\nx+@y-@=0\nx-@=0", 0, 0 }
	{ "Solve for x:\nx+@=y\n@y-x=@", 0, 0 }
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
		case 0:
		{
			argv[0] = RANDOM_POSITIVE(0, 10);
			argv[1] = RANDOM_POSITIVE(0, 10);
			argv[2] = argv[1] - argv[0]*solution;
			break;
		}
		case 1:
		{
			argv[0] = RANDOM_POSITIVE(0, 10);
			argv[1] = RANDOM_POSITIVE(0, 10);
			argv[2] = argv[0]*argv[1] + (argv[1]-1);
			break;
		}
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

int getRandomTaskIdAtLevel(int level)
{
	vector<int> tasks = getTasksAtLevel(level);
	return tasks[RANDOM(0, tasks.size())];
}

bool solutionCanBeDecimal(int taskId)
{
	return taskList[taskId].canBeDecimal;
}

void drawTaskUI(int currTask, int totalTasks, string topic, string task, string solutions[4], int selection)
{
	term_clear();

	short x, y;
	term_getTermSize(x, y);

	term_moveCursor(0,0);
	cout << topic << ' ' << currTask << '/' << totalTasks;

	vector<string> splitTaskText = fitStringToWidth(task, x-2);
	for (size_t i = 0; i<splitTaskText.size() && i<(size_t)(y/2+2); ++i) // print task
	{
		term_moveCursor(1, i+1);
		cout << splitTaskText[i];
	}

	for (int i = 0; i<4; ++i) // print answers
	{
		term_moveCursor(y/4*(2+(i&1)), x/4+(x/2*(i&1)==0));

		if (i==selection) term_invertColorPair();
		cout << solutions[i];
		if (i==selection) term_invertColorPair();
	}
}

int taskUI(int currTask, int totalTasks, string topic, string task, string solutions[4])
{
	int selection = 0;
	drawTaskUI(currTask, totalTasks, topic, task, solutions, selection);

	uint8_t ch;
	while ((ch = term_getch())!=KEY_ENTER)
	{
		switch (ch)
		{
			case CONTROL('C'):
			{
				if (drawExitWarning()) return -1; // if the warning is ignored
				break;
			}
			case KEY_ARROW_UP:
			{
				selection = (selection|1)-1;
				break;
			}
			case KEY_ARROW_DOWN:
			{
				selection |= 1;
				break;
			}
			case KEY_ARROW_LEFT:
			{
				selection = (selection|2)-2;
				break;
			}
			case KEY_ARROW_RIGHT:
			{
				selection |= 2;
				break;
			}
			default: break;
		}
		drawTaskUI(currTask, totalTasks, topic, task, solutions, selection);
	}

	return selection;
}
