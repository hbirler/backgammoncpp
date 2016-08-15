#pragma once

#include "network.h"
#include "tavla.h"
#include "myrandom.h"

class buzinessman :public evaluatorbase
{
public:
	buzinessman(bool random = true);
	buzinessman(double p, double b, double t, double o);
	virtual ~buzinessman() {}

	double evaluate(const double input[INSIZE]) const;
	void update(const double input[INSIZE], double output);

	double p, b, t, o;
};