// menu projektu

#ifndef PEA_P_1_MENU_H
#define PEA_P_1_MENU_H

#include "../_efficiency/Tests.h"

using namespace std;



class Menu {

private:

    // graf
    Graph* graph;

    // początkowa temperatura
    double maxTemp;

    // minimalna temperatura
    double minTemp;

    // czas wykonywania
    time_t timeSA;

    // kadencja
    int cadence;

    // dzielnik kadencji (intensyfikacja)
    int divCadence;

    // czas wykonania
    time_t timeTS;


public:

    // konstruktor
    Menu();

    // destruktor
    ~Menu();

    // start
    void startMenu();
};


#endif