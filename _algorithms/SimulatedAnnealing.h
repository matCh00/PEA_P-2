/*
 *  algorytm symulowanego wyżarzania
 */

#ifndef PEA_P_2_SIMULATEDANNEALING_H
#define PEA_P_2_SIMULATEDANNEALING_H

#include "../_structures/Graph.h"

using namespace std;


class SimulatedAnnealing {

private:

    // początkowa temperatura
    double maxTemperature;

    // minimalna temperatura
    double minTemperature;

    // aktualna temperatura
    double currentTemperature;

    // czas wykonania
    time_t executionTime;

    // macierz
    vector<vector<int>> matrix;

    // liczba miast
    int matrixSize;

    // aktualnie optymalna ścieżka
    vector<int> path;

    // najmniejszy znaleziony koszt
    int bestCost;


    // limit iteracji
    int iterationsLimit;

    // typ sąsiedztwa
    int neighborhoodType;


    // obliczanie drogi
    int route(vector<int> &currentPath);

    // losowanie kolejności miast
    void permutation(vector<int> &currentPath);

    // prawdopodobienstwo wybrania sasiedniego miasta
    bool probability(int length1, int length2, double temperature);


public:

    // konstruktor
    SimulatedAnnealing();

    // destruktor
    ~SimulatedAnnealing();

    // algorytm Simulated Annealing
    int algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<int> &bestPath);

    // ustawienia Simulated Annealing
    void settingsSimulatedAnnealing(double initialTemperature, double minTemperature, time_t stopTime, int iterationsLimit, int neighborhoodType);
};


#endif
