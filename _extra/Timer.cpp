#include "Timer.h"



Timer::Timer() {

}



Timer::~Timer() {

}



void Timer::start() {

    tstart = steady_clock::now();
}



void Timer::stop() {

    tstop = steady_clock::now();
    measurement = tstop - tstart;
}



double Timer::read() {

    return measurement.count();
}