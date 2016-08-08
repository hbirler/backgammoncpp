#pragma once

#include <cstdio>
#include <cstdlib>
#include <functional>

#include "tavla.h"
#include "network.h"
#include "nettest.h"

using namespace std;

struct test
{
	function<bool()> foo;
	string name;
	string parameters;
	test(const function<bool()>& foo, const string& name = "Unnamed", const string& parameters = "default");
	~test();
};

//test default_tests[];

bool test_deviation(bool log = false, double minst = 0.1, int length = 500);
bool test_learning(bool log = false, double testval = 0.33, double eta = 0.01, double decay = 0.7, double eps = 0.00001, int length = 10000);


bool run_tests();
bool run_tests(test tests[], int size);
int main_test();