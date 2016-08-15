#include "buzinessman.h"

buzinessman::buzinessman(bool random)
{
	if (!random)
	{
		this->p = 1.0;
		this->b = 1.0;
		this->t = 1.0;
		this->o = 1.0;
	}
	else 
	{
		this->p = randf();
		this->b = randf();
		this->t = randf();
		this->o = randf();
	}
}

buzinessman::buzinessman(double p, double b, double t, double o)
{
	this->p = p;
	this->b = b;
	this->t = t;
	this->o = o;
}

double buzinessman::evaluate(const double input[INSIZE]) const
{
	tavla tav(input);

	double retval = 0.0;

	double sumpos = 0.0;
	double avgpos = 0.0;

	for (int i = 0; i < 26; i++)
	{
		for (int k = 0; k < tav.checkers[0][i]; k++)
			sumpos += (26 - i)*(26 - i);
		for (int k = 0; k < tav.checkers[1][i]; k++)
			sumpos -= (26 - i)*(26 - i);
	}

	avgpos = sumpos / 15.0 / 10.0;

	double sb = 1.0;
	double sw = 1.0;
	for (int i = 19; i < 25; i++)
	{
		if (tav.checkers[0][i] >= 2)
			sw++;
		if (tav.checkers[1][i] >= 2)
			sb++;
	}
	double open = 0.0;
	for (int i = 0; i < 26; i++)
	{
		if (tav.checkers[0][i] == 1)
			open -= 1;
		if (tav.checkers[1][i] == 1)
			open += 0.5;
	}

	double broken = (- tav.checkers[0][25] * sb + tav.checkers[1][25] * sw) / 2.0;

	double taken = (tav.checkers[0][0] - tav.checkers[1][0]) / 7.5;

	retval = (p*avgpos + b*broken + t*taken + o*open) / (p + b + t + o) * 4;

	return sigmoid(retval); //-4 to 4
}

void buzinessman::update(const double input[INSIZE], double output) {}
