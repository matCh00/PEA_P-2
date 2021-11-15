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
    int stopTime;

    // limit iteracji - liczba iteracji bez poprawy globalnego minimum
    int iterations;

    // dzielnik kadencji - liczba przez którą jest dzielona kadencja w wrazie znalezienia globalnego minimum (INTENSYFIKACJA)
    int cadenceDivider;

    // liczba wierzchołków losowana przy generowaniu nowej ścieżki
    int nodesAmount;

    // typ sąsiedztwa (
    int neighborhoodType;

    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int matrixSize;

    // globalnie optymalna ścieżka
    vector <unsigned int>bestRoute;

    // aktualna ścieżka
    vector <unsigned int>currentRoute;

    // globalna funkcja celu
    int globalOptimum;

    // lokalna funkcja celu
    int currentOptimum;

    // aktualna kadencja
    int currentTabuCadence;

    // lista ostatnio wykonanych ruchów
    vector<vector<unsigned int>> tabuList;

    // generowanie początkowej ścieżki - algorytm zachłanny
    // nie dokonuje oceny czy w kolejnych krokach jest sens wykonywać dane działanie
    // dokonuje decyzji lokalnie optymalnej, kontynuując rozwiązanie podproblemu wynikającego z podjętej decyzji
    int getInitialGreedy(vector < unsigned >&route);
    int getInitialGreedyAndRandom(vector < unsigned >&route);
    void cleanTabuList();

    // przeszukiwanie sąsiedztwa
    // odwrócenie kolejnosci między wierzchołkami   reverse(4,1): <0,3,4,2,5,1,0> -> <0,3,1,5,2,4,0>
    int getBestNeighborhoodReverse(int &bestI, int &bestJ, vector <unsigned> currentRoute);

    // odwrócenie kolejności
    void reverseVector(int a, int b, vector <unsigned>& currentRoute);

    // sprawdzenie kosztu
    int calculateReverse(int i, int j, vector <unsigned> currentRoute);

    // przeszukiwanie sąsiedztwa
    // zamiana miejscami wierzchołków   swap(4,1): <0,3,4,2,5,1,0> -> <0,3,1,2,5,4,0>
    int getBestNeighborhoodSwap(int &bestI, int &bestJ, vector <unsigned> currentRoute);

    // zamiana miejscami
    void swapVector(int a, int b, vector <unsigned>& currentRoute);

    // sprawdzenie kosztu
    int calculateSwap(int i, int j, vector <unsigned> currentRoute);


public:

    // konstruktor
    TabuSearch();

    // destruktor
    ~TabuSearch();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    int algorithmTabuSearch(vector<vector<int>> originalMatrix, vector<unsigned int> &bestPath);

    // ustawienia Tabu Search
    void settingsTabuSearch(int a, int b, int c, int d, int e, int g);
};


#endif
