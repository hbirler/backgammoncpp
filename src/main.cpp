#include "main.h"

using namespace std;

inline bool file_exists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

void run_learning();
void run_businessman();
void export_network();

double easy_eval(const tavla& t, const network& net, int turn) {
	double input[198];
	t.to_vector(input, turn);
	return net.evaluate(input);
}

void my_test() {
	network net;
	string netpath = "./output/";
	int net_ind;
	if (file_exists(netpath + "network.bin"))
	{
		net = deserialize<network>(netpath + "network.bin");
		net_ind = net.no;
		cout << "Loaded network... #" << net_ind << endl;
	}
	else
	{
		return;
	}

	double input[198];
	tavla tav;
	tav.to_vector(input, false);
	double ev = net.evaluate(input);

	std::vector<tavla> vec;
	tav.next_states(4, 3, vec);


	std::vector<tavla> vec1;
	tav.next_states(5, 3, vec1);
	std::vector<tavla> vec2;
	tav.next_states(3, 5, vec2);

	tavla best = choose_next(tav, net, 4, 3);

	cout << ev << endl;
	
}

string tostr(tavla b)
{
	string ms;
	for (int i = 0; i < 26; i++)
		ms += to_string(b.checkers[0][i]) + ",";
	for (int i = 0; i < 26; i++)
		ms += to_string(b.checkers[1][i]) + ",";
	ms += to_string(b.turn);
	return ms;
}
tavla fromstr(string ms)
{
	tavla b;
	char c;
	stringstream ss(ms);
	for (int i = 0; i < 26; i++)
		ss >> (int&)b.checkers[0][i] >> c;
	for (int i = 0; i < 26; i++)
		ss >> (int&)b.checkers[1][i] >> c;
	ss >> (int&)b.turn;

	return b;

}

network loadnet()
{
	network net;
	string netpath = "./output/";
	int net_ind;
	if (file_exists(netpath + "network.bin"))
	{
		net = deserialize<network>(netpath + "network.bin");
		net_ind = net.no;
		cout << "Loaded network... #" << net_ind << endl;
	}
	return net;
}

network loadnet(int ind)
{
	network net;
	string netpath = "./output/";
	int net_ind;
	if (file_exists(netpath + "network.bin"))
	{
		net = deserialize<network>(netpath + "net-" + to_string(ind) + ".bin");
		net_ind = net.no;
		cout << "Loaded network... #" << net_ind << endl;
	}
	return net;
}

void my_test2()
{
	network net = loadnet();
	while (true)
	{
		string s;
		cin >> s;
		tavla b = fromstr(s);
		vector<tavla> nexts;
		b.next_states(5, 3, nexts);


		sort(nexts.begin(), nexts.end(), [&b, &net](const tavla& x, const tavla& y) -> bool {
			return easy_eval(x, net, b.turn) > easy_eval(y, net, b.turn);
		});

		for (auto& t: nexts) {
			cout << tostr(t) << " - " << easy_eval(t, net, b.turn)<<endl;
		}
		cout << tostr(choose_next(b, net, 5, 3)) << " - ******"<<endl;
	}
}

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
	//my_test();
	//my_test2();
	//export_network();

	system("pause");
    
    return 0;
}



void test_my_network(const network& net)
{
	nettest tester(&cout);
	cout << "\tTesting network against buzi..." << endl;
	tester.test_network(net, 50, 50, net.no, true);
	cout << "\tTesting network against rand..." << endl;
	tester.test_network(net, 50, 50, net.no, false);
}

void export_network()
{
	network net;
	string netpath = "./output/";
	int net_ind;
	if (file_exists(netpath + "network.bin"))
	{
		net = deserialize<network>(netpath + "network.bin");
		net_ind = net.no;
		cout << "Loaded network... #" << net_ind << endl;
	}
	else
	{
		return;
	}

	test_my_network(net);

	double ws[INSIZE + 3][HIDSIZE];
	net.export_weights(ws);
	serialize("./output/weights.bin", ws);
	//string output = encode_16(ws);
	//cout << endl << output << endl;
	cout << "Serialization succeeded." << endl;
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
	//network net(0.1, 0.7);
	//buzinessman buzi;
	string netpath = "./output/";

	ofstream testout;
	testout.open("./output/testout.txt", ios::out | ios::app);
	nettest tester(&testout);


	int ind = 0;

	network net = loadnet();

	double ws[INSIZE + 3][HIDSIZE];
	

	cout << std::fixed << std::setprecision(2);

	clock_t begin = clock();
	for (ind; ; ind += 2)
	{
		double busyrate = exp(-ind / 65536.0);
		double randbusyrate = busyrate * 0.8;
		double normbusyrate = busyrate * 0.2;
		double prerate = (1 - busyrate) * 0.1;
		double eta = exp(-ind / 131072.0) * 0.1;

		net.set_eta(eta);
		net.no = ind;

		if (ind % 100 == 0)
		{
			clock_t end = clock();
			double elapsed_secs = (double)(end - begin) / CLOCKS_PER_SEC;
			cout << setw(8) << left << ind << " " << elapsed_secs << endl;
		}

		if (ind % 1000 == 0)
		{
			buzinessman buzir(true);
			buzinessman buzin(false);
			int nind = ind / 4 * 3 / 1000 * 1000;
			network prent = loadnet(nind);

			cout << "\tTesting network against prent..." << endl;
			tester.test_network(net, 25, 25, ind, false, "prent");
			cout << "\tTesting network against buzir..." << endl;
			tester.test_network(net, 25, 25, ind, true, "buzir");
			cout << "\tTesting network against buzin..." << endl;
			tester.test_network(net, 25, 25, ind, true, "buzin");
			cout << "\tTesting network against randm..." << endl;
			tester.test_network(net, 25, 25, ind, false, "randm");

			cout << "\tSaving network...";
			serialize<network>(netpath + "net-" + to_string(ind) + ".bin", net);
			serialize<network>(netpath + "network.bin", net);

			net.export_weights(ws);
			serialize("./output/weights.bin", ws);
			cout << " Saved" << endl;
		}

		double todo = randf();
		if (todo < busyrate) {

			if (todo < randbusyrate)
			{
				buzinessman buzi(true);
				learn_game(net, buzi);
				learn_game(buzi, net);
			}
			else {
				buzinessman buzi(false);
				learn_game(net, buzi);
				learn_game(buzi, net);
			}
		}
		else if (todo < busyrate + prerate) {
			int nind = ind / 4 * 3 / 1000 * 1000;
			network other = loadnet(nind);
			learn_game(net, other);
			learn_game(other, net);
		}
		else {
			learn_game(net, net);
			learn_game(net, net);
		}

		/*buzinessman buzi(true);

		if (ind < 30000)
			learn_game(net, buzi);
		else
			learn_game(net, net);*/
	}


	//int qwer;
	//cin >> qwer;
}