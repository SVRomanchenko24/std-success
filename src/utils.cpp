#include <ctime>
#include <random>
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
