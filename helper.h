#ifndef HELPER_H
#define HELPER_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <initializer_list>
#include <string>

typedef long long BigInt;
typedef BigInt HealthPoints;
typedef BigInt Age;
typedef BigInt AttackPower;
typedef BigInt Time;

const int ERR_CODE = 42;

BigInt max(BigInt, BigInt);
void checkPointer(void *, std::string);

#endif
