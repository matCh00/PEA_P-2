/*
 * Algorytm bazuje na dynamicznej zmianie sąsiedztwa danego rozwiązania i szukaniu lokalnie najlepszych rozwiązań.
 * Podstawą algorytmu jest zapamiętywanie ruchów na liście tabu. Zapisywanie ruchów niedozwolonych w tabu pozwala na
 * odrzucenie rozwiązań niedawno sprawdzanych zwiększając obszar przeszukiwania, co skutkuje większą możliwością
 * wyjścia z minimum lokalnego kosztem dokładności algorytmu.
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
    int divideCadence;

    // intensyfikacja - wieksza dokładność przeszukiwania (krótka kadencja)
    // duże ryzyko wpadnięcia w cykl w pobliżu lokalnego minimum
    bool intensification;

    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int matrixSize;

    // optymalna ścieżka
    vector<int> bestRoute;

    // aktualna ścieżka
    vector<int> currentRoute;

    // najmniejszy znaleziony koszt
    int globalOptimum;

    // lokalnie najmniejszy znaleziony koszt
    int currentOptimum;

    // aktualna kadencja
    int currentCadence;

    // lista tabu
    // vector< wierzchołek1, wierzchołek2, kadencja >
    vector<vector<int>> tabuList;

    // znalezienie pierwszego rozwiązania
    // algorytm zachłanny nie dokonuje oceny czy w kolejnych krokach jest sens wykonywać dane działanie
    // dokonuje decyzji lokalnie optymalnej, kontynuując rozwiązanie podproblemu wynikającego z podjętej decyzji
    int findInitialSolution(vector<int> &route);

    // przeszukiwanie sąsiedztwa
    // szukanie ruchu prowadzącego do najlepszego sąsiada
    // i nienależącego do listy tabu, chyba że spełnia kryterium aspiracji
    int searchNeighborhood(int &bestI, int &bestJ, vector<int> &currentRoute);

    // obliczenie balansu po obróceniu ścieżki względem i oraz j
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
