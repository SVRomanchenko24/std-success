#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "../include/task.h"
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/ui-common.h"
#include "../include/keycodes.h"
#include "../include/defines.h"

static task taskList[] = {
    // text                           lesson  canBeDecimal
    { "Solve for y:\nx = @ - y\nx + 3y = @", 0, 0 },
    { "Solve for x:\n2x - @ = y\nx - y = @", 0, 0 },
    { "Solve for y:\nx = 2y - @\nx + y = @", 0, 0 },
    { "Solve for x:\nx + y = @ - 2y\n2x - 3y = @", 0, 0 },
    { "Solve for x:\n@x - y = 1\nx + y = @", 1, 0 },
    { "Solve for x:\n@x + y = 2\nx - y = @", 1, 0 },
    { "Solve for y:\nx + @y = 5\n2x - 3y = @", 1, 0 },
    { "Solve for x:\n@x + 2y = 0\n3x - y = @", 1, 0 },
	{ "Which one is the solution for:\nx > @(1 - 2x)\nx < @", 2, 1 },
    { "Which one is the solution for:\nx > (2 - @)*x - 10\n3(x + 1) <= @", 2, 1 },
    { "Which one is the solution for:\n@(x + 2) < 1\n@x > 8", 2, 1 },
    { "Which one is the solution for:\n-x + @(x - 3) > 4\n3x <= @ + 2x", 2, 1 }

};
const int nTasks = 12;
double ineq_max, ineq_min;

string generateTask(int taskId, double solution)
{
	cout << taskId;
	string output = taskList[taskId].task;

	int nArgs = 0;
	for (size_t i = 0; i<output.size(); ++i) nArgs += (output[i]=='@');

	double *args = new double[nArgs];

	args[0] = RANDOM(2, 10);
	switch (taskId)
	{
		case 0:
		{
			args[1] = -(args[0]-2*solution);
			break;
		}
		case 1:
		{
			args[1] = args[0]-solution;
			break;
		}
		case 2:
		{
			args[1] = solution*3-args[0];
			break;
		}
		case 3:
		{
			args[1] = 2*solution-(args[0]-solution);
			break;
		} // begin 1
		case 4:
		{
			args[1] = solution+(args[0]*solution-1);
			break;
		}
		case 5:
		{
			args[1] = solution+2-args[0]*solution;
			break;
		}
		case 6:
		{
			args[1] = 2*(5-args[0]*solution)-3*solution;
			break;
		}
		case 7:
		{
			args[1] = solution*(6+args[0])/2;
			break;
		} // begin 2
		case 8:
		{
			args[1] = RANDOM(1, 10);
			ineq_min = args[0]/(1+2*args[0]);
			ineq_max = args[1];
			break;
		}
		case 9:
		{
			args[0] = RANDOM(2, 10);
			args[1] = RANDOM(1, 10);
			ineq_min = -10/(1-2+args[0]);
			ineq_max = args[1]/3-1;
			break;
		}
		case 10:
		{
			args[0] = RANDOM(2, 10);
			args[1] = RANDOM(2, 10);
			ineq_min = 8/args[1];
			ineq_max = (1-args[0]*2)/args[0];
			break;
		}
		case 11:
		{
			args[0] = RANDOM(2, 10);
			args[1] = RANDOM(1, 10);
			ineq_min = (3*args[0]+4)/(args[0]-1);
			ineq_max = args[1];
			break;
		}
	}

	char buf[20];

	for (int i = 0, currArg = 0; currArg<nArgs; ++i, ++currArg)
	{
		i = output.find("@", i);
		if (i==-1) break;
		sprintf(buf, "%.2g", args[currArg]);
		output.replace(i, 1, buf);
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
