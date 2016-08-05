#include "tavla.h"

tavla::tavla()
{
    for (int i = 0; i < 2; i++)
    {
        this->checkers[i][6] = 5;
        this->checkers[i][8] = 3;
        this->checkers[i][13] = 5;
        this->checkers[i][24] = 2;
    }
    this->turn = WHITE;
}

tavla::tavla(const tavla& other)
{
    for (int i = 0; i < 2; i++)
     for (int k = 0; k < 26; k++)
     {
         this->checkers[i][k] = other.checkers[i][k];
     }
    this->turn = other.turn;
}

tavla::~tavla()
{
}

bool tavla::is_valid()
{
    int sum0 = 0, sum1 = 0;
    for (int i = 0; i < 26; i++)
    {
        sum0 += checkers[0][i];
        sum1 += checkers[1][i];
        if (checkers[0][i] < 0 || checkers[1][i] < 0)
            return false;
    }
    if (sum0 != NUMCHECKERS || sum1 != NUMCHECKERS)
        return false;
    for (int i = 1; i < 25; i++)
    {
        if (checkers[0][i] && checkers[1][25-i])
            return false;
    }
    
    return true;
}
bool tavla::is_endgame(int s)
{
    int sum = 0;
    for (int i = 0; i < 7; i++)
    {
        sum += checkers[s][i];
    }
    if (sum == NUMCHECKERS)
        return true;
    else
        return false;
}
bool tavla::is_hit(int s)
{
    return checkers[s][25] != 0;
}
bool tavla::is_end()
{
    if (checkers[0][0] == NUMCHECKERS || checkers[1][0] == NUMCHECKERS)
        return true;
    else
        return false;
}
int tavla::get_winner()
{
    if (!is_end())
        return -1;
    else if (checkers[0][0] == NUMCHECKERS)
        return WHITE;
    else if (checkers[1][0] == NUMCHECKERS)
        return BLACK;
    
}
std::string tavla::str()
{
    
}
void tavla::next_states(int d1, int d2, std::vector<tavla>& vec)
{
    std::set<tavla> s0, s1;
    if (d1 == d2)
    {
        this->next_die(d1, s0);
        for (int i = 1; i < 4; i++)
        {
            if (s0.empty())
                break;
            for (tavla t:s0)
                t.next_die(d1, s1);
            swap(s0, s1);
            s1.clear();
        }
    }
    else
    {
        this->next_die(d1, s0);
        for (tavla t:s0)
            t.next_die(d2, s1);
        swap(s0, s1);
        s1.clear();
        
        this->next_die(d2, s1);
        for (tavla t:s1)
            t.next_die(d1, s0);
        s1.clear();
    }
    if (s0.empty())
    {
        vec.clear();
        tavla nt(*this);
        nt.turn = 1-this->turn;
        vec.push_back(nt);
    }
    else
    {
        vec.clear();
        for (tavla t:s0)
        {
            t.turn = 1-this->turn;
            vec = std::vector<tavla>(s0.begin(), s0.end());
        }
    }
}
void tavla::next_die(int die, std::set<tavla>& stav)
{
    if (is_end())
        return;
    if (is_hit(turn))
    {
        if (checkers[1-turn][die] > 1)
            return;
        else
        {
            tavla nval(*this);
            nval.checkers[turn][25] -= 1;
            nval.checkers[turn][25-die] += 1;
            nval.checkers[1-turn][25] += nval.checkers[1-turn][die];
            nval.checkers[1-turn][die] = 0;
            stav.insert(nval);
        }
    }
    else
    {
        if (is_endgame(turn))
        {
            int msum = 0;
            for (int i = die; i < 7; i++)
                msum += checkers[turn][i];
            if (checkers[turn][die] >= 1)
            {
                tavla nval(*this);
                nval.checkers[turn][die] -= 1;
                nval.checkers[turn][0] += 1;
                stav.insert(nval);
            }
            else if (msum == 0)
            {
                int ind = 0;
                while (ind != 0 && checkers[turn][ind] == 0)
                    ind--;
                if (ind != 0)
                {
                    tavla nval(*this);
                    nval.checkers[turn][ind] -= 1;
                    nval.checkers[turn][0] += 1;
                    stav.insert(nval);
                }
            }
        }
        //MAIN GAME
        for (int i = die + 1; i < 25; i++)
        {
            if (checkers[turn][i] > 0 && checkers[1-turn][25-(i-die)] <= 1)
            {
                tavla nval(*this);
                nval.checkers[turn][i] -= 1;
                nval.checkers[turn][i-die] += 1;
                nval.checkers[1-turn][25] += nval.checkers[1-turn][25-(i-die)];
                nval.checkers[1-turn][25-(i-die)] = 0;
                stav.insert(nval);
            }
        }
    }
}
bool tavla::operator<(const tavla& rhs) const 
{
    
}
bool tavla::operator==(const tavla& rhs) const 
{
    
}