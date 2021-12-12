#include "TabuSearch.h"



TabuSearch::TabuSearch() {

}


TabuSearch::~TabuSearch() {

    bestRoute.clear();
}


/*
 * Algorytm bazuje na dynamicznej zmianie sąsiedztwa danego rozwiązania i szukaniu lokalnie najlepszych rozwiązań.
 * Podstawą algorytmu jest zapamiętywanie ruchów na liście tabu. Zapisywanie ruchów niedozwolonych w tabu pozwala na
 * odrzucenie rozwiązań niedawno sprawdzanych, zwiększając obszar przeszukiwania, co skutkuje większą możliwością
 * wyjścia z minimum lokalnego kosztem dokładności algorytmu.
 */

void TabuSearch::settingsTabuSearch(int cadence, int divCadence, time_t stopTime) {

    this->cadence = cadence;
    this->divideCadence = divCadence;
    this->executionTime = stopTime;
}



int TabuSearch::findInitialSolution(vector<int> &route) {

    int localMinimum = 0;
    int bestMinimum, tempBest = 0, oldTempBest;

    // tablica odwiedzonych wierzchołków
    vector<int> visitedTab(matrixSize, 0);

    bool ifVisited;

    // dla każdego wierzchołka
    for (int i = 0; i < matrixSize; i++) {

        bestMinimum = INT_MAX;
        oldTempBest = tempBest;

        // szukamy najkorzystniejsze rozwiązanie (dla niesprawdzonych wierzchołków)
        for (int j = 0; j < matrixSize; j++) {

            ifVisited = true;

            if (j != oldTempBest) {

                for (int k = 0; k <= i; k++) {

                    if (j == visitedTab[k]) {
                        ifVisited = false;
                    }
                }

                // znalezienie lokalnego minimum dla danego wierzchołka
                if (matrix[oldTempBest][j] < bestMinimum && ifVisited == true) {
                    bestMinimum = matrix[oldTempBest][j];
                    tempBest = j;
                }
            }
        }
        if (i < matrixSize - 1) {

            // dodajemy optymalny koszt dla danego wierzchołka
            localMinimum = localMinimum + bestMinimum;
        }
        else {

            // dodajemy koszt z ostatniego wierzchołka do pierwszego
            localMinimum = localMinimum + matrix[oldTempBest][0];
        }

        // dodajemy do ścieżki optymalny wierzchołek
        route.push_back(oldTempBest);
        visitedTab[i] = tempBest;
    }

    // dodajemy na koniec ścieżki wierzchołek startowy
    route.push_back(0);

    visitedTab.clear();

    return localMinimum;
}



int TabuSearch::searchNeighborhood(int &bestI, int &bestJ, vector<int> &currentRoute) {

    int bestBalance = INT_MAX, balance;
    bool ifTabu;
    bestI = 0;
    bestJ = 0;

    for (int i = 1; i < matrixSize - 1; i++) {

        for (int j = i + 1; j < matrixSize; j++) {

            // policzenie balansu pomiędzy wierzchołkami
            balance = calculateAfterReverse(i, j, currentRoute);

            ifTabu = false;

            for (int k = 0; k < tabuList.size(); k++) {

                // sprawdzenie czy sąsiad nie należy do listy tabu
                if (tabuList.at(k).at(0) == currentRoute.at(i) && tabuList.at(k).at(1) == currentRoute.at(j)) {
                    ifTabu = true;
                    break;
                }

                // sprawdzenie czy sąsiad nie należy do listy tabu
                if (tabuList.at(k).at(0) == currentRoute.at(j) && tabuList.at(k).at(1) == currentRoute.at(i)) {
                    ifTabu = true;
                    break;
                }
            }

            // nie zmieniamy rozwiązania jeżeli sąsiad znajduje się w liście tabu oraz
            // nie spełnia kryterium aspiracji czyli nie prowadzi do globalnego optimum
            if (ifTabu == true && currentOptimum + balance >= globalOptimum)
                continue;

            // uzyskanie nowego rozwiązania
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

    // reverse(4,1): <0,3,4,2,5,1,0> -> <0,3,1,5,2,4,0>

    int balance = matrix[currentRoute.at(i - 1)][currentRoute.at(j)] - matrix[currentRoute.at(i - 1)][currentRoute.at(i)];
    balance = balance + matrix[currentRoute.at(i)][currentRoute.at(j + 1)] - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];

    for (int k = i; k < j; k++)
        balance = balance + matrix[currentRoute.at(k + 1)][currentRoute.at(k)] - matrix[currentRoute.at(k)][currentRoute.at(k + 1)];

    return balance;
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

    // wygenerowanie początkowego rozwiązania
    globalOptimum = findInitialSolution(route);
    bestRoute = route;
    currentRoute = bestRoute;

    // początkowe ustawienia
    currentCadence = cadence;
    currentOptimum = globalOptimum;

    int bestBalance, bestI = 0, bestJ = 0;

    time_t check = 0;

    // wykonywanie przez określony czas
    while (timer.stop() < executionTime) {

        intensification = false;

        // przeszukanie całego sąsiedztwa
        bestBalance = searchNeighborhood(bestI, bestJ, currentRoute);

        // dodanie elementu do listy tabu
        vector<int> currentTabu(3, 0);
        currentTabu.at(0) = currentRoute[bestI];
        currentTabu.at(1) = currentRoute[bestJ];
        currentTabu.at(2) = currentCadence;

        // odwrócenie części ścieżki
        // reverse(4,1): <0,3,4,2,5,1,0> -> <0,3,1,5,2,4,0>
        reverse(currentRoute.begin() + bestI, currentRoute.begin() + bestJ + 1);

        // szukanie nowego lokalnego optimum
        currentOptimum = currentOptimum + bestBalance;

        if (currentOptimum < globalOptimum && currentOptimum > 0) {

            // włączenie intensyfikacji
            intensification = true;

            // przypisanie optymalnej ścieżki i kosztu
            globalOptimum = currentOptimum;
            bestRoute = currentRoute;
        }

        for (int i = 0; i < tabuList.size(); i++) {

            // dekrementacja kadencji w liście tabu
            tabuList.at(i).at(2)--;

            // usunięcie ruchu z listy tabu jeżeli ich kadencja jest równa 0
            if (tabuList.at(i).at(2) == 0) {
                tabuList.erase(tabuList.begin() + i);
                i = i - 1;
            }
        }

        // dodanie ruchu do listy tabu
        tabuList.push_back(currentTabu);

        // intensyfikacja po znalezieniu globalnego minimum
        if (intensification == true) {

            currentCadence /= divideCadence;
            intensification = false;
        }

// pokazuje aktualny wynik co sekundę (dane do wykresów)

//        if (timer.stop() > check) {
//
//            cout << "po " << timer.stop() << "s: " << globalOptimum << endl;
//            check += 1;
//        }
    }

    // zwolnienie pamięci
    currentRoute.clear();

    // zwrócenie wyników
    bestPath = bestRoute;
    bestCost = globalOptimum;

    return timer.stop();
}