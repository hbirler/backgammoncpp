#include "buzinessman.h"

double buzinessman::evaluate(double input[INSIZE]) const
{
	tavla tav;
	for (int i = 0; i < 24; i++)
	{
		tav.checkers[0][i + 1] = tav.checkers[1][i + 1] = 0;
		for (int k = 0; k < 4; k++)
			tav.checkers[0][i + 1] += input[i * 8 + k];
		for (int k = 0; k < 4; k++)
			tav.checkers[1][i + 1] += input[i * 8 + 4 + k];

	}
	tav.checkers[0][25] = input[192] * 2.0;
	tav.checkers[1][25] = input[193] * 2.0;
	tav.checkers[0][0] = input[194] * 16.0;
	tav.checkers[1][0] = input[195] * 16.0;
	tav.turn = input[196] > input[197];

	double retval = 0.0;

	double sumpos = 0.0;
	double avgpos = 0.0;

	for (int i = 0; i < 26; i++)
	{
		for (int k = 0; k < tav.checkers[0][i]; k++)
			sumpos += i;
		for (int k = 0; k < tav.checkers[1][i]; k++)
			sumpos -= i;
	}

	avgpos = sumpos / 15.0;

	double sb = 0.0;
	double sw = 0.0;
	for (int i = 19; i < 25; i++)
	{
		if (tav.checkers[0][i] >= 2)
			sw++;
		if (tav.checkers[1][i] >= 2)
			sb++;
	}
	double broken = - tav.checkers[0][25] * sb + tav.checkers[1][25] * sw;

	double taken = (tav.checkers[0][0] - tav.checkers[1][0]) / 7.5;

	retval = avgpos + broken / 2.0 + taken;

	return sigmoid(retval); //-4 to 4
}

void buzinessman::update(double input[INSIZE], double output) {}
