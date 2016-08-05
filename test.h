#ifndef TESTH
#define TESTH


#include "network.h"
#include "learn.h"
#include "tavla.h"

struct test_result
{
    double white;
    double black;
    double avg;
    test_result(double w, double b);
};

class tester
{
public:
    tester();
    tester(char* logdir, bool log = true);
    ~tester();
    int test_game(networkbase& w, networkbase& b);
    test_result test_network(networkbase& net, int num);
    test_result test_network(networkbase& net, int numw, int numb);
private:
    bool log;
    char* logdir;
};

#endif