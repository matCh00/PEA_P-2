#include "Timer.h"



Timer::Timer() {

}



Timer::~Timer() {

}



void Timer::start() {

    LARGE_INTEGER l_int;

    QueryPerformanceFrequency(&l_int);
    frequency = double(l_int.QuadPart);

    QueryPerformanceCounter(&l_int);
    counter = l_int.QuadPart;
}



double Timer::stop() {

    LARGE_INTEGER l_int;
    QueryPerformanceCounter(&l_int);
    return double(l_int.QuadPart - counter) / frequency;
}