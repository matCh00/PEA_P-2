// mierzenie czasu w algorytmach

#ifndef PEA_P_2_TIMER_H
#define PEA_P_2_TIMER_H

#include <chrono>
#include <iostream>
#include <windows.h>

using namespace std;
using namespace chrono;


class Timer {

private:

    // licznik
    long long counter;

    // częstotliwość
    double frequency;


public:

    // konstruktor
    Timer();

    // destruktor
    ~Timer();

    // początek pomiaru
    void start();

    // koniec pomiaru
    double stop();
};


#endif
