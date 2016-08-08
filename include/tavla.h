#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <cstring>
#include <utility>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <stdint.h>
#include "myrandom.h"


#ifndef _INSIZE
#define _INSIZE
const int INSIZE = 198;
#endif

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
	tavla::tavla(double input[INSIZE]);
    tavla(const tavla& other);
    ~tavla();
    bool is_valid()  const;
    bool is_endgame(int s)  const;
    bool is_hit(int s)  const;
    bool is_end()  const;
    int get_winner()  const;
    std::string str()  const;
    void next_states(int d1, int d2, std::vector<tavla>& vec) const;
    void next_die(int d1, std::unordered_set<tavla>& stav) const;
    bool operator<(const tavla& rhs) const ;
    bool operator==(const tavla& rhs) const ;
    void to_vector(double output[INSIZE], bool flip=false) const;
    int turn;
	uint8_t checkers[2][26] = {{0}, {0}};
private:
    
};

namespace std {

    template <>
    struct hash<tavla>
    {
        std::size_t operator()(const tavla& k) const;
    };
}


std::ostream& operator<<(std::ostream &strm, const tavla &a);