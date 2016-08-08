#include "main.h"

using namespace std;

inline bool file_exists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

void run_learning();
void run_businessman();


int main(int argc, char *argv[])
{
	if (argc > 1 && strcmp(argv[1], "test") == 0)
	{
		return main_test();
	}


	run_businessman();
	//run_learning();

	system("pause");
    
    return 0;
}


void run_businessman()
{
	nettest tester(&cout);
	buzinessman net;


	cout << "Testing Businessman" << endl;
	tester.test_network(net, 50, 50, 0);
}


void run_learning()
{
	network net(0.1, 0.7);
	ofstream testout;
	testout.open("./output/testout.txt", ios::out | ios::app);
	nettest tester(&testout);


	int ind = 0;

	string netpath = "./output/network.bin";

	if (file_exists(netpath))
	{
		net = deserialize<network>(netpath);
		ind = net.no;
		cout << "Loaded network... #" << ind << endl;
	}

	cout << std::fixed << std::setprecision(2);

	clock_t begin = clock();
	for (ind; ; ind++)
	{
		net.no = ind;

		if (ind % 100 == 0)
		{
			clock_t end = clock();
			double elapsed_secs = (double)(end - begin) / CLOCKS_PER_SEC;
			cout << setw(8) << left << ind << " " << elapsed_secs << endl;
		}

		if (ind % 1000 == 0)
		{
			cout << "\tTesting network..." << endl;
			tester.test_network(net, 50, 50, ind);

			cout << "\tSaving network...";
			serialize<network>(netpath, net);
			cout << " Saved" << endl;
		}


		learn_game(net);
	}


	//int qwer;
	//cin >> qwer;
}