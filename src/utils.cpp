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
	size_t lastNewLine = 0;
	for (size_t i = 0, lastSpace = 0; i<str.size(); ++i)
	{
		if (str[i]==' ') lastSpace = i;
		else if (str[i]=='\n')
		{
			ret.push_back(str.substr(lastNewLine, i-lastNewLine-1));
			lastNewLine = i + 1;
			continue;
		}
		if (i-lastNewLine>=width)
		{
			ret.push_back(str.substr(lastNewLine, lastSpace-lastNewLine));
			lastNewLine = lastSpace + 1;
		}
	}
	ret.push_back(str.substr(lastNewLine));
	return ret;
}
