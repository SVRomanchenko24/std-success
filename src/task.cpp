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
    { "Solve for x:\n@x + y = 2\nx - y = @", 1, 0 },
    { "Solve for y:\nx + @y = 5\n2x - 3y = @", 1, 0 },
    { "Solve for x:\n@x + 2y = 0\n3x - y = @", 1, 0 },
    { "Solve the inequalities:\nx + @y > @\n@x - y <= @", 3, 0 },
    { "Solve the inequalities:\nx + 2y > @\n3x - y <= @", 3, 0 },
    { "Solve the inequalities:\n@x + @y >= @\nx - y < @", 3, 0 },
    { "Solve the inequalities:\ny >= x^2 - @\nx + y < @", 4, 0 },
    { "Solve for x and y:\nx = @ - y\nx + y = @", 0, 0 },
    { "Solve for x and y:\n@x + @y = @\n2x - 3y = @", 1, 0 },
    { "Solve for x and y:\ny = x^2 - @\nx + y = @", 2, 0 },
    { "Solve the inequalities:\nx + @y > @\n@x - y <= @", 3, 0 },
    { "Solve the inequalities:\ny >= x^2 - @\nx + y < @", 4, 0 }
};
const int nTasks = 19;

string generateTask(int taskId, double solution)
{
	cout << taskId;
	string output = taskList[taskId].task;

	int nArgs = 0;
	for (size_t i = 0; i<output.size(); ++i) nArgs += (output[i]=='@');

	double *args = new double[nArgs];

	switch (taskId)
	{
		case 0:
		{
			args[0] = RANDOM_POSITIVE(0, 10);
			args[1] = -(args[0]-2*solution);
			break;
		}
		case 1:
		{
			args[0] = RANDOM_POSITIVE(0, 10);
			args[1] = args[0]-solution;
			break;
		}
		case 2:
		{
			args[0] = RANDOM_POSITIVE(0, 10);
			args[1] = solution*3-args[0];
			break;
		}
		case 3:
		{
			args[0] = RANDOM_POSITIVE(0, 10);
			args[1] = solution+2-argv[0]*solution;
			break;
		}
		case 4:
		{
			args[0] = RANDOM_POSITIVE(0, 10);
			args[1] = 2*(5-args[0]*solution)-3*solution;
			break;
		}
		case 5:
		{
			args[0] = RANDOM_POSITIVE(0, 10);
			args[1] = solution(6+args[0])/2;
			break;
		}
	}

	char buf[20];

	for (int i = 0, currArg = 0; currArg<nArgs; ++i, ++currArg)
	{
		i = output.find("@", i);
		if (i==-1) break;
		sprintf(buf, "%g", args[currArg]);
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
