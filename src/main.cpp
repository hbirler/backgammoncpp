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
	if (argc > 1)
	{
		if (strcmp(argv[1], "test") == 0)
			return main_test();
		else if (strcmp(argv[1], "play") == 0)
			return play(argc - 2, argv + 2);
	}

	//run_tests();
	//run_businessman();
	run_learning();

	system("pause");
    
    return 0;
}


void run_businessman()
{
	nettest tester(&cout);
	buzinessman net;


	cout << "Testing Buzinessman" << endl;
	tester.test_network(net, 50, 50, 0);
}


void run_learning()
{
	network net(0.1, 0.7);
	buzinessman buzi;


	ofstream testout;
	testout.open("./output/testout.txt", ios::out | ios::app);
	nettest tester(&testout);


	int ind = 0;

	string netpath = "./output/";

	if (file_exists(netpath + "network.bin"))
	{
		net = deserialize<network>(netpath + "network.bin");
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
			cout << "\tTesting network against buzi..." << endl;
			tester.test_network(net, 50, 50, ind, true);
			cout << "\tTesting network against rand..." << endl;
			tester.test_network(net, 50, 50, ind, false);

			cout << "\tSaving network...";
			serialize<network>(netpath + "net-" + to_string(ind) + ".bin", net);
			serialize<network>(netpath + "network.bin", net);
			cout << " Saved" << endl;
		}

		if (ind < 30000)
			learn_game(net, buzi);
		else
			learn_game(net, net);
	}


	//int qwer;
	//cin >> qwer;
}