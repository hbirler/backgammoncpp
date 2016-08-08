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

bool test_tavla2vector(bool log)
{
	tavla org, aft;
	
	org = tavla();
	org.checkers[0][6]--;
	org.checkers[0][0]++;
	org.checkers[0][24]--;
	org.checkers[0][25]++;

	double input[INSIZE];
	org.to_vector(input);
	aft = tavla(input);

	bool r1 = org == aft;

	org = tavla();
	org.checkers[0][6]--;
	org.checkers[0][0]++;
	org.checkers[0][24]--;
	org.checkers[0][25]++;


	org.to_vector(input, true);
	aft = tavla(input);

	bool r2 = true;
	for (int i = 0; i < 26; i++)
	{
		r2 = r2 && (org.checkers[0][i] == aft.checkers[1][i]);
	}
	r2 = r2 && org.turn == !aft.turn;

	bool result = r1 && r2;

	return result;
}

bool test_choosenext(bool log)
{
	evaluatorlambda myeval([](double input[INSIZE])->double {
		tavla t(input);
		int rval = t.checkers[0][23] + t.checkers[0][4] - (t.checkers[1][23] + t.checkers[1][4]);
		return sigmoid(rval);
	}, [](double input[INSIZE], double output) {
		return;
	});

	tavla tav;

	tavla next = choose_next(tav, myeval, 1, 2);

	tav.turn = !tav.turn;
	tav.checkers[0][24]--;
	tav.checkers[0][6]--;
	tav.checkers[0][23]++;
	tav.checkers[0][4]++;

	bool r1 = tav == next;

	tav = tavla();
	tav.turn = !tav.turn;

	next = choose_next(tav, myeval, 1, 2);

	tav.turn = !tav.turn;
	tav.checkers[1][24]--;
	tav.checkers[1][6]--;
	tav.checkers[1][23]++;
	tav.checkers[1][4]++;

	bool r2 = tav == next;

	bool result = r1 && r2;

	return result;
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
	test([]() -> bool { return test_deviation(false); }, "Deviation"),
	test([]() -> bool { return test_tavla2vector(false); }, "Tav2Vec"),
	test([]() -> bool { return test_choosenext(false); }, "ChooseNxt")
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