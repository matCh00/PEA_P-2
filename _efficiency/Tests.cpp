#include "Tests.h"



ofstream file;


void Tests::startAutomaticTests() {

    file.open("C:/Users/matic/Desktop/current projects/PEA_P-2/results.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }

    SA();
    TS();

    file.close();
}



void Tests::TS() {

    Graph *graph;
    vector<unsigned int> path;
    int cost;

    // parametry TS
    vector<int> cadence = {40, 120};        // kadencja
    vector<int> timeTS = {3};               // czas wykonania
    vector<int> divCad = {9};               // dzielnik kadencji (intensyfikacja)
    vector<int> randNodes = {5};            // liczba poczatkowych losowych wierzcholkow przy generowaniu nowej sciezki
    vector<int> typesTS = {0};           // rodzaj sasiedztwa
    vector<int> iterTS = {5000};            // limit iteracji bez poprawy
    vector<bool> diversification = {true};  // dywersyfikacja


    // TS
    TabuSearch *ts = new TabuSearch();

    for (int num = 0; num < 3; num++) {

        if (num == 0)
            graph = new Graph("C:/Users/matic/Desktop/br17.atsp");

        if (num == 1)
            graph = new Graph("C:/Users/matic/Desktop/ftv64.atsp");

        if (num == 2)
            graph = new Graph("C:/Users/matic/Desktop/ftv170.atsp");


        path.resize(graph->getSize() + 1);


        for (int i = 0; i < cadence.size(); i++) {

            for (int j = 0; j < timeTS.size(); j++) {

                for (int k = 0; k < divCad.size(); k++) {

                    for (int l = 0; l < randNodes.size(); l++) {

                        for (int m = 0; m < typesTS.size(); m++) {

                            for (int n = 0; n < diversification.size(); n++) {

                                for (int p = 0; p < iterTS.size(); p++) {

                                    ts->settingsTabuSearch(cadence[i], timeTS[j], divCad[k], randNodes[l], typesTS[m], diversification[n], iterTS[p]);
                                    cost = ts->algorithmTabuSearch(graph->getMatrix(), path);

                                    file << "TS:  rozmiar: " << graph->getSize() << " znalezione optimum: " << cost << "  kadencja: " << cadence[i] <<
                                    "  czas: " << timeTS[j] << "  div: " << divCad[k] << "  nodes: " << randNodes[l] << "  sasiedztwo: " << typesTS[m] <<
                                    "  czy dywersyfikacja: " << diversification[n] << "  iter: " << iterTS[p] << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cadence.clear();
    timeTS.clear();
    divCad.clear();
    randNodes.clear();
    typesTS.clear();
    diversification.clear();
    iterTS.clear();
}



void Tests::SA() {

    Graph *graph;
    vector<unsigned int> path;
    int cost;

    // parametry SA
    vector<double> initTemp = {10.0, 150.0};  // początkowa temperatura
    vector<double> minTemp = {0.001};            // minimalna temperatura
    vector<int> timeSA = {3};                  // czas wykonania
    vector<int> iterSA = {100};                // liczba iteracji
    vector<double> cooling = {0.999};          // współczynnik chłodzenia
    vector<int> typesSA = {0};              // rodzaj sasiedztwa



    // SA
    SimulatedAnnealing *sa = new SimulatedAnnealing();

    for (int num = 0; num < 3; num++) {

        if (num == 0)
            graph = new Graph("C:/Users/matic/Desktop/br17.atsp");

        if (num == 1)
            graph = new Graph("C:/Users/matic/Desktop/ftv64.atsp");

        if (num == 2)
            graph = new Graph("C:/Users/matic/Desktop/ftv170.atsp");


        path.resize(graph->getSize() + 1);


        for (int i = 0; i < initTemp.size(); i++) {

            for (int j = 0; j < minTemp.size(); j++) {

                for (int n = 0; n < timeSA.size(); ++n) {

                    for (int k = 0; k < iterSA.size(); k++) {

                        for (int l = 0; l < cooling.size(); l++) {

                            for (int m = 0; m < typesSA.size(); m++) {

                                sa->settingsSimulatedAnnealing(initTemp[i], minTemp[j], timeSA[n], iterSA[k], cooling[l], typesSA[m]);
                                cost = sa->algorithmSimulatedAnnealing(graph->getMatrix(), path);

                                file << "SA:  rozmiar: " << graph->getSize() << " znalezione optimum: " << cost << "  początkowa temp: " << initTemp[i] <<
                                "  minimalna temp: " << minTemp[j] << "czas: " << timeSA[n] << "  iter: " << iterSA[k] << "  cooling: " << cooling[l] <<
                                "  sasiedztwo: " << typesSA[m] << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    initTemp.clear();
    minTemp.clear();
    iterSA.clear();
    timeSA.clear();
    cooling.clear();
    typesSA.clear();
}


