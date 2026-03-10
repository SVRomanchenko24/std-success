#ifndef SHA256_H
#define SHA256_H

#define RIGHTROTATE(var, n) (var>>n|var<<32-n)

#include <string>
using namespace std;

string hash_sha256(const char *input);

#endif
