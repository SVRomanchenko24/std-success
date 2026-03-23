#include <iostream>
#include <string>
#include <vector>
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/test.h"
#include "../include/accounts.h"

using namespace std;

string theory[] = {
	"The Substitution Method involves solving one equation for a single variable (like x=...) and then plugging that expression into the other equation to create one simple equation you can solve.",
	"You align the equations and add them together so that one variable (like x or −x) equals zero, allowing you to solve for the remaining variable immediately.",
	"To solve a system of inequalities, you graph each line separately and find the overlapping shaded area (the intersection) that satisfies every inequality in the set.",
};

int classwork()
{
	term_clear();
	short x, y;
	term_getTermSize(x, y);
	cout << currTopic;
	vector<string> splitTheory = fitStringToWidth(theory[currTopic], x-2);
	for (size_t i = 0; i<splitTheory.size(); ++i)
	{
		term_moveCursor(1, 1+i);
		cout << splitTheory[i];
	}
	term_getch();
	if (!hasHomeworkPending)
	{
		if (test("Classwork", 3)==-1) return -1;
		hasHomeworkPending = 1;
	}
	return 0;
}
