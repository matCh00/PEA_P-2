/*
 * Algorytm symulowanego wyżarzania
 * Algorytm rozpoczyna działanie od temperatury początkowej. W trakcie działania stopniowo obniżana jest temperatura.
 * Algorytm zaczyna od pewnego rozwiązania początkowego i w kolejnych iteracjach zamienia miejscami losowe elementy trasy.
 * Jeśli po zamianie, trasa jest lepsza – krótsza, zostaje ona zapisana jako dotychczasowo najlepsza, jeśli nie,
 * odrzucamy ją i wykonujemy zamianę elementów ponownie. Aby podczas tych zamian, algorytm nie utknął w minimum lokalnym,
 * dopuszczane jest także przyjęcie z pewnym prawdopodobieństwem gorszego od dotychczas najlepszego rozwiązania.
 */

#ifndef PEA_P_2_SIMULATEDANNEALING_H
#define PEA_P_2_SIMULATEDANNEALING_H

#include "../_structures/Graph.h"

using namespace std;


class SimulatedAnnealing {

private:

    // początkowa temperatura
    double maxTemperature;

    // minimalna temperatura
    double minTemperature;

    // aktualna temperatura
    double currentTemperature;

    // czas wykonania
    time_t executionTime;

    // macierz
    vector<vector<int>> matrix;

    // liczba miast
    int matrixSize;

    // aktualnie optymalna ścieżka
    vector<int> path;

    // najmniejszy znaleziony koszt
    int foundOptimum;

    // obliczanie kosztu ścieżki
    int calculateCost(vector<int> &currentPath);

    // losowanie kolejności miast
    void shufflePath(vector<int> &currentPath);

    // prawdopodobienstwo przyjęcia gorszego rozwiązania
    bool probability(int length1, int length2, double temperature);


public:

    // konstruktor
    SimulatedAnnealing();

    // destruktor
    ~SimulatedAnnealing();

    // algorytm Simulated Annealing
    double algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<int> &bestPath, int &bestCost);

    // ustawienia Simulated Annealing
    void settingsSimulatedAnnealing(double initialTemperature, double minTemperature, time_t stopTime);
};


#endif
