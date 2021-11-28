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


    // instancja grafu
    graph = new Graph();


    while (run) {

        cout << "\n [1] - wczytaj dane z pliku \n"
                " [2] - wyswietl graf \n"
                "  [4] - algorytm SA - symulowane wyzarzanie \n"
                "  [5] - algorytm TS - tabu search \n"
                " [9] - pomiary automatyczne \n"
                " [0] - wyjscie \n";

        cin >> key;
        cout << endl;

        switch (key) {

            case 1:
                cout << "podaj nazwe pliku: ";      // C:\Users\matic\Desktop\br17.atsp  C:\Users\matic\Desktop\ftv170.atsp
                cin >> name;
                graph = new Graph(name);
                break;

            case 2:
                cout << "graf w postaci macierzy sasiedztwa: \n";
                graph->display();
                break;

            case 4:
                if (graph != nullptr) {

                    double maxTemp = 2600.0;    // początkowa temperatura
                    double minTemp = 1.00079;   // minimalna temperatura
                    time_t time = 10;           // czas wykonywania

                    int iter = 1000;          // liczba iteracji
                    int types = 0;            // rodzaj sasiedztwa

                    int choose;
                    bool loop = true;

                    while (loop) {

                        cout << " [1] - ustaw parametry\n"
                                " [2] - rozpocznij algorytm\n"
                                " [0] - wyjdz\n" << endl;
                        cin >> choose;

                        if (choose == 0) {

                            loop = false;
                        }

                        else if (choose == 1) {

                            int x;
                            cout << "1-max temp, 2-min temp, 3-czas, 4-iteracje, 5-sasiedztwo";
                            cin >> x;

                            if (x == 1) {
                                cout << "poczatkowa temperatura: "; cin >> maxTemp;
                            }

                            else if (x == 2) {
                                cout << "minimalna temperatura: "; cin >> minTemp;
                            }

                            else if (x == 3) {
                                cout << "czas [s]: "; cin >> time;
                            }

                            else if (x == 4) {
                                cout << "limit iteracji: "; cin >> iter;
                            }

                            else if (x == 5) {
                                cout << "sasiedztwo: 0-reverse, 1-swap "; cin >> types;
                            }

                            cout << endl;
                        }

                        else if (choose == 2) {

                            SimulatedAnnealing *sa = new SimulatedAnnealing();

                            vector<int> path;
                            path.resize(graph->getSize() + 1);
                            int cost;

                            sa->settingsSimulatedAnnealing(maxTemp, minTemp, time, iter, types);
                            cost = sa->algorithmSimulatedAnnealing(graph->getMatrix(), path);

                            cout << "\nKoszt: " << cost << endl;
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

            case 5:
                if (graph != nullptr) {

                    int cadence = 120;           // kadencja
                    time_t time = 2;                // czas wykonania
                    int divCad = 9;              // dzielnik kadencji (intensyfikacja)
                    int randNodes = 5;           // liczba poczatkowych losowych wierzcholkow przy generowaniu nowej sciezki
                    int types = 0;               // rodzaj sasiedztwa
                    int iter = 5000 ;            // limit iteracji bez poprawy
                    bool diversification = true; // dywersyfikacja
                    int choose;
                    bool loop = true;

                    while (loop) {

                        cout << " [1] - ustaw parametry\n"
                                " [2] - rozpocznij algorytm\n"
                                " [0] - wyjdz\n" << endl;
                        cin >> choose;

                        if (choose == 0) {

                            loop = false;
                        }

                        else if (choose == 1) {

                            int x;
                            cout << "1-kadencja, 2-czas, 3-dzielnik, 4-wierzcholki, 5-sasiedztwo, 6-dywersyfikacja, 7-iteracje  ";
                            cin >> x;

                            if (x == 1) {
                                cout << "kadencja: "; cin >> cadence;
                            }

                            else if (x == 2) {
                                cout << "czas [s]: "; cin >> time;
                            }

                            else if (x == 3) {
                                cout << "dzielnik kadencji: "; cin >> divCad;
                            }

                            else if (x == 4) {
                                cout << "wierzcholki: "; cin >> randNodes;
                            }

                            else if (x == 5) {
                                cout << "sasiedztwo: 0-reverse, 1-swap "; cin >> types;
                            }

                            else if (x == 6) {
                                cout << "dywersyfikacja: true/false"; cin >> diversification;
                            }

                            else if (x == 7) {
                                cout << "iteracje: "; cin >> iter;
                            }

                            cout << endl;
                        }

                        else if (choose == 2) {

                            TabuSearch *ts = new TabuSearch();

                            vector<unsigned int> path;
                            path.resize(graph->getSize() + 1);
                            int cost;

                            ts->settingsTabuSearch(cadence, time, divCad, randNodes, types, diversification, iter);
                            cost = ts->algorithmTabuSearch(graph->getMatrix(), path);

                            cout << "\nKoszt: " << cost << endl;
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