// funkcje losujące

#ifndef PEA_P_1_RANDOMIZE_H
#define PEA_P_1_RANDOMIZE_H

#include <random>
#include <iostream>

using namespace std;


class Randomize {

public:

    // ze stackoverflow.com
    static int random_mt19937(int min, int max);
};


#endif
