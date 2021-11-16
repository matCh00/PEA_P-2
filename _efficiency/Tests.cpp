#include "Tests.h"



void Tests::startAutomaticTests() {

    Graph *graph;
    vector<unsigned int> path;
    int cost;

    // parametry
    vector<int> cadence = {40, 120};       // kadencja
    vector<int> time = {2};                // czas wykonania
    vector<int> divCad = {9};              // dzielnik kadencji (intensyfikacja)
    vector<int> randNodes = {5};           // liczba poczatkowych losowych wierzcholkow przy generowaniu nowej sciezki
    vector<int> types = {0, 1};            // rodzaj sasiedztwa
    vector<int> iter = {5000};             // limit iteracji bez poprawy
    vector<bool> diversification = {true}; // dywersyfikacja


    ofstream file;
    file.open("C:/Users/matic/Desktop/current projects/PEA_P-2/results.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }


    TabuSearch *ts = new TabuSearch();

    // TS

    for (int num = 0; num < 3; num++) {

        if (num == 0)
            graph = new Graph("C:/Users/matic/Desktop/br17.atsp");

        if (num == 1)
            graph = new Graph("C:/Users/matic/Desktop/ftv64.atsp");

        if (num == 2)
            graph = new Graph("C:/Users/matic/Desktop/ftv170.atsp");


        path.resize(graph->getSize() + 1);


        for (int i = 0; i < cadence.size(); i++) {

            for (int j = 0; j < time.size(); j++) {

                for (int k = 0; k < divCad.size(); k++) {

                    for (int l = 0; l < randNodes.size(); l++) {

                        for (int m = 0; m < types.size(); m++) {

                            for (int n = 0; n < diversification.size(); n++) {

                                for (int p = 0; p < iter.size(); p++) {

                                    ts->settingsTabuSearch(cadence[i], time[j], divCad[k], randNodes[l], types[m], diversification[n], iter[p]);
                                    cost = ts->algorithmTabuSearch(graph->getMatrix(), path);

                                    file << "TS:  rozmiar: " << graph->getSize() << " znalezione optimum: " << cost << "  kadencja: " << cadence[i] <<
                                    "  czas: " << time[j] << "  div: " << divCad[k] << "  nodes: " << randNodes[l] << "  sasiedztwo: " << types[m] <<
                                    "  czy dywersyfikacja: " << diversification[n] << "  iter: " << iter[p] << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    // SA


    //file << "SA: " << endl;


    file.close();
}