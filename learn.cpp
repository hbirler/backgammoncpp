#include "learn.h"

const int LRATE = 0.7;

double evaluate(const tavla& t, const networkbase& net, int turn, bool toto)
{
    if (!toto && t.is_end())
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

tavla choose_next(tavla tav, const networkbase& net, int d1, int d2)
{
    std::vector<tavla> vec;
    tav.next_states(d1, d2, vec);
    
    tavla best = tav;
    double maxval = -1.0;
    
    for (auto& t:vec)
    {
        double nval = evaluate(t, net, tav.turn);
        if (nval > maxval)
            best = t;
    }
    
    if (maxval < -1)
    {
        return tav;
    }
    
    return best;
}

void update_net(const tavla& tav, double val, network& net, int turn = 0, double lrate = LRATE)
{
    double input[INSIZE];
    tav.to_vector(input, turn);
    //printf("xx%d\n",net.nono);
    net.update(input, val);
}

void learn_game(network& net)
{
    network_random dumb;
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
                double res = evaluate(tav, net, tav.turn);
                printf("%lf %lf\n",evaluate(prew, net, WHITE),evaluate(tav, net, WHITE));
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
                double res = evaluate(tav, net, tav.turn);
                update_net(preb, res, net);
            }
            preb = tav;
        }
        
        tav = choose_next(tav, net, d1, d2);
    }
    if (tav.turn == WHITE)
    {
        if (wfirst)
            wfirst = false;
        else
        {
            double res = evaluate(tav, net, tav.turn);
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
            double res = evaluate(tav, net, tav.turn);
            update_net(preb, res, net);
        }
        preb = tav;
    }
    
    
}