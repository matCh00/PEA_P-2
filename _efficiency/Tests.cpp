#include "Tests.h"


ofstream file;
ofstream file2;


void Tests::startAutomaticTests() {

    file.open("C:/Users/matic/Desktop/current projects/PEA_P-2/resultsSA.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }

    SA();

    file.close();


    file2.open("C:/Users/matic/Desktop/current projects/PEA_P-2/resultsTS.txt");

    if(!file2.is_open()) {

        cout << "plik nie jest otwarty";
    }

    TS();

    file2.close();
}



void Tests::SA() {

    Graph *graph;
    vector<int> path;
    int cost;
    double exeTime;

    // parametry SA
    vector<double> initTemp = {2500.0};
    vector<double> minTemp = {1.0008};
    vector<time_t> timeSA = {10, 30, 60};


    // SA
    SimulatedAnnealing *sa = new SimulatedAnnealing();

    for (int num = 0; num < 3; num++) {

        if (num == 0)
            graph = new Graph("C:/Users/matic/Desktop/PEA/sourcesAsymmetricTSP/br17.atsp");

        if (num == 1)
            graph = new Graph("C:/Users/matic/Desktop/PEA/sourcesAsymmetricTSP/ft70.atsp");

        if (num == 2)
            graph = new Graph("C:/Users/matic/Desktop/PEA/sourcesAsymmetricTSP/ftv170.atsp");


        path.resize(graph->getSize() + 1);


        for (int i = 0; i < initTemp.size(); i++) {

            for (int j = 0; j < minTemp.size(); j++) {

                for (int n = 0; n < timeSA.size(); ++n) {

                    sa->settingsSimulatedAnnealing(initTemp[i], minTemp[j], timeSA[n]);
                    exeTime = sa->algorithmSimulatedAnnealing(graph->getMatrix(), path, cost);

                    file << "SA:  rozmiar: " << graph->getSize() << " koszt: " << cost << " czas wykonania: " << exeTime <<
                    "  max temp: " << initTemp[i] << "  min temp: " << minTemp[j] << "czas: " << timeSA[n] << endl;
                }
            }
        }
    }

    initTemp.clear();
    minTemp.clear();
    timeSA.clear();
}



void Tests::TS() {

    Graph *graph;
    vector<int> path;
    int cost;
    double exeTime;

    // parametry TS
    vector<int> cadence = {120};
    vector<int> divCad = {9};
    vector<time_t> timeTS = {10, 30, 60};


    // TS
    TabuSearch *ts = new TabuSearch();

    for (int num = 0; num < 3; num++) {

        if (num == 0)
            graph = new Graph("C:/Users/matic/Desktop/PEA/sourcesAsymmetricTSP/br17.atsp");

        if (num == 1)
            graph = new Graph("C:/Users/matic/Desktop/PEA/sourcesAsymmetricTSP/ft70.atsp");

        if (num == 2)
            graph = new Graph("C:/Users/matic/Desktop/PEA/sourcesAsymmetricTSP/ftv170.atsp");


        path.resize(graph->getSize() + 1);


        for (int i = 0; i < cadence.size(); i++) {

            for (int j = 0; j < divCad.size(); j++) {

                for (int k = 0; k < timeTS.size(); k++) {

                    ts->settingsTabuSearch(cadence[i], divCad[j], timeTS[k]);
                    exeTime = ts->algorithmTabuSearch(graph->getMatrix(), path, cost);

                    file2 << "TS:  rozmiar: " << graph->getSize() << " koszt: " << cost << " czas wykonania: " << exeTime <<
                    "  kadencja: " << cadence[i] << "  div: " << divCad[k] << "  czas: " << timeTS[j] <<endl;
                }
            }
        }
    }

    cadence.clear();
    timeTS.clear();
    divCad.clear();
}


