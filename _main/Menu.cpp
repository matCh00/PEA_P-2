#include "Menu.h"



Menu::Menu() {

}



Menu::~Menu() {

}



void Menu::startMenu() {

    // do menu
    int key;
    bool run = true;
    string name;

    // defaultowe ustawienia algorytmu
    maxTemp = 2600.0;
    minTemp = 1.00079;
    timeSA = 5;
    cadence = 120;
    timeTS = 5;
    divCadence = 9;

    // instancja grafu
    graph = new Graph();


    while (run) {

        cout << "\n [1] - wczytaj dane z pliku \n"
                "  [2] - algorytm SA - symulowane wyzarzanie \n"
                "  [3] - algorytm TS - tabu search \n"
                " [9] - pomiary automatyczne \n"
                " [0] - wyjscie \n";

        cin >> key;
        cout << endl;

        switch (key) {

            case 1:
                cout << "podaj nazwe pliku wraz z rozszerzeniem: ";      // C:\Users\matic\Desktop\br17.atsp  C:\Users\matic\Desktop\ftv170.atsp
                cin >> name;
                graph = new Graph(name);
                break;

            case 2:
                if (graph != nullptr) {

                    int choose;
                    bool loop = true;

                    while (loop) {

                        cout << " [1] - pokaz parametry\n"
                                " [2] - ustaw parametry\n"
                                " [3] - rozpocznij algorytm\n"
                                " [0] - wyjdz\n" << endl;
                        cin >> choose;

                        if (choose == 0) {

                            loop = false;
                        }

                        else if (choose == 1) {

                            cout << " poczatkowa temperatura: " << maxTemp <<
                                    "\n minimalna temperatura: " << minTemp <<
                                    "\n czas [s]: " << timeSA << endl << endl;
                        }

                        else if (choose == 2) {

                            int x;
                            cout << "1) max temp, 2) min temp, 3) czas  ";
                            cin >> x;

                            if (x == 1) {
                                cout << "poczatkowa temperatura: "; cin >> maxTemp;
                            }

                            else if (x == 2) {
                                cout << "minimalna temperatura: "; cin >> minTemp;
                            }

                            else if (x == 3) {
                                cout << "czas [s]: "; cin >> timeSA;
                            }

                            cout << endl;
                        }

                        else if (choose == 3) {

                            SimulatedAnnealing *sa = new SimulatedAnnealing();

                            vector<int> path(graph->getSize() + 1);
                            int cost;
                            double exeTime;

                            sa->settingsSimulatedAnnealing(maxTemp, minTemp, timeSA);
                            exeTime = sa->algorithmSimulatedAnnealing(graph->getMatrix(), path, cost);

                            cout << "\nCzas: " << exeTime << " s" << endl;
                            cout << "Koszt: " << cost << endl;
                            cout << "Sciezka: " ;
                            for (int i = 0; i < graph->getSize(); i++)
                                cout << path[i] << " -> ";
                            cout << path[graph->getSize()] << endl << endl;
                        }
                    }
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 3:
                if (graph != nullptr) {

                    int choose;
                    bool loop = true;

                    while (loop) {

                        cout << " [1] - pokaz parametry\n"
                                " [2] - ustaw parametry\n"
                                " [3] - rozpocznij algorytm\n"
                                " [0] - wyjdz\n" << endl;
                        cin >> choose;

                        if (choose == 0) {

                            loop = false;
                        }

                        else if (choose == 1) {

                            cout << " kadencja: " << cadence <<
                                 "\n dzielnik kadencji: " << divCadence <<
                                 "\n czas [s]: " << timeTS << endl << endl;
                        }

                        else if (choose == 2) {

                            int x;
                            cout << "1) kadencja, 2) dzielnik, 3) czas  ";
                            cin >> x;

                            if (x == 1) {
                                cout << "kadencja: "; cin >> cadence;
                            }

                            else if (x == 2) {
                                cout << "dzielnik kadencji: "; cin >> divCadence;
                            }

                            else if (x == 3) {
                                cout << "czas [s]: "; cin >> timeTS;
                            }

                            cout << endl;
                        }

                        else if (choose == 3) {

                            TabuSearch *ts = new TabuSearch();

                            vector<int> path(graph->getSize() + 1);
                            int cost;
                            double exeTime;

                            ts->settingsTabuSearch(cadence, divCadence, timeTS);
                            exeTime = ts->algorithmTabuSearch(graph->getMatrix(), path, cost);

                            cout << "\nCzas: " << exeTime << " s" << endl;
                            cout << "Koszt: " << cost << endl;
                            cout << "Sciezka: " ;
                            for (int i = 0; i < graph->getSize(); i++)
                                cout << path[i] << " -> ";
                            cout << path[graph->getSize()] << endl << endl;
                        }
                    }
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 9:

                system("PAUSE");
                Tests tests;
                tests.startAutomaticTests();
                break;

            case 0:
                run = false;
                break;

            default:
                break;

        }
    }
}