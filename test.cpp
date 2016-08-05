#include "test.h"

test_result::test_result(double w, double b)
{
    this->white = w;
    this->black = b;
    this->avg = (w+b)/2.0;
}


tester::tester(std::ostream* os, bool tolog)
{
    this->tolog = tolog;
    this->out = os;
}

tester::~tester()
{
    
}

int tester::test_game(const networkbase& w, const networkbase& b)
{
    tavla tav;
    
    while (!tav.is_end())
    {
        int d1, d2;
        roll(&d1, &d2);
        if (tav.turn == WHITE)
            tav = choose_next(tav, w, d1, d2);
        else
            tav = choose_next(tav, b, d1, d2);
    }
    return tav.get_winner();
}

void tester::log(const test_result& result, int netno)
{
    *(this->out) << "Test Result: ";
    if (netno > 0)
    {
        *(this->out) << "#" << netno << " ";
    }
    *(this->out) << std::setprecision(2) << result.white << " " << result.black << "\t" << result.avg;
    *(this->out) << std::endl;
}

test_result tester::test_network(const networkbase& net, int numw, int numb, int netno)
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
    
    test_result res(wwin*1.0/numw, bwin*1.0/numb);
    
    if (this->tolog)
        log(res, netno);
    
    return res;
}