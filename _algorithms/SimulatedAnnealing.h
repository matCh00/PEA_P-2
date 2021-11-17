/*
 *  algorytm symulowanego wyżarzania
 */

#ifndef PEA_P_2_SIMULATEDANNEALING_H
#define PEA_P_2_SIMULATEDANNEALING_H

#include "../_structures/Graph.h"

using namespace std;
using namespace chrono;


class SimulatedAnnealing {

private:

    // czas działania algorytmu
    int stopTime;

    // typ sąsiedztwa
    int neighborhoodType;

    // minimalna temperatura
    double minTemperature;


    // początkowa temperatura
    double initialTemperature;

    // limit iteracji
    int iterationsLimit;

    // współczynnik chłodzenia
    double cooling;



    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int matrixSize;

    // globalnie optymalna ścieżka
    vector<unsigned int> bestRoute;

    // globalna funkcja celu
    int globalOptimum;

    // lokalna funkcja celu
    int currentOptimum;



    // generowanie początkowej ścieżki i zwrócenie lokalnego minimum
    // algorytm zachłanny nie dokonuje oceny czy w kolejnych krokach jest sens wykonywać dane działanie
    // dokonuje decyzji lokalnie optymalnej, kontynuując rozwiązanie podproblemu wynikającego z podjętej decyzji
    int getInitialGreedy(vector<unsigned> &route);

    // sprawdzenie kosztu
    int calculateReverse(int i, int j, vector<unsigned> &currentRoute);

    // sprawdzenie kosztu
    int calculateSwap(int i, int j, vector<unsigned> &currentRoute);

    // przetasowanie ścieżki
    int reshufflePath(vector <unsigned>& shuffled, vector <unsigned>&currentRoute);

    // funkcja prawdopodobienstwa - uproszczonego algorytmu Metropolisa
    int calculateProbability(int newCost, int oldCost, double temperature);




    // liczenie kosztu ścieżki
    int countPath(vector<int> &path);

    // tworzenie permutacji wierzchołków
    void createPermutation(vector<int> &permutation);

    // liczenie prawdopodobieństwa
    bool countProbability(int length1, int length2, double temperature);


public:

    // konstruktor
    SimulatedAnnealing();

    // destruktor
    ~SimulatedAnnealing();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    int algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<unsigned int> &bestPath);

    // ustawienia Tabu Search
    void settingsSimulatedAnnealing(int stopTime, int neighborhoodType);
};


#endif
