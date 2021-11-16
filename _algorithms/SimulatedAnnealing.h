/*
 *  algorytm symulowanego wyżarzania
 */

#ifndef PEA_P_2_SIMULATEDANNEALING_H
#define PEA_P_2_SIMULATEDANNEALING_H

#include "../_structures/Graph.h"

using namespace std;


class SimulatedAnnealing {

private:

    int optMin;
    int currentOptMin;
    int iterationsLimit;
    int intensificationDiv;
    int amountRandomNodes;
    bool algorithmType;
    int neighborhoodType;
    vector < unsigned >bestRoute;
    int **matrix;
    int matrixSize;
    vector< vector<unsigned> > tabuList;
    double initialTemperature;
    double cooling;
    double minTemperature;
    int iterations;


    // generowanie początkowej ścieżki i zwrócenie lokalnego minimum
    // algorytm zachłanny nie dokonuje oceny czy w kolejnych krokach jest sens wykonywać dane działanie
    // dokonuje decyzji lokalnie optymalnej, kontynuując rozwiązanie podproblemu wynikającego z podjętej decyzji
    int getInitialGreedy(vector<unsigned> &route);

    // przeszukiwanie sąsiedztwa
    // odwrócenie kolejnosci między wierzchołkami   reverse(4,1): <0,3,4,2,5,1,0> -> <0,3,1,5,2,4,0>
    int getBestNeighborhoodReverse(int &bestI, int &bestJ, vector<unsigned> &currentRoute);

    // odwrócenie kolejności
    void reverseVector(int a, int b, vector<unsigned> &currentRoute);

    // sprawdzenie kosztu
    int calculateReverse(int i, int j, vector<unsigned> &currentRoute);

    // przeszukiwanie sąsiedztwa
    // zamiana miejscami wierzchołków   swap(4,1): <0,3,4,2,5,1,0> -> <0,3,1,2,5,4,0>
    int getBestNeighborhoodSwap(int &bestI, int &bestJ, vector<unsigned> &currentRoute);

    // zamiana miejscami
    void swapVector(int a, int b, vector<unsigned> &currentRoute);

    // sprawdzenie kosztu
    int calculateSwap(int i, int j, vector<unsigned> &currentRoute);

    int reshufflePath(vector <unsigned>& shuffled, vector <unsigned>&currentRoute);
    int calculateProbability(int newCost, int oldCost, double temperature);


public:

    // konstruktor
    SimulatedAnnealing();

    // destruktor
    ~SimulatedAnnealing();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    int algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<unsigned int> &bestPath);

    // ustawienia Tabu Search
    void settingsSimulatedAnnealing();
};


#endif
