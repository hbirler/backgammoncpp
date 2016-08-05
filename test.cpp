#include "test.h"

test_result::test_result(double w, double b)
{
    this->white = w;
    this->black = b;
    this->avg = (w+b)/2.0;
}

tester::tester()
{
    this->log = false;
}

tester::tester(char* logdir, bool log = true)
{
    this->log = log;
    this->logdir = logdir;
}

tester::~tester()
{
}

int tester::test_game(networkbase& w, networkbase& b)
{
    
}

test_result tester::test_network(networkbase& net, int num)
{
    return test_network(net, num, num);
}

test_result tester::test_network(networkbase& net, int numw, int numb)
{
    network_random dumb;
    int wwin = 0, bwin = 0;
    for (int i = 0; i < numw; i++)
    {
        wwin += test_game(net, dumb) == WHITE;
    }
    
    for (int i = 0; i < numb; i++)
    {
        bwin += test_game(dumb, net) == BLACK;
    }
    
    return test_result(wwin*1.0/numw, bwin*1.0/numb);
}