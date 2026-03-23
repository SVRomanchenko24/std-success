#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <string>
#include <vector>

using namespace std;

int _random();
vector<string> fitStringToWidth(string str, size_t width);

#define RANDOM(min, max) (_random()%(int)(max-min)+min) // random with min and max boundaries
#define RANDOM_DECIMAL(min, max, decimalSigns) (RANDOM(min, max)+RANDOM(0, pow(10, decimalSigns))/pow(10, decimalSigns))

#endif
