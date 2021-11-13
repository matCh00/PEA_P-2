// menu projektu

#ifndef PEA_P_1_MENU_H
#define PEA_P_1_MENU_H

#include "../_efficiency/Tests.h"

using namespace std;



class Menu {

private:

    // graf
    Graph* graph;


public:

    // konstruktor
    Menu();

    // destruktor
    ~Menu();

    // start
    void startMenu();
};


#endif