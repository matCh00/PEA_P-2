#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {

}


SimulatedAnnealing::~SimulatedAnnealing() {

}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
// TODO dodać limit iteracji i typy sąsiedztwa na podstawie koks projektu
void SimulatedAnnealing::settingsSimulatedAnnealing(double maxTemperature, double minTemperature, time_t executionTime, int iterationsLimit, int neighborhoodType) {

    this->maxTemperature = maxTemperature;
    this->minTemperature = minTemperature;
    this->executionTime = executionTime;

    this->iterationsLimit = iterationsLimit;
    this->neighborhoodType = neighborhoodType;
}



int SimulatedAnnealing::route(vector<int> &currentPath) {

    int cost = 0;

    // zliczanie drogi dla danego zbioru wierzchołków
    for (int i = 0; i < matrixSize - 1; i++) {
        cost += matrix[currentPath[i]][currentPath[i + 1]];
    }

    // dodanie drogi z ostatniego wierzchołka do pierwszego
    cost += matrix[currentPath[matrixSize - 1]][currentPath[0]];

    return cost;
}



void SimulatedAnnealing::permutation(vector<int> &currentPath) {

    vector<int> num;
    num.resize(matrixSize);

    int random;

    for (int i = 0; i < matrixSize; i++) {
        num[i] = i;
    }

    for (int i = matrixSize; i > 0; i--) {

        // losowanie jednego miasta
        random = rand() % i;
        currentPath[i - 1] = num[random];
        num[random] = num[i - 1];
    }

    for (int i = 0; i < matrixSize; i++) {

        // po losowaniu ustawienie początkowego miasta jako 0
        if (currentPath[i] == 0) {

            auto temp = currentPath[0];
            currentPath[0] = 0;
            currentPath[i] = temp;
        }
    }

    num.clear();

//    Randomize r;
//
//    int i, j, balance = 0;
//
//    if (neighborhoodType == 1) { //swap
//        do {
//            i = r.random_engine(1, matrixSize - 2);
//            j = r.random_engine(1, matrixSize - 2);
//        } while (i == j || j < i);
//
//        unsigned buffer = perm.at(j);
//        perm.at(j) = perm.at(i);
//        perm.at(i) = buffer;
//    }
//
//
//    else if (neighborhoodType == 0) {
//        do {
//            i = r.random_engine(1, matrixSize - 2);
//            j = r.random_engine(1, matrixSize - 2);
//        } while (i == j || j < i);
//
//        reverse(perm.begin() + i, perm.begin() + j + 1);
//    }
}



bool SimulatedAnnealing::probability(int length1, int length2, double temperature) {

    double e = 2.718281828459;

    // prawdopodobieństwo
    double p = pow(e, ((-1 * ((long long)length2 - (long long)length1)) / temperature));

    // wybranie liczby z przedziału <0,1>
    double r = (double)rand() / RAND_MAX;

    // jezeli prawdopodobienstwo ze wzoru jest wieksze od losowo wybranej liczby
    return (r < p);
}



int SimulatedAnnealing::algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<int> &bestPath) {

    Timer timer;

    // wartości początkowe
    bestCost = INT_MAX;
    matrix = originalMatrix;
    matrixSize = originalMatrix.size();

    int vertex1, vertex2;
    double cost1, cost2;

    vector<int> permutation1;
    permutation1.resize(matrixSize);

    vector<int> permutation2;
    permutation2.resize(matrixSize);

    // zaczynamy od maxymalnej temperatury
    currentTemperature = maxTemperature;


    // rozpoczęcie mierzenia czasu
    timer.start();

    // pierwsza permutacja miast i jej koszt
    permutation(permutation1);
    cost1 = route(permutation1);

    // zapasowa permutacja
    permutation2 = permutation1;


    time_t finishTime;
    time_t startTime = time(NULL);
    finishTime = startTime + executionTime;

    // wykonywanie przez określony czas lub do osiągnięcia minimalnej temperatury
    while (currentTemperature > minTemperature && startTime < finishTime) {

        do {
            // losowanie 2 miast (różnych i nierównych 0)
            vertex1 = rand() % matrixSize;
            vertex2 = rand() % matrixSize;

        } while (vertex1 == vertex2 || vertex1 == 0 || vertex2 == 0);

        // zamiana miast
        permutation2[vertex2] = permutation1[vertex1];
        permutation2[vertex1] = permutation1[vertex2];

        // koszt nowej permutacji miast
        cost2 = route(permutation2);

        // jeżeli jest lepszy od poprzedniej lub prawdopodobieństwo == true
        if (cost2 <= cost1 || probability(cost1, cost2, currentTemperature)) {

            // nowe minimum lokalne
            cost1 = cost2;

            // jeżeli jest mniejsze od minimum globalnego
            if (cost1 <= bestCost) {

                bestCost = cost1;
                path = permutation2;
            }

            // przepisanie lepszej permutacji
            permutation1[vertex1] = permutation2[vertex1];
            permutation1[vertex2] = permutation2[vertex2];
        }
        else {

            permutation2[vertex1] = permutation1[vertex1];
            permutation2[vertex2] = permutation1[vertex2];
        }

        // beta
        double beta = (maxTemperature - minTemperature) / (10000000 * maxTemperature * minTemperature);

        // zmiana temperatury
        currentTemperature = (currentTemperature / (1 + beta * currentTemperature));

        startTime = time(NULL);
        timer.stop();
    }

    // dodanie początkowego wierzchołka na koniec cyklu
    path.push_back(0);

    permutation1.clear();
    permutation2.clear();

    // zwrócenie wyników
    bestPath = path;
    return bestCost;
}