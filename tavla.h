#include <string>
#include <set>
#include <vector>
#include <cmath>
#include <utility>


enum side
{
    WHITE = 0,
    BLACK = 1
};

const int NUMCHECKERS = 15;

void roll(int* d1, int* d2);

class tavla
{
public:
    tavla();
    tavla(const tavla& other);
    ~tavla();
    bool is_valid();
    bool is_endgame(int s);
    bool is_hit(int s);
    bool is_end();
    int get_winner();
    std::string str();
    void next_states(int d1, int d2, std::vector<tavla>& vec);
    void next_die(int d1, std::set<tavla>& stav);
    bool operator<(const tavla& rhs) const ;
    bool operator==(const tavla& rhs) const ;
    int turn;
private:
    int checkers[2][26];
};

