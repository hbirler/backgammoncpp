#include "myrandom.h"

void roll(int* d1, int* d2)
{
	static std::uniform_int_distribution<int> distribution(1, 6);
	*d1 = distribution(get_generator());
	*d2 = distribution(get_generator());
}

double randf()
{
	static std::uniform_real_distribution<double> distribution(0, 1);
	return distribution(get_generator());
}

double randn()
{
	static std::normal_distribution<double> distribution(0.0, 1.0);
	return distribution(get_generator());
}

std::mt19937& get_generator()
{
	static std::random_device rd;
	static std::mt19937 generator(rd());
	return generator;
}