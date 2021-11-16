#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {

}


SimulatedAnnealing::~SimulatedAnnealing() {

}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
void SimulatedAnnealing::settingsSimulatedAnnealing() {

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

void SimulatedAnnealing::algorithmSimulatedAnnealing(int a, int **TSPMatrix) {

    iterations = 0;
    optMin = 0;
    currentOptMin = 0;
    //int optimum = INT_MAX;
    matrixSize = a;
    matrix = new int *[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = new int[matrixSize];
        for (int j = 0; j < matrixSize; j++)
            matrix[i][j] = TSPMatrix[i][j];
    }
    vector <unsigned> route;

    optMin = getInitialGreedy(bestRoute);

    int counter = 0;
    //cout << "optMin = " << optMin << endl;
    vector <unsigned> currentRoute = bestRoute;
    //displayRoute(currentRoute);
    Timer onboardClock;
    int currentCost = optMin;
    onboardClock.start();

    double temperature = initialTemperature;
    currentOptMin = optMin;
    int balance;
    vector<unsigned> shuffled;

    do
    {
        for (auto i = 0; i < iterationsLimit; i++)
        {
            shuffled = currentRoute;
            balance = reshufflePath(shuffled, currentRoute);
            currentCost = currentCost + balance;

            if (currentCost < currentOptMin)
            {
                currentRoute = shuffled;
                currentOptMin = currentCost;
                //if (currentOptMin < optimum)
                //	optimum = currentOptMin;
            }
            else if (static_cast<float>(rand()) / RAND_MAX < calculateProbability(currentOptMin, currentCost, temperature)) // Metropolis condition
                {
                currentRoute = shuffled;
                currentOptMin = currentCost;
                }
            else {
                currentCost = currentCost - balance;
            }
            iterations++;
        }
        static_cast<double>(temperature = initialTemperature/(1+0.1*counter));
        //cout << "temperature = " << temperature << endl;
        counter++;
    } while (temperature>minTemperature);
    //cout << "Iteracje = " << counter << endl;
    onboardClock.stop();
    time = onboardClock.read();
    bestRoute = currentRoute;
    optMin = currentOptMin;


    bestRoute.clear();
    currentRoute.clear();


    for (int i = 0; i < matrixSize; i++) {
        delete[]matrix[i];
    }
    delete[]matrix;

    //cout << "rzeczywiste: " << optimum << endl;
    shuffled.clear();
    vector<unsigned>().swap(shuffled);
}

int SimulatedAnnealing::reshufflePath(vector <unsigned>& shuffled, vector <unsigned>&currentRoute) {

    random_device randomSrc;
    default_random_engine randomGen(randomSrc());
    uniform_int_distribution<> nodeRand(1, matrixSize - 2);
    int i, j, balance = 0;

    if (neighborhoodType == 1) { //swap
        do {
            i = nodeRand(randomGen);
            j = nodeRand(randomGen);
        } while (i == j || j < i);

        calculateSwap(i, j, balance, currentRoute);

        unsigned buffer = shuffled.at(j);
        shuffled.at(j) = shuffled.at(i);
        shuffled.at(i) = buffer;
    }


    else if (neighborhoodType == 0) {
        do {
            i = nodeRand(randomGen);
            j = nodeRand(randomGen);
        } while (i == j || j < i);

        calculateReverse(i, j, balance, currentRoute);

        reverse(shuffled.begin() + i, shuffled.begin() + j + 1);

    }
    //cout << "balance " << balance << endl;
    return balance;

}

int SimulatedAnnealing::calculateProbability(int newCost, int oldCost, double temperature)
{
    float result;

    result = (exp(-(static_cast<float>((newCost - oldCost) / temperature))));

    return result;
}



int SimulatedAnnealing::getBestNeighborhoodReverse(int &bestI, int &bestJ, vector<unsigned> &currentRoute) {

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



void SimulatedAnnealing::reverseVector(int a, int b, vector<unsigned> &currentRoute) {

    reverse(currentRoute.begin() + a, currentRoute.begin() + b + 1);
}



int SimulatedAnnealing::calculateReverse(int i, int j, vector<unsigned> &currentRoute) {

    int balance;
    balance = 0 - matrix[currentRoute.at(i - 1)][currentRoute.at(i)] - matrix[currentRoute.at(j)][currentRoute.at(j + 1)];
    balance = balance + matrix[currentRoute.at(i - 1)][currentRoute.at(j)] + matrix[currentRoute.at(i)][currentRoute.at(j + 1)];

    for (int k = i; k < j; k++)
        balance = balance - matrix[currentRoute.at(k)][currentRoute.at(k + 1)] + matrix[currentRoute.at(k + 1)][currentRoute.at(k)];

    return balance;
}



int SimulatedAnnealing::getBestNeighborhoodSwap(int &bestI, int &bestJ, vector<unsigned> &currentRoute) {

    int bestBalance = INT_MAX;
    int balance;
    bool ifTabu;
    bestI = 0;
    bestJ = 0;


    for (int i = 1; i < matrixSize - 1; i++) {
        for (int j = i + 1; j < matrixSize; j++) {

            balance = calculateSwap(i, j, currentRoute);

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



void SimulatedAnnealing::swapVector(int a, int b, vector<unsigned> &currentRoute) {

    unsigned buffer = currentRoute.at(b);
    currentRoute.at(b) = currentRoute.at(a);
    currentRoute.at(a) = buffer;
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