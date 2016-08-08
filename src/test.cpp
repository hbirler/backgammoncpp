#include "test.h"

using namespace std;

bool test_learning(bool log, double testval, double eta, double decay, double eps, int length)
{
	tavla tav;
	double inp[INSIZE];
	tav.to_vector(inp);
	network net(eta, decay);
	for (int i = 0; i < length; i++)
	{
		net.update(inp, testval);
		if (log && i % 100 == 0)
		{
			double out = net.evaluate(inp);
			printf("%lf\n", out);
		}
	}

	double out = net.evaluate(inp);
	if (out - testval < eps)
		return true;
	else
		return false;
}

bool test_deviation(bool log, double minst, int length)
{
	tavla tav;
	network net;
	double inp[INSIZE];
	tav.to_vector(inp);

	double* result = new double[length];
	double sum = 0.0;

	for (int i = 0; i < length; i++)
	{
		net = network(0.01, 0.7);
		double out = net.evaluate(inp);
		result[i] = out;
		sum += out;
		if (log)
			printf("%lf\n", out);
	}

	double avg = sum / length;
	double dev = 0.0;

	for (int i = 0; i < length; i++)
	{
		dev += (result[i] - avg) * (result[i] - avg);
	}

	dev = sqrt(dev);

	delete result;

	if (dev < minst)
		return false;
	else
		return true;
}



test::test(const function<bool()>& foo, const string& name, const string& parameters)
{
	this->foo = foo;
	this->name = name;
	this->parameters = parameters;
}
test::~test() {}

test default_tests[] = {
	test([]() -> bool { return test_learning(false, 0.33); }, "Learning", "val=0.33"),
	test([]() -> bool { return test_learning(false, 0.2); }, "Learning", "val=0.2"),
	test([]() -> bool { return test_learning(false, 0.8); }, "Learning", "val=0.8"),
	test([]() -> bool { return test_deviation(false); }, "Deviation")
};

bool run_tests()
{
	return run_tests(default_tests, sizeof(default_tests) / sizeof(test));
}

bool run_tests(test tests[], int size)
{
	bool retval = true;
	for (int i = 0; i < size; i++)
	{
		cout << "Test #" << i << "  " << tests[i].name << " ( " << tests[i].parameters << " ) ...\t";
		bool result = tests[i].foo();
		if (result == true)
		{
			cout << "SUCCEEDED" << endl;
		}
		else
		{
			cout << "FAILED" << endl;
		}
		retval = retval && result;
	}
	return retval;
}

int main_test()
{
	bool result = run_tests();
	if (result == true)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}