#include "tavla.h"

int randint(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

void roll(int* d1, int* d2)
{
    *d1 = randint(1,6);
    *d2 = randint(1,6);
}


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

bool tavla::is_valid()  const
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
bool tavla::is_endgame(int s)  const
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
bool tavla::is_hit(int s)  const
{
    return checkers[s][25] != 0;
}
bool tavla::is_end()  const
{
    if (checkers[0][0] == NUMCHECKERS || checkers[1][0] == NUMCHECKERS)
        return true;
    else
        return false;
}
int tavla::get_winner()  const
{
    if (!is_end())
        return -1;
    else if (checkers[0][0] == NUMCHECKERS)
        return WHITE;
    else if (checkers[1][0] == NUMCHECKERS)
        return BLACK;
    
}
std::string tavla::str()  const
{
    using namespace std;
    ostringstream os;
    os << endl << hash<tavla>()(*this) << endl;
    
    for (int i = 0; i < 13; i++)
        os << "#";
    os << "W" << checkers[0][0] << ":" << checkers[0][25] << " " <<
          "B" << checkers[1][0] << ":" << checkers[1][25] << endl;
    
    
    
    for (int k = 1; ; k++)
    {
        bool tob = true;
        
        for (int i = 0; i < 12; i++)
        {
            if (i == 6)
                os << "#";
            if (checkers[0][13+i] >= k)
            {
                os << "W";
                tob = false;
            }
            else if (checkers[1][12-i] >= k)
            {
                os << "B";
                tob = false;
            }
            else
                os << " ";
        }
        
        os << endl;
        if (tob)
            break;
    }
    
    int mmax = 0;
    for (int i = 1; i <= 12; i++)
    {
        mmax = max(mmax, checkers[0][i]);
        mmax = max(mmax, checkers[1][25-i]);
    }
    
    for (int k = mmax; k > 0; k--)
    {
        for (int i = 0; i < 12; i++)
        {
            if (i == 6)
                os << "#";
            if (checkers[0][12-i] >= k)
                os << "W";
            else if (checkers[1][13+i] >= k)
                os << "B";
            else
                os << " ";
        }
        os << endl;
    }
    for (int i = 0; i < 13; i++)
        os << "#";
    os << ((turn == WHITE)?"W":"B");
    os << endl;
    return os.str();
}
void tavla::next_states(int d1, int d2, std::vector<tavla>& vec) const
{
    std::unordered_set<tavla> s0, s1;
    if (d1 == d2)
    {
        this->next_die(d1, s0);
        for (int i = 1; i < 4; i++)
        {
            if (s0.empty())
                break;
            for (auto& t:s0)
                t.next_die(d1, s1);
            swap(s0, s1);
            s1.clear();
        }
    }
    else
    {
        this->next_die(d1, s0);
        for (auto& t:s0)
            t.next_die(d2, s1);
        swap(s0, s1);
        s1.clear();
        
        this->next_die(d2, s1);
        for (auto& t:s1)
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
        for (auto& t:s0)
        {
            tavla nt(t);
            nt.turn = 1-turn;
            vec.push_back(nt);
        }
    }
}
void tavla::next_die(int die, std::unordered_set<tavla>& stav) const
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
                int ind = die;
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
void tavla::to_vector(double output[INSIZE], bool flip) const
{
    for (int i = 0; i < INSIZE; i++)
        output[i] = 0;
    
    for (int i = 0; i < 24; i++)
    {
        for (int k = 0; k < checkers[flip][i+1]; k++)
        {
            output[i*8 + k] = (k<3)?1:(checkers[flip][i+1]-3)/2;
        }
        for (int k = 0; k < checkers[!flip][i+1]; k++)
        {
            output[i*8 + 4 + k] = (k<3)?1:(checkers[!flip][i+1]-3)/2;
        }
    }
    output[192] = checkers[flip][25] / 2;
    output[193] = checkers[!flip][25] / 2;
    output[194] = checkers[flip][0] / 15;
    output[195] = checkers[!flip][0] / 15;
    output[196] = turn == flip;
    output[197] = turn == !flip;
}
bool tavla::operator<(const tavla& other) const 
{
    for (int i = 0; i < 26; i++)
    {
        if (this->checkers[i] < other.checkers[i])
            return true;
    }
    if (this->turn < other.turn)
        return true;
    
    return false;
}
bool tavla::operator==(const tavla& other) const 
{
    for (int i = 0; i < 26; i++)
    {
        if (this->checkers[0][i] != other.checkers[0][i])
            return false;
        if (this->checkers[1][i] != other.checkers[1][i])
            return false;
    }
    if (this->turn != other.turn)
        return false;
    return true;
}


std::size_t std::hash<tavla>::operator()(const tavla& k) const
{
    std::size_t seed = 52;
    for(int i = 0; i < 26; i++) {
        seed ^= k.checkers[0][i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= k.checkers[1][i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    seed ^= k.turn + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}