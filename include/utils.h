#ifndef UTILS_H
#define UTILS_H

#include <cmath>

using namespace std;

int _random();

#define RANDOM(min, max) (_random()%(int)(max-min)+min) // random with min and max boundaries
#define RANDOM_POSITIVE(min, max) ((_random()>>1)%(max-min)+min) // remove the signedness bit
#define RANDOM_DECIMAL(min, max, decimalSigns) (RANDOM(min, max)/pow(10, decimalSigns)+RANDOM(min, max))

#endif
