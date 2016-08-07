#ifndef TESTH
#define TESTH


#include "network.h"
#include "learn.h"
#include "tavla.h"
#include <iostream>
#include <iomanip>

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
    tester(std::ostream* os, bool tolog = true);
    ~tester();
    int test_game(const networkbase& w, const networkbase& b);
    test_result test_network(const networkbase& net, int numw, int numb, int netno=-1);
    void log(const test_result& result, int netno=-1);
private:
    bool tolog;
    std::ostream* out;
};

#endif