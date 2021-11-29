#include "TabuSearch.h"



TabuSearch::TabuSearch() {

}


TabuSearch::~TabuSearch() {

    bestRoute.clear();
}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
// TODO uprościć TS
void TabuSearch::settingsTabuSearch(int cadence, int divCadence, time_t stopTime) {

    this->cadence = cadence;
    this->divCadence = divCadence;
    this->stopTime = stopTime;
}



int TabuSearch::getInitialGreedy(vector<int> &bestTab) {

    int localMin = 0;
    int bestMin, tempBest = 0, oldTempBest = 0;
    vector<int> visitedTab(matrixSize, 0);

    vector<vector<int>> macierz;
    macierz = matrix;

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
                if (macierz[oldTempBest][j] < bestMin && ifVisited == true) {
                    bestMin = macierz[oldTempBest][j];
                    tempBest = j;
                }
            }
        }
        if (i < matrixSize - 1)
            localMin = localMin + bestMin;
        else
            localMin = localMin + macierz[oldTempBest][0];

        bestTab.push_back(oldTempBest);
        visitedTab[i] = tempBest;
    }

    bestTab.push_back(0);

    macierz.clear();
    visitedTab.clear();

    return localMin;
}



int TabuSearch::getInitialGreedyAndRandom(vector<int> &bestTab) {

    Randomize r;

    int bestMin, tempBest = 0, oldTempBest = 0;
    int localMin = 0;
    vector<int> visitedTab(matrixSize, 0);
    vector<vector<int>> macierz;
    macierz = matrix;

    bool ifVisited;
    int randomNode;
    int remainingNodes = matrixSize - 5;

    for (int i = 0; i < matrixSize; i++) {
        bestMin = INT_MAX;
        oldTempBest = tempBest;
        if (remainingNodes != 0) {
            ifVisited = false;
            while (ifVisited == false) {
                randomNode = r.random_engine(0, matrixSize - 1);
                ifVisited = true;
                for (int k = 0; k <= i; k++) {
                    if (randomNode == visitedTab[k]) {
                        ifVisited = false;
                    }
                }
            }
            tempBest = randomNode;
            bestMin = macierz[oldTempBest][randomNode];
            remainingNodes--;

        } else {
            for (int j = 0; j < matrixSize; j++) {
                ifVisited = true;
                if (j != oldTempBest) {
                    for (int k = 0; k <= i; k++) {
                        if (j == visitedTab[k]) {
                            ifVisited = false;
                        }
                    }
                    if (macierz[oldTempBest][j] < bestMin && ifVisited == true) {
                        bestMin = macierz[oldTempBest][j];
                        tempBest = j;
                    }
                }
            }
        }
        if (i < matrixSize - 1)
            localMin = localMin + bestMin;
        else
            localMin = localMin + macierz[oldTempBest][0];

        bestTab.push_back(oldTempBest);
        visitedTab[i] = tempBest;
    }
    bestTab.push_back(0);

    macierz.clear();
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
    int greedyStart = 1;

    //int xxx = 0;/////////

    // rezerwacja miejsca
    bestRoute.resize(matrixSize + 1);
    currentRoute.resize(matrixSize + 1);


    vector<int> route;
    globalOptimum = getInitialGreedy(route);

    bestRoute = route;
    currentRoute = bestRoute;




    bool continuing = true;
    currentTabuCadence = cadence;
    currentOptimum = globalOptimum;
    int bestBalance;
    int bestI = 0, bestJ = 0;
    int counter = 0, iterWithoutImprovement = 0;


    while (continuing == true) {
        intensification = false;
        vector<int> currentTabu(3, 0);

        currentTabu.at(2) = currentTabuCadence;


        bestBalance = getBestNeighborhoodReverse(bestI, bestJ, currentRoute);
        currentTabu.at(0) = currentRoute[bestI];
        currentTabu.at(1) = currentRoute[bestJ];
        reverseVector(bestI, bestJ, currentRoute);



        currentOptimum = currentOptimum + bestBalance;
        //cout << "currentOptimum: " << currentOptimum << "     xxx: " << xxx++ << endl;

        if (currentOptimum < globalOptimum) {
            iterWithoutImprovement = 0; //wyzerowanie w razie znalezienia globalnego minimum
            intensification = true;
            globalOptimum = currentOptimum; //lokalne minimum = globalne minimum
            bestRoute = currentRoute; //lokalna sciezka = globalna sciezka

        }

        //-----zinkrementowanie kadencji i usuniecie zerowych------
        cleanTabuList();

        //-----dodanie ruchu do listy tabu------
        tabuList.push_back(currentTabu);

        counter++;
        iterWithoutImprovement++;


        //-----sprawdzenie czy uplynal czas------
        if (timer.stop() > stopTime)
            continuing = false;

        //-----w razie znalezienie globalnego optimum intensyfikacja------
        if (intensification == true) {
            currentTabuCadence = cadence / divCadence;
            intensification = false;
        }

    }

    // zwolnienie pamięci
    currentRoute.clear();

    // przekazanie cieżki
    bestPath = bestRoute;
    bestCost = globalOptimum;

    return timer.stop();
}



void TabuSearch::cleanTabuList() {

    for (int i = 0; i < tabuList.size(); i++) {
        tabuList.at(i).at(2)--;

        if (tabuList.at(i).at(2) == 0) {
            tabuList.erase(tabuList.begin() + i);
            i = i - 1;
        }
    }
}



int TabuSearch::getBestNeighborhoodReverse(int &bestI, int &bestJ, vector<int> &currentRoute) {

    int bestBalance = INT_MAX;
    int balance;
    bool ifTabu;
    bestI = 0;
    bestJ = 0;

    for (int i = 1; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {

            balance = calculateReverse(i, j, currentRoute);

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



void TabuSearch::reverseVector(int a, int b, vector<int> &currentRoute) {

    reverse(currentRoute.begin() + a, currentRoute.begin() + b + 1);
}



int TabuSearch::calculateReverse(int i, int j, vector<int> &currentRoute) {

    int balance;
    balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)] - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
    balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)] + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];

    for (int k = i; k < j; k++)
        balance = balance - matrix[currentRoute.at(k)][currentRoute.at(k + 1)] + matrix[currentRoute.at(k + 1)][currentRoute.at(k)];

    return balance;
}