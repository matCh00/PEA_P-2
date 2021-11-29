/*
 *  algorytm przeszukiwania tabu
 */

#ifndef PEA_P_2_TABUSEARCH_H
#define PEA_P_2_TABUSEARCH_H

#include "../_structures/Graph.h"

using namespace std;


class TabuSearch {

private:

    // kadencja - liczba iteracji przez które element znajduje się na liście tabu
    int cadence;

    // czas działania algorytmu
    time_t executionTime;

    // dzielnik kadencji - liczba przez którą jest dzielona kadencja w wrazie znalezienia globalnego minimum (INTENSYFIKACJA)
    int divCadence;

    // intensyfikacja - wieksza dokładność przeszukiwania (krótka kadencja)
    // duże ryzyko wpadnięcia w cykl w pobliżu lokalnego minimum
    bool intensification;

    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int matrixSize;

    // globalnie optymalna ścieżka
    vector<int> bestRoute;

    // aktualna ścieżka
    vector<int> currentRoute;

    // globalna funkcja celu
    int globalOptimum;

    // lokalna funkcja celu
    int currentOptimum;

    // aktualna kadencja
    int currentTabuCadence;

    // lista ostatnio wykonanych ruchów
    vector<vector<int>> tabuList;

    // znalezienie lokalnego minimum i jego ścieżki
    // algorytm zachłanny nie dokonuje oceny czy w kolejnych krokach jest sens wykonywać dane działanie
    // dokonuje decyzji lokalnie optymalnej, kontynuując rozwiązanie podproblemu wynikającego z podjętej decyzji
    int findLocalMinimum(vector<int> &route);

    // szukanie najlepszego sąsiada
    // odwrócenie części ścieżki   reverse(4,1): <0,3,4,2,5,1,0> -> <0,3,1,5,2,4,0>
    int bestNeighborhood(int &bestI, int &bestJ, vector<int> &currentRoute);

    // obliczenie kosztu ścieżki
    int calculateAfterReverse(int i, int j, vector<int> &currentRoute);


public:

    // konstruktor
    TabuSearch();

    // destruktor
    ~TabuSearch();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    double algorithmTabuSearch(vector<vector<int>> originalMatrix, vector<int> &bestPath, int &bestCost);

    // ustawienia Tabu Search
    void settingsTabuSearch(int cadence, int divCadence, time_t stopTime);
};


#endif
