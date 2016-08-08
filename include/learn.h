#pragma once

#include "tavla.h"
#include "network.h"
#include "globals.h"

void learn_game(network& net);
tavla choose_next(tavla tav, const evaluatorbase& net, int d1, int d2);
double evaluate(const tavla& t, const evaluatorbase& net, int turn = 0);
