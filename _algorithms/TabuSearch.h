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

    vector<vector<int>> matrix;
    int matrixSize;
    vector < unsigned >bestRoute;
    int optMin;
    int currentOptMin;
    int currentTabuCadence;
    vector< vector<unsigned> > tabuList;


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
    int calculateInsert(int i, int j, vector <unsigned> currentRoute);
    int calculateReverse(int i, int j, vector <unsigned> currentRoute);
    int calculateSwap(int i, int j, vector <unsigned> currentRoute);


public:

    // konstruktor
    TabuSearch();

    // destruktor
    ~TabuSearch();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    int algorithmTabuSearch(vector<vector<int>> TSPMatrix);

    // ustawienia Tabu Search
    void setSettingsTabu(int a, unsigned b, int c, int d, int e, int g);
};


#endif
