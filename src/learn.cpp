#include "learn.h"

const int LRATE = 0.7;

double evaluate(const tavla& t, const evaluatorbase& net, int turn)
{
    if (t.is_end())
    {
        //printf("KEKEKEKEK\n");
        //if (t.get_winner() == turn)
        //    printf("AYYYYLMAOOOO %d %d\n",t.get_winner(),turn);
        return t.get_winner() == turn;
    }
    
    double output[INSIZE];
    t.to_vector(output, turn);
    
    double out = net.evaluate(output);
    
    return out;
}

tavla choose_next(tavla tav, const evaluatorbase& net, int d1, int d2)
{
    std::vector<tavla> vec;
    tav.next_states(d1, d2, vec);
    
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

void update_net(const tavla& tav, double val, network& net, int turn = 0)
{
    double input[INSIZE];
    tav.to_vector(input, turn);
    //printf("xx%d\n",net.nono);
    net.update(input, val);
}

void learn_game(network& net)
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
                double res = evaluate(tav, net);
                //if (rand() % 1000 == 0)
                //    printf("%lf %lf\n",evaluate(prew, net, WHITE),evaluate(tav, net, WHITE));
                update_net(prew, res, net);
            }
            prew = tav;
        }
        else
        {
            if (bfirst)
                bfirst = false;
            else
            {
                double res = evaluate(tav, net);
                update_net(preb, res, net);
            }
            preb = tav;
        }
        
        tav = choose_next(tav, net, d1, d2);
    }
    double resw = evaluate(tav, net);
    update_net(prew, resw, net);
    //double resb = evaluate(tav, net, BLACK);
    //update_net(preb, resb, net,BLACK);
    //if (rand() % 100 ==0)
    //   printf("\t%lf %lf\n",resw,resb);
    
    
}