// mierzenie czasu w algorytmach

#ifndef PEA_P_2_TIMER_H
#define PEA_P_2_TIMER_H

#include <chrono>
#include <iostream>
#include <windows.h>

using namespace std;


class Timer {

private:

    // start
    long long int begin;

    // stop
    long long int end;

    // częstotliwość
    double frequency;


public:

    // konstruktor
    Timer();

    // destruktor
    ~Timer();

    // początek pomiaru
    void start();

    // koniec i odczyt pomiaru w [us]
    long long int stop();
};


#endif
