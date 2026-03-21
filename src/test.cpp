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

		sprintf(buf, "%g", solution);

		int answerIndex = RANDOM(0, 4);
		solutions[answerIndex] = buf;

		for (int i = 0; i<4; ++i)
		{
			if (i==answerIndex) continue;
			sprintf(buf, "%g", (canBeDecimal?RANDOM_DECIMAL(solution-4, solution+4, 2):RANDOM(solution-6, solution+6)));
			solutions[i] = buf;
		}

		int result = taskUI(i+1, size, type, task, solutions);
		if (result == -1) return -1;
		correctAnswers += result;
	}
	return correctAnswers;
}
