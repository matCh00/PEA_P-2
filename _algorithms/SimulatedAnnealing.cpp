#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {

}


SimulatedAnnealing::~SimulatedAnnealing() {

}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
void SimulatedAnnealing::settingsSimulatedAnnealing(int stopTime, int neighborhoodType) {

    this->stopTime = stopTime;
    this->neighborhoodType = neighborhoodType;
}



int SimulatedAnnealing::countPath(vector<int> &path) {

    int cost = 0;

    // zliczanie drogi
    for (int i = 0; i < matrixSize - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }

    // droga z ostatniego do pierwszego
    cost += matrix[path[matrixSize - 1]][path[0]];

    return cost;
}



void SimulatedAnnealing::createPermutation(vector<int> &permutation) {

    vector<int> cities(matrixSize);

    // zapełnij wektor liczbami od 0 do matrixSize - 1
    iota(begin(cities), end(cities), 0);

    int random;

    for (int i = matrixSize; i > 0; i--) {

        // losowanie wierzchołka
        random = rand() % i;

        permutation[i - 1] = cities[random];
        cities[random] = cities[i - 1];
    }

    cities.clear();
}



bool SimulatedAnnealing::countProbability(int length1, int length2, double temperature) {

    double p = pow(2.718281828459, ((-1 * ((long long)length2 - (long long)length1)) / temperature));

    // wybranie cyfry z przedziału <0,1>
    double r = (double)rand() / RAND_MAX;

    // czy prawdopodobienstwo ze wzoru jest wieksze od losowo wybranej liczby
    return (r < p);
}



int SimulatedAnnealing::algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<unsigned int> &bestPath) {

    // ustawienie początkowych wartości
    matrixSize = originalMatrix.size();
    matrix = originalMatrix;
    minTemperature = 0.001;
    double finishTime = 0;
    Timer timer;


    __int64 counter = 0;
    double frequency = 1;
    LARGE_INTEGER l_int;
    QueryPerformanceFrequency(&l_int);
    frequency = double(l_int.QuadPart);
    QueryPerformanceCounter(&l_int);
    counter = l_int.QuadPart;


    // deklaracja zmiennych i struktur
    int vertex1, vertex2;
    double temperature, deltaMax = 0, delta, cost1, cost2;

    // wektory permutacji
    vector<int> permutation1;
    vector<int> permutation2;
    permutation1.resize(matrixSize);
    permutation2.resize(matrixSize);

    // początek liczenia czasu
    timer.start();

    for (int i = 0; i < matrixSize; i++) {

        createPermutation(permutation1);
        createPermutation(permutation2);

        delta = abs(countPath(permutation1) - countPath(permutation2));

        if (delta > deltaMax) {

            deltaMax = delta;
        }

        permutation1.clear();
        permutation2.clear();
        permutation1.resize(matrixSize);
        permutation2.resize(matrixSize);
    }

    temperature = deltaMax;

    // tworzenie permutacji i obliczanie jej kosztu
    createPermutation(permutation1);
    cost1 = countPath(permutation1);

    // tworzenie zapasowej permutacji
    for (int i = 0; i < matrixSize; i++) {

        permutation2[i] = permutation1[i];
    }


    std::time_t finish;
    std::time_t start1 = std::time(NULL);
    finish = start1 + (time_t)stopTime;

    int count = 0;;

    while (temperature > minTemperature && start1<finish) {

        count++;
        do
        {
            //losowanie 2 nowych miast do zamiany w permutacji
            vertex1 = rand() % matrixSize;
            vertex2 = rand() % matrixSize;

        } while (vertex1 == vertex2);//petla wykonuje sie dopoki miasta nie beda rozne

        //zamiana miast
        permutation2[vertex2] = permutation1[vertex1];
        permutation2[vertex1] = permutation1[vertex2];


        cost2 = countPath(permutation2);

        if (cost2 <= cost1 || countProbability(cost1, cost2, temperature))
        {
            cost1 = cost2;//
            if (cost1 <= globalOptimum)
            {
                globalOptimum = cost1;
            }

            permutation1[vertex1] = permutation2[vertex1]; //koszt dla permutacji 2 by� wi�kszy wi�c staje sie "lepsza" permutacja
            permutation1[vertex2] = permutation2[vertex2];
        }
        else
        {
            permutation2[vertex1] = permutation1[vertex1];
            permutation2[vertex2] = permutation1[vertex2];
        }

        double delta_min = pow(deltaMax, 0.0001);

        double beta = (deltaMax - delta_min) / (100000 * deltaMax*delta_min);

        temperature = (temperature/(1+beta*temperature));


        start1 = std::time(NULL);
        LARGE_INTEGER l_int;
        QueryPerformanceCounter(&l_int);
        return double(l_int.QuadPart - counter) / frequency;

        // dodanie czasu
        //finishTime += (double) (timer.stop() / 1000000.0);
    }

    permutation1.clear();
    permutation2.clear();

    // zwrócenie kosztu
    return globalOptimum;
}
