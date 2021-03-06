#pragma once


#include "network.h"
#include "learn.h"
#include "tavla.h"
#include "buzinessman.h"
#include <iostream>
#include <iomanip>

struct test_result
{
    double white;
    double black;
    double avg;
    test_result(double w, double b);
};

class nettest
{
public:
    nettest();
    nettest(std::ostream* os, bool tolog = true);
    ~nettest();
    int test_game(const evaluatorbase& w, const evaluatorbase& b);
	test_result test_network(const evaluatorbase& net, int numw, int numb, int netno, const evaluatorbase& other, std::string note);
    test_result test_network(const evaluatorbase& net, int numw, int numb, int netno=-1, bool buzi=false, std::string note = "");
    void log(const test_result& result, int netno=-1, std::string note = "");
private:
    bool tolog;
    std::ostream* out;
};