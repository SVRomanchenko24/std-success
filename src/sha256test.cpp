#include <iostream>
#include <string>
#include "../include/sha256.h"
#include <cstdint>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
	if (argc!=2) return 0;
	cout << hash_sha256(argv[1]) << endl;
	printf("%b\n", RIGHTROTATE((uint32_t)1,1));
}
