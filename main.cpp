#include "main.h"

using namespace std;

int main()
{
    network net(0.01, 0.7, 5);
    tester test(&cout);
    
    
    tavla tot;
    double inp[INSIZE];
    tot.to_vector(inp);
    for (int i = 0; i<100;i++)
    {
        net = network(1, 0.7, 5);
        double out = net.evaluate(inp);
        printf("%lf\n", out);
    }
    int a;
    cin>>a;
    //return 0;
    
    clock_t begin = clock();
    for(int ind = 0;  ; ind++)
    {
        learn_game(net);
        if (ind % 100 == 0)
        {
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            
            cout<<ind<<" "<<setprecision(2)<<elapsed_secs<<endl;
            
            test.test_network(net, 50, 50, ind);
        }
    }
    
    
    int qwer;
    cin>>qwer;
    
    return 0;
}