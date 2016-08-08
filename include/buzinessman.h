#pragma once

#include "network.h"
#include "tavla.h"

class buzinessman :public evaluatorbase
{
public:
	virtual ~buzinessman() {}

	double evaluate(const double input[INSIZE]) const;
	void update(const double input[INSIZE], double output);
};