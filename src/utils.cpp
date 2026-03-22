#include <ctime>
#include <random>
#include <string>
#include <vector>
#include "../include/utils.h"

using namespace std;

int _random()
{
	struct timespec ts;
	static int last_mask; // avoiding repetition in consequent generations
	timespec_get(&ts, TIME_UTC);
	mt19937 mt(ts.tv_nsec);
	srand(mt()^last_mask);
	last_mask -= rand();
	return rand();
}

vector<string> fitStringToWidth(string str, size_t width)
{
	vector<string> ret;
	int currLine = 0;
	for (size_t i = 0, lastNewLine = 0, lastSpace = 0; i<str.size(); ++i)
	{
		if (str[i]==' ') lastSpace = i;
		else if (str[i]=='\n')
		{
			ret[currLine++] = str.substr(lastNewLine, i-lastNewLine-1);
			lastNewLine = i + 1;
		}
		if (i-lastNewLine>=width)
		{
			ret[currLine++] = str.substr(lastNewLine, lastSpace-lastNewLine);
			lastNewLine = lastSpace + 1;
		}
	}
	return ret;
}
