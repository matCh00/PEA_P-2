#include "Time.h"



Time::Time() {

}



Time::~Time() {

}



void Time::start() {

    tstart = steady_clock::now();
}



void Time::stop() {

    tstop = steady_clock::now();
    measurement = tstop - tstart;
}



double Time::read() {

    return measurement.count();
}