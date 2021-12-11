#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {

}


SimulatedAnnealing::~SimulatedAnnealing() {

}


/*
 * Algorytm symulowanego wyżarzania
 * Algorytm rozpoczyna działanie od temperatury początkowej. W trakcie działania, stopniowo obniżana jest temperatura.
 * Algorytm zaczyna od pewnego rozwiązania początkowego i w kolejnych iteracjach zamienia miejscami losowe elementy trasy.
 * Jeśli po zamianie, trasa jest lepsza – krótsza, zostaje ona zapisana jako dotychczasowo najlepsza, jeśli nie,
 * odrzucamy ją i wykonujemy zamianę elementów ponownie. Aby podczas tych zamian, algorytm nie utknął w minimum lokalnym,
 * dopuszczane jest także przyjęcie z pewnym prawdopodobieństwem gorszego od dotychczas najlepszego rozwiązania.
 */

void SimulatedAnnealing::settingsSimulatedAnnealing(double maxTemperature, double minTemperature, time_t executionTime) {

    this->maxTemperature = maxTemperature;
    this->minTemperature = minTemperature;
    this->executionTime = executionTime;
}



int SimulatedAnnealing::calculateCost(vector<int> &currentPath) {

    int cost = 0;

    // zliczanie drogi dla danego zbioru wierzchołków
    for (int i = 0; i < matrixSize - 1; i++) {
        cost += matrix[currentPath[i]][currentPath[i + 1]];
    }

    // dodanie drogi z ostatniego wierzchołka do pierwszego
    cost += matrix[currentPath[matrixSize - 1]][currentPath[0]];

    return cost;
}



void SimulatedAnnealing::shufflePath(vector<int> &currentPath) {

    auto rng = std::default_random_engine {};

    // pomocnicza ścieżka
    vector<int> num;
    num.resize(matrixSize);

    // wypełnienie wektora
    iota(num.begin(), num.end(), 0);

    // przetasowanie ścieżki
    shuffle(begin(num), end(num), rng);

    // przypisanie (bez pomocniczej ścieżki były błędy)
    currentPath = num;

    for (int i = 0; i < matrixSize; i++) {

        // ustawienie początkowego miasta jako 0 po przetasownaiu
        if (currentPath[i] == 0) {

            auto temp = currentPath[0];
            currentPath[0] = 0;
            currentPath[i] = temp;
        }
    }

    num.clear();
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



double SimulatedAnnealing::algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<int> &bestPath, int &bestCost) {

    Timer timer;

    // rozpoczęcie mierzenia czasu
    timer.start();

    // wartości początkowe
    foundOptimum = INT_MAX;
    matrix = originalMatrix;
    matrixSize = originalMatrix.size();

    int vertex1, vertex2;
    double cost1, cost2;

    vector<int> permutation1(matrixSize);
    vector<int> permutation2(matrixSize);

    // zaczynamy od maksymalnej temperatury
    currentTemperature = maxTemperature;

    // pierwsza permutacja miast i jej koszt
    shufflePath(permutation1);
    cost1 = calculateCost(permutation1);

    // zapasowa permutacja
    permutation2 = permutation1;


    // wykonywanie przez określony czas lub do osiągnięcia minimalnej temperatury
    while (currentTemperature > minTemperature && timer.stop() < executionTime) {

        do {
            // losowanie 2 miast (różnych i nierównych 0)
            vertex1 = rand() % matrixSize;
            vertex2 = rand() % matrixSize;

        } while (vertex1 == vertex2 || vertex1 == 0 || vertex2 == 0);

        // zamiana miast
        permutation2[vertex2] = permutation1[vertex1];
        permutation2[vertex1] = permutation1[vertex2];

        // koszt nowej permutacji miast
        cost2 = calculateCost(permutation2);

        // jeżeli jest lepszy od poprzedniej lub prawdopodobieństwo == true
        if (cost2 <= cost1 || probability(cost1, cost2, currentTemperature)) {

            // nowe minimum lokalne
            cost1 = cost2;

            // jeżeli jest mniejsze od minimum globalnego
            if (cost1 <= foundOptimum) {

                foundOptimum = cost1;
                path = permutation2;
            }

            // przepisanie lepszej permutacji
            permutation1[vertex1] = permutation2[vertex1];
            permutation1[vertex2] = permutation2[vertex2];
        }
        else {
            // przepisanie aktualnej permutacji
            permutation2[vertex1] = permutation1[vertex1];
            permutation2[vertex2] = permutation1[vertex2];
        }

        // beta
        double beta = (maxTemperature - minTemperature) / (10000000 * maxTemperature * minTemperature);

        // zmiana temperatury
        currentTemperature = (currentTemperature / (1 + beta * currentTemperature));
    }

    // dodanie początkowego wierzchołka na koniec cyklu
    path.push_back(0);

    permutation1.clear();
    permutation2.clear();

    // zwrócenie wyników
    bestPath = path;
    bestCost = foundOptimum;

    return timer.stop();
}