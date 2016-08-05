#ifndef LEARNH
#define LEARNH

#include "tavla.h"
#include "network.h"

void learn_game(networkbase& net);
tavla choose_next(tavla tav, networkbase& net, int d1, int d2);
double evaluate(const tavla& t, const networkbase& net, int turn = 0);

#endif