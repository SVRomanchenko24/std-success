#include <iostream>
#include <string>
#include <vector>
#include "../include/utils.h"
#include "../include/ui.h"
#include "../include/test.h"
#include "../include/accounts.h"

using namespace std;

string theory[] = {
	"placeholder",
	"placeholder",
	"placeholder",
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
