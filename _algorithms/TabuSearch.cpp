#include "TabuSearch.h"



TabuSearch::TabuSearch() {

}


TabuSearch::~TabuSearch() {

}


void TabuSearch::setSettingsTabu(int a, unsigned b, int c, int d, int e, int g) {
    tabuCadence = a;
    tabuTime = b;
    iterationsLimit = c;
    intensificationDiv = d;
    amountRandomNodes = e;
    neighborhoodType = g;
}


int TabuSearch::getInitialGreedy(vector < unsigned >&bestTab) {
    int localMin = 0;
    int bestMin, tempBest = 0, oldTempBest = 0;
    int *visitedTab = new int[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        visitedTab[i] = 0;
    }

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

    delete[]visitedTab;

    return localMin;

}


int TabuSearch::getInitialGreedyAndRandom(vector < unsigned >&bestTab) {

    random_device randomSrc;
    default_random_engine randomGen(randomSrc());
    uniform_int_distribution<> nodeRand(0, matrixSize - 1);

    int bestMin, tempBest = 0, oldTempBest = 0;
    int localMin = 0;
    int *visitedTab = new int[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        visitedTab[i] = 0;
    }
    vector<vector<int>> macierz;
    macierz = matrix;

    bool ifVisited;
    int randomNode;
    int remainingNodes = amountRandomNodes;

    for (int i = 0; i < matrixSize; i++) {
        bestMin = INT_MAX;
        oldTempBest = tempBest;
        if (remainingNodes != 0) {
            ifVisited = false;
            while (ifVisited == false) {
                randomNode = nodeRand(randomGen);
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

        }
        else {
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

    return localMin;
}


int TabuSearch::algorithmTabuSearch(vector<vector<int>> TSPMatrix) {
    matrixSize = TSPMatrix.size();
    optMin = INT_MAX;

    matrix = TSPMatrix;


    int greedyStart = 1;
    vector <unsigned> route;
    optMin = getInitialGreedy(route);  cout<<"optMin po mierwszym greedy: "<<optMin<<endl;
    bestRoute = route;
    vector < unsigned > currentRoute = bestRoute;

    Timer onboardClock;

    onboardClock.start();


    bool continuing = true;
    currentTabuCadence = tabuCadence;
    currentOptMin = optMin;
    int balance = 0, bestBalance;
    int bestI = 0, bestJ = 0;
    int counter = 0, iterWithoutImprovement = 0;
    bool intensification, diversification = true;


    while (continuing == true) {
        intensification = false;
        vector<unsigned> currentTabu(3, 0);

        currentTabu.at(2) = currentTabuCadence;

        if (neighborhoodType == 0) {
            bestBalance = getBestNeighborhoodReverse(bestI, bestJ, currentRoute);
            currentTabu.at(0) = currentRoute[bestI];
            currentTabu.at(1) = currentRoute[bestJ];
            reverseVector(bestI, bestJ, currentRoute);
        }

        if (neighborhoodType == 1) {
            bestBalance = getBestNeighborhoodSwap(bestI,bestJ, currentRoute);
            currentTabu.at(0) = currentRoute[bestI];
            currentTabu.at(1) = currentRoute[bestJ];
            swapVector(bestI, bestJ, currentRoute);
        }



        currentOptMin = currentOptMin + bestBalance;
        cout<<"currentOptMin: "<<currentOptMin<<endl;

        if (currentOptMin < optMin) {
            iterWithoutImprovement = 0; //wyzerowanie w razie znalezienia globalnego minimum
            intensification = true;
            optMin = currentOptMin; //lokalne minimum = globalne minimum
            bestRoute = currentRoute; //lokalna sciezka = globalna sciezka

        }

        //-----zinkrementowanie kadencji i usuniecie zerowych------
        cleanTabuList();

        //-----dodanie ruchu do listy tabu------
        tabuList.push_back(currentTabu);

        counter++;
        iterWithoutImprovement++;

        onboardClock.stop();
        //cout << onboardClock.read()<<endl;
        //-----sprawdzenie czy uplynal czas------
        if (onboardClock.read() > tabuTime)
            continuing = false;

        //-----w razie znalezienie globalnego optimum intensyfikacja------
        if (intensification == true)
        {
            currentTabuCadence = tabuCadence / intensificationDiv;
            intensification = false;
        }

        //-----sprawdzenie czy nie doszlo do przekroczenia limutu iteracji------
        if (iterWithoutImprovement > iterationsLimit) {
            if (diversification == true)
            {

                tabuList.clear();

                vector < unsigned > route;

                //-----jednorazowe uruchomienie greedy------
                if (greedyStart != 0) {
                    currentOptMin = getInitialGreedy(route);
                    greedyStart--;
                }
                //-----dalej uruchamianie randomowych------
                else {

                    currentOptMin = getInitialGreedyAndRandom(route);
                }
                //-----powrot do domyslnej kadencji------
                currentTabuCadence = tabuCadence;
                //-----wyzerowanie liczby iteracji------
                iterWithoutImprovement = 0;
                //-----ustawienie obecnej sciezki------
                currentRoute = route;

            }
        }
    }
    clearParameters(currentRoute);

    return optMin;
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


void TabuSearch::clearParameters(vector <unsigned> currentRoute) {
    bestRoute.clear();
    currentRoute.clear();
}



int TabuSearch::getBestNeighborhoodReverse(int &bestI, int &bestJ, vector <unsigned> currentRoute) {
    int bestBalance = INT_MAX;
    int balance;
    bool ifTabu;
    bestI = 0;
    bestJ = 0;

    for (int i = 1; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {

            balance = calculateReverse(i, j,currentRoute);

            ifTabu = false;

            for (int k = 0; k < tabuList.size(); k++)
            {
                if (tabuList.at(k).at(0) == currentRoute.at(i) && tabuList.at(k).at(1) == currentRoute.at(j))
                {
                    ifTabu = true;
                    break;
                }
                if (tabuList.at(k).at(0) == currentRoute.at(j) && tabuList.at(k).at(1) == currentRoute.at(i))
                {
                    ifTabu = true;
                    break;
                }
            }

            if (ifTabu == true && currentOptMin + balance >= optMin)
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


void TabuSearch::reverseVector(int a, int b, vector <unsigned>& currentRoute) {
    reverse(currentRoute.begin() + a, currentRoute.begin() + b + 1);
}



int TabuSearch::calculateReverse(int i, int j, vector <unsigned> currentRoute) {

    int balance;
    balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)] - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
    balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)] + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];

    for (int k = i; k < j; k++)
        balance = balance - matrix[currentRoute.at(k)][currentRoute.at(k + 1)] + matrix[currentRoute.at(k + 1)][currentRoute.at(k)];

    return balance;
}



int TabuSearch::getBestNeighborhoodSwap(int &bestI, int &bestJ, vector <unsigned> currentRoute) {
    int bestBalance = INT_MAX;
    int balance;
    bool ifTabu;
    bestI = 0;
    bestJ = 0;


    for (int i = 1; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {

            balance = calculateSwap(i, j, currentRoute);

            ifTabu = false;

            for (int k = 0; k < tabuList.size(); k++)
            {
                if (tabuList.at(k).at(0) == currentRoute.at(i) && tabuList.at(k).at(1) == currentRoute.at(j))
                {
                    ifTabu = true;
                    break;
                }
                if (tabuList.at(k).at(0) == currentRoute.at(j) && tabuList.at(k).at(1) == currentRoute.at(i))
                {
                    ifTabu = true;
                    break;
                }
            }

            if (ifTabu == true && currentOptMin + balance >= optMin)
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



void TabuSearch::swapVector(int a, int b, vector <unsigned>& currentRoute) {
    unsigned buffer = currentRoute.at(b);
    currentRoute.at(b) = currentRoute.at(a);
    currentRoute.at(a) = buffer;
}



int TabuSearch::calculateSwap(int i, int j, vector <unsigned> currentRoute) {
    int balance;
    if (i + 1 == j) {
        balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)];
        balance = balance - matrix[currentRoute.at(i)][currentRoute.at(j)];
        balance = balance - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
        balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)];
        balance = balance + matrix[currentRoute.at(j)][currentRoute.at(i)];
        balance = balance + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];
    }
    else {
        balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)];
        balance = balance - matrix[currentRoute.at(i)][currentRoute.at(i + 1)];
        balance = balance - matrix[currentRoute.at(j - 1)][currentRoute.at(j)];
        balance = balance - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
        balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)];
        balance = balance + matrix[currentRoute.at(j)][currentRoute.at(i + 1)];
        balance = balance + matrix[currentRoute.at(j - 1)][currentRoute.at(i)];
        balance = balance + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];
    }
    return balance;
}