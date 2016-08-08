#pragma once

#include "network.h"
#include "tavla.h"

class buzinessman :public evaluatorbase
{
public:
	virtual ~buzinessman() {}

	double evaluate(double input[INSIZE]) const;
	void update(double input[INSIZE], double output);
};