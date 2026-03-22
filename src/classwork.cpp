#include <iostream>
#include <string>
#include <vector>
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/test.h"
#include "../include/accounts.h"

using namespace std;

string theory[] = {
	"The Substitution Method involves solving one equation for a single variable (like x=…) \n\t and then plugging that expression into the other equation to \n\t create one simple equation you can solve.",
	"You align the equations and add them together so that one variable (like x or −x) equals zero,\n\t allowing you to solve for the remaining variable immediately.",
	"To solve these, you substitute the linear equation into the quadratic one, creating a single \n\t quadratic equation (ax2+bx+c=0) that you solve using factoring or \n\t the quadratic formula.",
	"placeholder",
	"placeholder"
};

int classwork()
{
	term_clear();
	short x, y;
	term_getTermSize(x, y);
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
