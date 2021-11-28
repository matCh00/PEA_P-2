#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {

}


SimulatedAnnealing::~SimulatedAnnealing() {

}


// TODO opisać działanie algorytmu - komentarze i ewentualnie pozmieniać nazwy
// TODO skopiować od madarasza
void SimulatedAnnealing::settingsSimulatedAnnealing(double initialTemperature, double minTemperature, time_t stopTime, int iterationsLimit, double cooling, int neighborhoodType) {

    this->initialTemperature = initialTemperature;
    this->minTemperature = minTemperature;
    this->stopTime = stopTime;
    this->iterationsLimit = iterationsLimit;
    this->cooling = cooling;
    this->neighborhoodType = neighborhoodType;
}



void SimulatedAnnealing::start()
{
    LARGE_INTEGER l_int;

    QueryPerformanceFrequency(&l_int);
    frequency = double(l_int.QuadPart);

    QueryPerformanceCounter(&l_int);
    counter = l_int.QuadPart;
}

void SimulatedAnnealing::setOptimum(int opt)
{
    optimum = opt;
}

double SimulatedAnnealing::stop()
{
    LARGE_INTEGER l_int;
    QueryPerformanceCounter(&l_int);
    return double(l_int.QuadPart - counter) / frequency;
}

int SimulatedAnnealing::route(vector<int> &permutation) {

    int cost = 0;

    //zliczanie drogi calkowitej dla danej permutacji
    for (int i = 0; i < cities - 1; i++) {
        cost += matrix[permutation[i]][permutation[i + 1]];
    }

    //droga od ostatniego do pierwszego miasta
    cost += matrix[permutation[cities - 1]][permutation[0]];

    return cost;
}

//tworzenie permutacji
void SimulatedAnnealing::permutation(vector<int> &perm) {

    vector<int> num;
    num.resize(cities);

    int random;

    for (int i = 0; i < cities; i++)
    {
        num[i] = i;
    }


    for (int i = cities; i > 0; i--)
    {
        random = rand() % i; //losuje jedno miasto
        perm[i - 1] = num[random];
        num[random] = num[i - 1];
    }

    for (int i = 0; i < cities; i++)
    {
        if (perm[i] == 0) {
            auto temp = perm[0];
            perm[0] = 0;
            perm[i] = temp;
        }
    }


//    for (int i = 0; i < cities; i++)
//    {
//        cout<<perm[i]<<"  ";
//    }cout<<endl;

    num.clear();



//    Randomize r;
//
//    int i, j, balance = 0;
//
//    if (neighborhoodType == 1) { //swap
//        do {
//            i = r.random_engine(1, cities - 2);
//            j = r.random_engine(1, cities - 2);
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
//            i = r.random_engine(1, cities - 2);
//            j = r.random_engine(1, cities - 2);
//        } while (i == j || j < i);
//
//        reverse(perm.begin() + i, perm.begin() + j + 1);
//    }
}



bool SimulatedAnnealing::probability(int length, int length1, double temperature) {

    double p = pow(e, ((-1 * ((long long)length1 - (long long)length)) / temperature));

    double r = (double)rand() / RAND_MAX; // wybieramy cyfr� z przedzia�u <0,1>

    return (r < p); //jezeli prawdopodobienstwo ze wzoru jest wieksze od losowo wybranej liczby z przedzialu<0,1>

}

int SimulatedAnnealing::algorithmSimulatedAnnealing(vector<vector<int>> matrix1, vector<int> &bestPath) {

    matrix = matrix1;
    cities = matrix1.size();

    int solution = INT_MAX;

    start();

    vector<int> permutation1;
    permutation1.resize(cities);

    vector<int> permutation2;
    permutation2.resize(cities);

    int oldOptimum = 0;
    int city1, city2;
    double temperature, delta_max = 0, delta, cost1, cost2;;


    for (int i = 0; i < cities; i++)
    {
        permutation(permutation1);
        permutation(permutation2);
        delta = abs(route(permutation1) - route(permutation2));
        if (delta > delta_max)
        {
            delta_max = delta;
        }

        permutation1.clear();
        permutation2.clear();

        permutation1.resize(cities);
        permutation2.resize(cities);
    }

    temperature = delta_max;

    //tworze permutacje i obliczam koszt drogi dla niej
    permutation(permutation1);
    cost1 = route(permutation1);

    //tworze zapasowa tablice permutacja2
    for (int i = 0; i < cities; i++)
    {
        permutation2[i] = permutation1[i];
    }

    std::time_t finish;
    std::time_t start1 = std::time(NULL);

    finish = start1 + stopTime;

    int counter = 0;;

    while (temperature > min_temperature && start1<finish )
    {
        counter++;
        do
        {
            //losowanie 2 nowych miast do zamiany w permutacji
            city1 = rand() % cities;
            city2 = rand() % cities;

        } while (city1 == city2 || city1 == 0 || city2 == 0);//petla wykonuje sie dopoki miasta nie beda rozne

        //zamiana miast
        permutation2[city2] = permutation1[city1];
        permutation2[city1] = permutation1[city2];


        cost2 = route(permutation2);

        if (cost2 <= cost1 || probability(cost1, cost2, temperature))
        {
            cost1 = cost2;//
            if (cost1 <= solution)
            {
                solution = cost1;
                path = permutation2;
            }

            permutation1[city1] = permutation2[city1]; //koszt dla permutacji 2 by� wi�kszy wi�c staje sie "lepsza" permutacja
            permutation1[city2] = permutation2[city2];
        }
        else
        {
            permutation2[city1] = permutation1[city1];
            permutation2[city2] = permutation1[city2];
        }

        double delta_min = pow(delta_max, 0.0001);

        double beta = (delta_max - delta_min) / (100000 * delta_max*delta_min);

        temperature = (temperature/(1+beta*temperature));

        start1 = std::time(NULL);
        stop();
    }


    path.push_back(0);
    bestPath = path;

    permutation1.clear();
    permutation2.clear();

    return solution;
}