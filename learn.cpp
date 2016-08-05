#include "learn.h"

const int LRATE = 0.7;

double evaluate(const tavla& t, const networkbase& net, int turn)
{
    if (t.is_end())
        return t.get_winner() == turn;
    
    double output[INSIZE];
    t.to_vector(output, turn);
    
    double out = net.evaluate(output);
    
    return out;
}

tavla choose_next(tavla tav, networkbase& net, int d1, int d2)
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
        return tav;
    
    return best;
}

void update_net(const tavla& tav, double val, networkbase& net, double lrate = LRATE)
{
    double input[INSIZE];
    tav.to_vector(input);
    net.update(input, val);
}

void learn_game(networkbase& net)
{
    tavla tav;
    
    const tavla& pret = tav;
    bool first = true;
    while (!tav.is_end())
    {
        if (tav.turn == WHITE)
        {
            if (!first)
                first = false;
            else
            {
                update_net(pret, evaluate(tav, net, WHITE), net);
            }
        }
        int d1, d2;
        roll(&d1, &d2);
        
        tav = choose_next(tav, net, d1, d2);
    }
    if (!first)
        update_net(pret, evaluate(tav, net, WHITE), net);
}