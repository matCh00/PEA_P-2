#include "Randomize.h"



int Randomize::random_mt19937(int min, int max) {

    static random_device rd;
    static mt19937 rng{rd()};
    static uniform_int_distribution<int> uid(min,max);

    return uid(rng);
}




int Randomize::random_engine(int min, int max) {

    static random_device rd;
    static default_random_engine dre(rd());
    static uniform_int_distribution<> uid(min, max);

    return uid(dre);
}