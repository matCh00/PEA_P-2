#include "Randomize.h"



static random_device rd;
static mt19937 rng{rd()};


int Randomize::random_mt19937(int min, int max) {

    static uniform_int_distribution<int> uid(min,max);
    return uid(rng);
}