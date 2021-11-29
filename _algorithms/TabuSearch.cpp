#include "TabuSearch.h"



TabuSearch::TabuSearch() {

}


TabuSearch::~TabuSearch() {

    bestRoute.clear();
}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
void TabuSearch::settingsTabuSearch(int cadence, int divCadence, time_t stopTime) {

    this->cadence = cadence;
    this->divCadence = divCadence;
    this->executionTime = stopTime;
}



int TabuSearch::findLocalMinimum(vector<int> &route) {

    int localMin = 0;
    int bestMin, tempBest = 0, oldTempBest = 0;
    vector<int> visitedTab(matrixSize, 0);

    bool ifVisited;
    for (int i = 0; i < matrixSize; i++) {

        bestMin = INT_MAX;
        oldTempBest = tempBest;

        for (int j = 0; j < matrixSize; j++) {

            ifVisited = true;

            if (j != oldTempBest) {

                for (int k = 0; k <= i; k++) {

                    if (j == visitedTab[k]) {
                        ifVisited = false;
                    }
                }

                if (matrix[oldTempBest][j] < bestMin && ifVisited == true) {
                    bestMin = matrix[oldTempBest][j];
                    tempBest = j;
                }
            }
        }
        if (i < matrixSize - 1) {
            localMin = localMin + bestMin;
        }
        else {
            localMin = localMin + matrix[oldTempBest][0];
        }

        route.push_back(oldTempBest);
        visitedTab[i] = tempBest;
    }

    route.push_back(0);

    visitedTab.clear();

    return localMin;
}


double TabuSearch::algorithmTabuSearch(vector<vector<int>> originalMatrix, vector<int> &bestPath, int &bestCost) {

    Timer timer;

    // rozpoczęcie mierzenia czasu
    timer.start();

    // wartości początkowe
    matrixSize = originalMatrix.size();
    matrix = originalMatrix;
    globalOptimum = INT_MAX;

    // rezerwacja miejsca
    bestRoute.resize(matrixSize + 1);
    currentRoute.resize(matrixSize + 1);


    vector<int> route;
    globalOptimum = findLocalMinimum(route);
    bestRoute = route;
    currentRoute = bestRoute;


    currentTabuCadence = cadence;
    currentOptimum = globalOptimum;
    int bestBalance;
    int bestI = 0, bestJ = 0;
    int counter = 0, iterWithoutImprovement = 0;


    while (timer.stop() < executionTime) {

        intensification = false;
        vector<int> currentTabu(3, 0);

        currentTabu.at(2) = currentTabuCadence;

        bestBalance = bestNeighborhood(bestI, bestJ, currentRoute);
        currentTabu.at(0) = currentRoute[bestI];
        currentTabu.at(1) = currentRoute[bestJ];

        // odwrócenie części wektora
        reverse(currentRoute.begin() + bestI, currentRoute.begin() + bestJ + 1);


        currentOptimum = currentOptimum + bestBalance;

        if (currentOptimum < globalOptimum) {

            // wyzerowanie po znalezieniu globalnego minimum
            iterWithoutImprovement = 0;
            intensification = true;

            // przypisanie optymalnyej ścieżki i kosztu
            globalOptimum = currentOptimum;
            bestRoute = currentRoute;

        }

        // wyczyszczenie listy tabu
        for (int i = 0; i < tabuList.size(); i++) {
            tabuList.at(i).at(2)--;

            if (tabuList.at(i).at(2) == 0) {
                tabuList.erase(tabuList.begin() + i);
                i = i - 1;
            }
        }

        // dodanie ruchu do listy tabu
        tabuList.push_back(currentTabu);

        counter++;
        iterWithoutImprovement++;


        // intensyfikacja po znalezieniu globalnego minimum
        if (intensification == true) {
            currentTabuCadence /= divCadence;
            intensification = false;
        }
    }

    // zwolnienie pamięci
    currentRoute.clear();

    // zwrócenie wyników
    bestPath = bestRoute;
    bestCost = globalOptimum;

    return timer.stop();
}



int TabuSearch::bestNeighborhood(int &bestI, int &bestJ, vector<int> &currentRoute) {

    int bestBalance = INT_MAX;
    int balance;
    bool ifTabu;
    bestI = 0;
    bestJ = 0;

    for (int i = 1; i < matrixSize - 1; i++) {

        for (int j = i + 1; j < matrixSize; j++) {

            balance = calculateAfterReverse(i, j, currentRoute);

            ifTabu = false;

            for (int k = 0; k < tabuList.size(); k++) {

                if (tabuList.at(k).at(0) == currentRoute.at(i) && tabuList.at(k).at(1) == currentRoute.at(j)) {
                    ifTabu = true;
                    break;
                }

                if (tabuList.at(k).at(0) == currentRoute.at(j) && tabuList.at(k).at(1) == currentRoute.at(i)) {
                    ifTabu = true;
                    break;
                }
            }

            if (ifTabu == true && currentOptimum + balance >= globalOptimum)
                continue;

            if (balance < bestBalance) {
                bestBalance = balance;
                bestI = i;
                bestJ = j;
            }
        }
    }

    return bestBalance;
}



int TabuSearch::calculateAfterReverse(int i, int j, vector<int> &currentRoute) {

    int balance;

    balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)] - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
    balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)] + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];

    for (int k = i; k < j; k++)
        balance = balance - matrix[currentRoute.at(k)][currentRoute.at(k + 1)] +
                  matrix[currentRoute.at(k + 1)][currentRoute.at(k)];

    return balance;
}