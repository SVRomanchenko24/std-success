#include <cstdio>
#include <string>
#include "../include/ui.h"
#include "../include/test.h"
#include "../include/task.h"
#include "../include/utils.h"
#include "../include/accounts.h"

using namespace std;

int test(string type, int size)
{
	int correctAnswers = 0;
	for (int i = 0; i<size; ++i)
	{
		string task, solutions[4];
		char buf[10];

		int taskId = getRandomTaskIdAtLevel(currTopic);

		bool canBeDecimal = solutionCanBeDecimal(taskId);
		double solution = (canBeDecimal?RANDOM_DECIMAL(-100, 100, 2):RANDOM(-100, 100));

		task = generateTask(taskId, solution);

		if (currTopic!=2) // not ineq
			sprintf(buf, "%g", solution);
		else
		{
			switch (taskId)
			{
				case 8:
				{
					sprintf(buf, "(%g;%g)", ineq_min, ineq_max);
					break;
				}
				case 9:
				{
					sprintf(buf, "(%g;%g]", ineq_min, ineq_max);
					break;
				}
				case 10:
				{
					sprintf(buf, "(%g;+inf)", ineq_min);
					break;
				}
				case 11:
				{
					sprintf(buf, "(%g;%g]", ineq_min, ineq_max);
					break;
				}
			}
		}

		int answerIndex = RANDOM(0, 4);
		solutions[answerIndex] = buf;

		for (int i = 0; i<4; ++i)
		{
			if (i==answerIndex) continue;
			if (currTopic!=2) // not ineq
				sprintf(buf, "%g", (canBeDecimal?RANDOM_DECIMAL(solution-4, solution+4, 2):RANDOM(solution-6, solution+6)));
			else
			{
				switch (taskId)
				{
					case 8:
					{
						sprintf(buf, "(%g;%g)", RANDOM_DECIMAL(ineq_min-4, ineq_min+4, 2), RANDOM_DECIMAL(ineq_max-4, ineq_max+4, 2));
						break;
					}
					case 9:
					{
						sprintf(buf, "(%g;%g]", RANDOM_DECIMAL(ineq_min-4, ineq_min+4, 2), RANDOM_DECIMAL(ineq_max-4, ineq_max+4, 2));
						break;
					}
					case 10:
					{
						sprintf(buf, "(%g;+inf)", RANDOM_DECIMAL(ineq_min-4, ineq_min+4, 2));
						break;
					}
					case 11:
					{
						sprintf(buf, "(%g;%g]", RANDOM_DECIMAL(ineq_min-4, ineq_min+4, 2), RANDOM_DECIMAL(ineq_max-4, ineq_max+4, 2));
						break;
					}
				}
			}
			solutions[i] = buf;
		}

		int result = taskUI(i+1, size, type, task, solutions);
		if (result == -1) return -1;
		correctAnswers += result;
	}
	return correctAnswers;
}
