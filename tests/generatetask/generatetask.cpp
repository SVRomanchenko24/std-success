#include <cstdio>
#include "../../include/task.h"

int main()
{
	for (int i = 0; i<12; ++i)
	{
		printf("%s", generateTask(i, 10).c_str());
		if (i>=8) printf(" ; min - %d, max - %d", ineq_min, ineq_max);
	}
}
