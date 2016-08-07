#ifndef MYRANDOMH
#define MYRANDOMH

#include <random>

void roll(int* d1, int* d2);
double randf();
double randn();
std::mt19937& get_generator();

#endif