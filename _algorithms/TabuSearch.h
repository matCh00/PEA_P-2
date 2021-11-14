/*
 *  algorytm przeszukiwania tabu
 */

#ifndef PEA_P_2_TABUSEARCH_H
#define PEA_P_2_TABUSEARCH_H

#include "../_structures/Graph.h"

using namespace std;


class TabuSearch {

private:

    int tabuCadence;
    unsigned tabuTime;
    int iterationsLimit;
    int intensificationDiv;
    int amountRandomNodes;
    int neighborhoodType;

    int **matrix;
    int matrixSize;
    vector < unsigned >bestRoute;
    int optMin;
    int currentOptMin;
    int currentTabuCadence;
    vector< vector<unsigned> > tabuList;

    void copyMatrix(int **macierz);
    int getInitialGreedy(vector < unsigned >&route);
    int getInitialGreedyAndRandom(vector < unsigned >&route);
    void clearParameters(vector <unsigned> currentRoute);
    void cleanTabuList();

    int getBestNeighborhoodInsert(int &bestI, int &bestJ, vector <unsigned> currentRoute);
    int getBestNeighborhoodReverse(int &bestI, int &bestJ, vector <unsigned> currentRoute);
    int getBestNeighborhoodSwap(int &bestI, int &bestJ, vector <unsigned> currentRoute);
    void reverseVector(int a, int b, vector <unsigned>& currentRoute);
    void insertVector(int a, int b, vector <unsigned>& currentRoute);
    void swapVector(int a, int b, vector <unsigned>& currentRoute);
    void calculateInsert(int i, int j, int &balance, vector <unsigned> currentRoute);
    void calculateReverse(int i, int j, int &balance, vector <unsigned> currentRoute);
    void calculateSwap(int i, int j, int &balance, vector <unsigned> currentRoute);


public:

    // konstruktor
    TabuSearch();

    // destruktor
    ~TabuSearch();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    void algorithmTabuSearch(int matrixSize, int **TSPMatrix);

    // ustawienia Tabu Search
    void setSettingsTabu(int a, unsigned b, int c, int d, int e, int g);
};


#endif
