#include "learn.h"

const int LRATE = 0.7;

double evaluate(const tavla& t, const networkbase& net, int turn)
{
    if (t.is_end())
    {
        //printf("KEKEKEKEK\n");
        //if (t.get_winner() != turn)
        //    printf("AYYYYLMAOOOO\n");
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
        double nval = evaluate(t, net, 1-t.turn);
        if (nval > maxval)
            best = t;
    }
    
    if (maxval < -1)
    {
        return tav;
    }
    
    return best;
}

void update_net(const tavla& tav, double val, network& net, double lrate = LRATE)
{
    double input[INSIZE];
    tav.to_vector(input);
    //printf("xx%d\n",net.nono);
    net.update(input, val);
}

void learn_game(network& net)
{
    tavla tav;
    
    tavla pret = tav;
    bool first = true;
    while (!tav.is_end())
    {
        if (tav.turn == WHITE)
        {
            if (first)
                first = false;
            else
            {
                double res = evaluate(tav, net, WHITE);
                update_net(pret, res, net);
                //printf("%lf %lf\n",evaluate(tav, net, WHITE),evaluate(pret, net, WHITE));
                pret = tav;
            }
        }
        int d1, d2;
        roll(&d1, &d2);
        
        tav = choose_next(tav, net, d1, d2);
    }
    if (!first)
    {
        //printf("%d\n",tav.get_winner());
        update_net(pret, evaluate(tav, net, WHITE), net);
        update_net(tav, evaluate(tav, net, WHITE), net);
    }
}