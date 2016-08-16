#include "minimax.h"

using namespace std;

struct sdata
{

};
struct tmove
{
	char from;
	char to;
	tmove(char from = 0, char to = 0) {
		this->from = from;
		this->to = to;
	}
};
struct tmoves
{
	tmove m[2];
	double e[2];
};
/*
tavla minimax(tavla tav, const evaluatorbase& net, int d1, int d2)
{
	vector<tmove> moves;


}
inline char domove(tavla& tav, char from, char to) {
	tav.checkers[tav.turn][from] -= 1;
	tav.checkers[tav.turn][to] += 1;
	char back = tav.checkers[1 - tav.turn][25 - to];
	if (to != 0)
	{
		tav.checkers[1 - tav.turn][25] += back;
		tav.checkers[1 - tav.turn][25 - to] = 0;
	}
	return back;
}

inline void undomove(tavla& tav, char from, char to, char back) {
	tav.checkers[tav.turn][from] += 1;
	tav.checkers[tav.turn][to] -= 1;
	//char back = tav.checkers[1 - tav.turn][25 - to];
	if (to != 0)
	{
		tav.checkers[1 - tav.turn][25] -= back;
		tav.checkers[1 - tav.turn][25 - to] = back;
	}
}

tmoves rec0(tavla& tav, const evaluatorbase& net, tmoves& moves, int d1, int d2, int depth = 0);
tmoves rec1(tavla& tav, const evaluatorbase& net, tmoves& moves, int d1, int d2, int depth = 0);
tmoves rec2(tavla& tav, const evaluatorbase& net, tmoves& moves, int d1, int d2, int depth = 0);

tmoves rec0(tavla& tav, const evaluatorbase& net, tmoves& moves, int d1, int d2, int depth = 0) {
	char die = 0;

	tmoves mmax;


	if (tav.is_end())
	{
		//saveop
		int winner = tav.get_winner();
		mmax.e[winner] = 1.0;
		mmax.e[1 - winner] = 0.0;
	}
	else if (tav.is_hit(tav.turn))
	{
		if (tav.checkers[1 - tav.turn][die] > 1)
		{
			//saveop
			mmax = rec2(tav, net, moves, d1, d2, depth + 1);
			mmax.m[0] = mmax.m[1] = tmove();
		}
		else
		{
			char back = domove(tav, 25, 25 - die);
			//saveop
			undomove(tav, 25, 25 - die, back);
		}
	}
	else
	{
		if (tav.is_endgame(tav.turn))
		{
			int msum = 0;
			for (int i = die; i < 7; i++)
				msum += tav.checkers[tav.turn][i];
			if (tav.checkers[tav.turn][die] >= 1)
			{
				char back = domove(tav, die, 0);
				//saveop
				undomove(tav, die, 0, back);
			}
			else if (msum == 0)
			{
				int ind = die;
				while (ind != 0 && tav.checkers[tav.turn][ind] == 0)
					ind--;
				if (ind != 0)
				{
					char back = domove(tav, ind, 0);
					//saveop
					undomove(tav, ind, 0, back);
				}
			}
		}
		//MAIN GAME
		for (int i = die + 1; i < 25; i++) 
		{
			if (tav.checkers[tav.turn][i] > 0 && tav.checkers[1 - tav.turn][25 - (i - die)] <= 1)
			{
				char back = domove(tav, i, i - die);
				//saveop
				undomove(tav, i, i - die, back);
			}
		}
	}
}

tmoves rec(tavla& tav, const evaluatorbase& net, tmoves& moves, int d1, int d2, int depth = 0, int pdepth = 0) {
	static double input[INSIZE];

	int dice = 0;
	if (pdepth == 0)
		dice = d1;
	else if (pdepth == 1)
		dice = d2;
	else if (pdepth == 2)
	{
		//roll dice
	}

	if (tav.is_end())
	{
		tavla nval(tav);
		stav.insert(nval);
		return;
	}
	if (tav.is_hit(tav.turn))
	{
		if (tav.checkers[1 - tav.turn][die] > 1)
			return;
		else
		{
			tavla nval(tav);
			nval.checkers[tav.turn][25] -= 1;
			nval.checkers[tav.turn][25 - die] += 1;
			nval.checkers[1 - tav.turn][25] += nval.checkers[1 - tav.turn][die];
			nval.checkers[1 - tav.turn][die] = 0;
			stav.insert(nval);
		}
	}
	else
	{
		if (tav.is_endgame(tav.turn))
		{
			int msum = 0;
			for (int i = die; i < 7; i++)
				msum += checkers[tav.turn][i];
			if (tav.checkers[tav.turn][die] >= 1)
			{
				tavla nval(tav);
				nval.checkers[tav.turn][die] -= 1;
				nval.checkers[tav.turn][0] += 1;
				stav.insert(nval);
			}
			else if (msum == 0)
			{
				int ind = die;
				while (ind != 0 && tav.checkers[tav.turn][ind] == 0)
					ind--;
				if (ind != 0)
				{
					tavla nval(tav);
					nval.checkers[tav.turn][ind] -= 1;
					nval.checkers[tav.turn][0] += 1;
					stav.insert(nval);
				}
			}
		}
		//MAIN GAME
		for (int i = die + 1; i < 25; i++)
		{
			if (tav.checkers[tav.turn][i] > 0 && tav.checkers[1 - tav.turn][25 - (i - die)] <= 1)
			{
				tavla nval(tav);
				nval.checkers[tav.turn][i] -= 1;
				nval.checkers[tav.turn][i - die] += 1;
				nval.checkers[1 - tav.turn][25] += nval.checkers[1 - tav.turn][25 - (i - die)];
				nval.checkers[1 - tav.turn][25 - (i - die)] = 0;
				stav.insert(nval);
			}
		}
	}
}*/