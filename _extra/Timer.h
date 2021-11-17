// mierzenie czasu w algorytmach

#ifndef PEA_P_2_TIMER_H
#define PEA_P_2_TIMER_H

#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;


class Timer {

private:

    // pomiar
    duration<double> measurement;

    // początek
    time_point<steady_clock> tstart;

    // koniec
    time_point<steady_clock> tstop;

public:

    // konstruktor
    Timer();

    // destruktor
    ~Timer();

    // początek pomiaru
    void start();

    // koniec pomiaru
    void stop();

    // odczyt pomiaru
    double read();
};


#endif
