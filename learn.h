#ifndef LEARNH
#define LEARNH

#include "tavla.h"
#include "network.h"
#include "globals.h"

void learn_game(network& net);
tavla choose_next(tavla tav, const networkbase& net, int d1, int d2);
double evaluate(const tavla& t, const networkbase& net, int turn = 0,bool toto=false);

#endif