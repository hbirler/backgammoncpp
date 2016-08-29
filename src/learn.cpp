#include "learn.h"


double evaluate(const tavla& t, const evaluatorbase& net, int turn)
{
	static double output[INSIZE];
    if (t.is_end())
    {
        return t.get_winner() == turn;
    }
    
    t.to_vector(output, turn);
    
    double out = net.evaluate(output);
    
    return out;
}

tavla choose_next(tavla tav, const evaluatorbase& net, int d1, int d2)
{
    std::vector<tavla> vec;
    tav.next_states(d1, d2, vec);

	//std::string mystr = "";
	//for (auto& t : vec)
	//	mystr += t.str() + "\n";
    
    int bestind = 0;
    double maxval =-1.0;

    
    for (int i = 0; i < vec.size(); i++)
    {
        double nval = evaluate(vec[i], net, tav.turn);
        if (nval > maxval)
        {
            bestind = i;
            maxval = nval;
        }
    }
    
    return vec[bestind];
}

/*tavla choose_next_depr(tavla tav, const networkbase& net, int d1, int d2)
{
    std::vector<tavla> vec;
    tavla retval = tav.next_best_state(d1, d2, vec, [](const tavla& tav)->double {
        double eval = evaluate(tav, net, WHITE);
        if (tav.turn == 0)
            return eval;
        else
            return 1-eval;
    });
    
    
    return retval;
}*/

void update_net(const tavla& tav, double val, evaluatorbase& net, int turn = 0)
{
    static double input[INSIZE];
    tav.to_vector(input, turn);
    //printf("xx%d\n",net.nono);
    net.update(input, val);
}

void learn_game(evaluatorbase& net)
{
	learn_game(net, net);
}
void learn_game(evaluatorbase& netw, evaluatorbase& netb)
{
	random_evaluator dumb;
	tavla tav;

	tavla pre;

	while (!tav.is_end())
	{
		int d1, d2;
		roll(&d1, &d2);

		update_net(pre, evaluate(tav, netw, WHITE), netw, WHITE);
		update_net(pre, evaluate(tav, netb, BLACK), netw, BLACK);
		pre = tav;

		if (tav.turn == WHITE)
			tav = choose_next(tav, netw, d1, d2);
		else if (tav.turn == BLACK)
			tav = choose_next(tav, netb, d1, d2);
	}
	update_net(pre, evaluate(tav, netw, WHITE), netw, WHITE);
	update_net(pre, evaluate(tav, netb, BLACK), netw, BLACK);

	update_net(tav, evaluate(tav, netw, WHITE), netw, WHITE);
	update_net(tav, evaluate(tav, netb, BLACK), netw, BLACK);

}

void learn_game_depr(evaluatorbase& netw, evaluatorbase& netb)
{
    random_evaluator dumb;
    tavla tav;
    
    tavla prew;
    tavla preb;
    bool wfirst = true;
    bool bfirst = true;
    
    while (!tav.is_end())
    {
        int d1, d2;
        roll(&d1, &d2);
        
        if (tav.turn == WHITE)
        {
            if (wfirst)
                wfirst = false;
            else
            {
                double res = evaluate(tav, netw, WHITE);
                update_net(prew, res, netw);
            }
            prew = tav;
        }
        else
        {
            if (bfirst)
                bfirst = false;
            else
            {
                double res = evaluate(tav, netb, BLACK);
                update_net(preb, res, netw);
            }
            preb = tav;
        }
        
		if (tav.turn == WHITE)
			tav = choose_next(tav, netw, d1, d2);
		else
			tav = choose_next(tav, netb, d1, d2);
    }
    double resw = evaluate(tav, netw, tav.turn);
    update_net(prew, resw, netw, tav.turn);
    double resb = evaluate(tav, netb, tav.turn);
	update_net(preb, resb, netb, tav.turn);
    //if (rand() % 100 ==0)
    //   printf("\t%lf %lf\n",resw,resb);
    
    
}