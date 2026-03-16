#include <cstdio>
#include "../../include/task.h"

int main(int argc, char **argv)
{
	if (argc!=2) return 1;
	if (*argv[1]==0) return 1;
	int arg;
	sscanf(argv[1], "%d", &arg);
	printf("%s\n", generateTask(arg, 10).c_str());
}
