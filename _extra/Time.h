// mierzenie czasu w algorytmach

#ifndef PEA_P_2_TIME_H
#define PEA_P_2_TIME_H

#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;


class Time {

private:

    // pomiar
    duration<double> measurement;

    // początek
    time_point<steady_clock> tstart;

    // koniec
    time_point<steady_clock> tstop;

public:

    // konstruktor
    Time();

    // destruktor
    ~Time();

    // początek pomiaru
    void start();

    // koniec pomiaru
    void stop();

    // odczyt pomiaru
    double read();
};


#endif
