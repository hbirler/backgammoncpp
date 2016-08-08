#include "play.h"

using namespace std;

inline bool file_exists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

struct game_state
{
	tavla tav;
	int d1;
	int d2;
};

int play(int argc, char* argv[])
{
	network net;

	int net_ind = -1;

	string netpath = "./output/";
	if (file_exists(netpath + "network.bin"))
	{
		net = deserialize<network>(netpath + "network.bin");
		net_ind = net.no;
	}
	else
	{
		return 0;
	}

	
	bool illegal = false;
	int ed1, ed2;
	game_state retgame;

	if (argc == 0)
	{

	}

	roll(&retgame.d1, &retgame.d2);

	if (argc != 0)
	{
		game_state game;
		decode_16<game_state>(argv[0], &game);

		vector<tavla> next;
		game.tav.next_states(game.d1, game.d2, next);

		unordered_set<tavla> mt(next.begin(), next.end());

		tavla nmove = game.tav;

		//UPDATE NMOVE
		for (int i = 0; i < (argc - 1) / 2; i++)
		{
			int from = stoi(argv[i * 2 + 1]);
			int to = stoi(argv[i * 2 + 2]);

			if (from < 0 || to < 0 || from > 25 || to > 25)
			{
				nmove.checkers[0][0] = 25;
				break;
			}

			nmove.checkers[0][from]--;
			nmove.checkers[0][to]++;
			if (to != 0)
			{
				nmove.checkers[1][25] += nmove.checkers[1][25 - to];
				nmove.checkers[1][25 - to] = 0;
			}
		}
		nmove.turn = 1 - nmove.turn;
		//cout << "**********\n" << nmove.str() << "\n**********\n" << endl;

		if (mt.find(nmove) == mt.end())
		{
			illegal = true;
			retgame.tav = game.tav;
			retgame.d1 = game.d1;
			retgame.d2 = game.d2;
		}
		else
		{
			roll(&ed1, &ed2);
			retgame.tav = choose_next(nmove, net, ed1, ed2);
		}
		
	}

	
	

	

	string retenc = encode_16<game_state>(retgame);

	cout << retenc << "\n";
	if (illegal)
		cout << "ILLEGAL MOVE !!!" << "\n";
	else if (argc != 0)
		cout << "Enemy Dice: " << ed1 << " " << ed2 << "\n";
	else
		cout << "Begin!" << "\n";

	cout << "\n" << retgame.tav.str_pretty() << "\n";

	cout << "Your Dice: " << retgame.d1 << " " << retgame.d2 << "\n";
	

	return 0;
}