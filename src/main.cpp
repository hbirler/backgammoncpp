#include "main.h"

using namespace std;

inline bool file_exists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main()
{
    network net(0.1, 0.7);
	ofstream testout;
	testout.open("./output/testout.txt", ios::out | ios::app);
    tester test(&testout);
    
    /*tavla tot;
    double inp[INSIZE];
    tot.to_vector(inp);
    network noto(0.01, 0.7);
    for (int i = 0; i < 10000;i++)
    {
        noto.update(inp, 0.33);
        if (i % 100 == 0)
        {
            double out = noto.evaluate(inp);
            printf("%lf\n", out);
        }
    }
    int a;
    cin>>a;*/
    
    
    /*tavla tot;
    double inp[INSIZE];
    tot.to_vector(inp);
    for (int i = 0; i<100;i++)
    {
        net = network(0.01, 0.7, 5);
        double out = net.evaluate(inp);
        printf("%lf\n", out);
    }
    int a;
    cin>>a;
    
    net = network(0.01, 0.7, 5);*/
    
    //return 0;

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
    for (ind;  ; ind++)
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
            test.test_network(net, 50, 50, ind);
			
			cout << "\tSaving network...";
			serialize<network>(netpath, net);
			cout << " Saved" << endl;
        }


		learn_game(net);
    }
    
    
    int qwer;
    cin>>qwer;
    
    return 0;
}