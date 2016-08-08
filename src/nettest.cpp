#include "nettest.h"

test_result::test_result(double w, double b)
{
    this->white = w;
    this->black = b;
    this->avg = (w+b)/2.0;
}


nettest::nettest()
{
	this->tolog = false;
	this->out = NULL;
}

nettest::nettest(std::ostream* os, bool tolog)
{
    this->tolog = tolog;
    this->out = os;
}

nettest::~nettest()
{
    
}

int nettest::test_game(const evaluatorbase& w, const evaluatorbase& b)
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

void nettest::log(const test_result& result, int netno)
{
	if (this->out != NULL && this->out != &std::cout)
	{
		*(this->out) << std::fixed << std::setprecision(2);
		*(this->out) << "Test Result: ";
		if (netno > 0)
			*(this->out) << "#" << netno << " ";
		*(this->out) << std::setprecision(2) << result.white << " " << result.black << "\t" << result.avg;
		*(this->out) << std::endl;
	}
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\t-Test Result: ";
    if (netno > 0)
        std::cout << "#" << netno << " ";
    std::cout << std::setprecision(2) << result.white << " " << result.black << "\t" << result.avg;
    std::cout << std::endl; 
}

test_result nettest::test_network(const evaluatorbase& net, int numw, int numb, int netno)
{
    random_evaluator dumb;
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