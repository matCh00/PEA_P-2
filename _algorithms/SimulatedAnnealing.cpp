#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {

}


SimulatedAnnealing::~SimulatedAnnealing() {

}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
void SimulatedAnnealing::settingsSimulatedAnnealing(double initialTemperature, double minTemperature, int stopTime, int iterationsLimit, double cooling, int neighborhoodType) {

    this->initialTemperature = initialTemperature;
    this->minTemperature = minTemperature;
    this->stopTime = stopTime;
    this->iterationsLimit = iterationsLimit;
    this->cooling = cooling;
    this->neighborhoodType = neighborhoodType;
}



int SimulatedAnnealing::getInitialGreedy(vector<unsigned> &bestTab) {

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

int SimulatedAnnealing::algorithmSimulatedAnnealing(vector<vector<int>> originalMatrix, vector<unsigned int> &bestPath) {

    globalOptimum = 0;
    currentOptimum = 0;
    matrixSize = originalMatrix.size();
    int xxx = 0;/////////
    matrix = originalMatrix;

    vector <unsigned> route;

    globalOptimum = getInitialGreedy(bestRoute);

    //int counter = 0;
    int currentCost = globalOptimum;
    vector <unsigned> currentRoute = bestRoute;

    Timer onboardClock;
    onboardClock.start();

    double temperature = initialTemperature;
    currentOptimum = globalOptimum;
    int balance;
    vector<unsigned> shuffled;

    bool continuing = true;

    while (continuing == true && temperature > minTemperature) {

        for (auto i = 0; i < iterationsLimit; i++)
        {
            shuffled = currentRoute;
            balance = reshufflePath(shuffled, currentRoute);
            currentCost = currentCost + balance;

            if (currentCost < currentOptimum)
            {
                currentRoute = shuffled;
                currentOptimum = currentCost;

            }
            else if (rand() / RAND_MAX < calculateProbability(currentOptimum, currentCost, temperature)) // Metropolis condition
                {
                currentRoute = shuffled;
                currentOptimum = currentCost;
                }
            else {
                currentCost = currentCost - balance;
            }

            cout << "currentOptimum: " << currentOptimum << "     xxx: " << xxx++ << endl;
        }
        //static_cast<double>(temperature = initialTemperature/(1+0.1*counter));

        temperature *= cooling;

        //counter++;

        onboardClock.stop();


        if (onboardClock.read() > stopTime)
            continuing = false;
    }


    bestRoute = currentRoute;
    globalOptimum = currentOptimum;


    bestRoute.clear();
    currentRoute.clear();


    matrix.clear();
    shuffled.clear();
    vector<unsigned>().swap(shuffled);

    return globalOptimum;
}

int SimulatedAnnealing::reshufflePath(vector <unsigned>& shuffled, vector <unsigned>&currentRoute) {

    Randomize r;

    int i, j, balance = 0;

    if (neighborhoodType == 1) { //swap
        do {
            i = r.random_engine(1, matrixSize - 2);
            j = r.random_engine(1, matrixSize - 2);
        } while (i == j || j < i);

        balance = calculateSwap(i, j, currentRoute);

        unsigned buffer = shuffled.at(j);
        shuffled.at(j) = shuffled.at(i);
        shuffled.at(i) = buffer;
    }


    else if (neighborhoodType == 0) {
        do {
            i = r.random_engine(1, matrixSize - 2);
            j = r.random_engine(1, matrixSize - 2);
        } while (i == j || j < i);

        balance = calculateReverse(i, j, currentRoute);

        reverse(shuffled.begin() + i, shuffled.begin() + j + 1);

    }

    return balance;

}

int SimulatedAnnealing::calculateProbability(int newCost, int oldCost, double temperature)
{
    float result;

    result = (exp(-((newCost - oldCost) / temperature)));

    return result;
}



int SimulatedAnnealing::calculateReverse(int i, int j, vector<unsigned> &currentRoute) {

    int balance;
    balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)] - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
    balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)] + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];

    for (int k = i; k < j; k++)
        balance = balance - matrix[currentRoute.at(k)][currentRoute.at(k + 1)] + matrix[currentRoute.at(k + 1)][currentRoute.at(k)];

    return balance;
}



int SimulatedAnnealing::calculateSwap(int i, int j, vector<unsigned> &currentRoute) {

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