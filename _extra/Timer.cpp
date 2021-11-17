#include "Timer.h"



Timer::Timer() {

    begin = 0;
    end = 0;
}



Timer::~Timer() {

    begin = 0;
    end = 0;
}



long long int read_QPC() {

    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((long long int)count.QuadPart);
}



void Timer::start() {

    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    begin = read_QPC();
}



long long int Timer::stop() {

    end = read_QPC() - begin;
    return (1000000.0 * end) / frequency;
}