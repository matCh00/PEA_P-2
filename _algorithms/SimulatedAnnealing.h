/*
 *  algorytm symulowanego wyżarzania
 */

#ifndef PEA_P_2_SIMULATEDANNEALING_H
#define PEA_P_2_SIMULATEDANNEALING_H

#include "../_structures/Graph.h"

using namespace std;


class SimulatedAnnealing {

private:
    __int64 counter = 0;
    double frequency = 1;
    const double e = 2.718281828459;
    double min_temperature = 0.001;
    double solution = 0;
    int optimum = 0;
    int cities;
    vector<int> path;

    // początkowa temperatura
    double initialTemperature;

    // minimalna temperatura
    double minTemperature;

    // czas wykonania
    int stopTime;

    // limit iteracji
    int iterationsLimit;

    // współczynnik chłodzenia
    double cooling;

    // typ sąsiedztwa
    int neighborhoodType;

public:

    SimulatedAnnealing();
    ~SimulatedAnnealing();

    void setOptimum(int opt);

    //wyliczenie czasu końcowego
    double stop();
    //ustawienie danych potrzebnych do mierzenia czasu
    void start();

    vector<vector<int>> matrix;

    //obliczanie drogi pomiędzy miastami
    int route(vector<int> &perm);

    //losowanie
    void permutation(vector<int> &perm);

    //prawdopodobienstwo wybrania sasiedniego miasta
    bool probability(int length1, int length2, double temperature);

    //algorytm symulowanego wyrzazania
    int algorithmSimulatedAnnealing(vector<vector<int>> matrix1, vector<int> &bestPath);

    void settingsSimulatedAnnealing(double initialTemperature, double minTemperature, time_t stopTime, int iterationsLimit, double cooling, int neighborhoodType);
};


#endif
