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
    int cities;
    long long int frequency, start, elapsed;


    // instancja grafu
    graph = new Graph();


    while (run) {

        cout << "\n [1] - wczytaj dane z pliku \n"
                " [2] - generuj losowy graf \n"
                " [3] - wyswietl graf \n"
                "  [4] - algorytm TS - tabu search \n"
                "  [5] - algorytm SA - symulowane wyzarzanie \n"
                " [9] - badanie efektywnosci \n"
                " [0] - wyjscie \n";

        cin >> key;
        cout << endl;

        switch (key) {

            case 1:
                cout << "podaj nazwe pliku: ";
                cin >> name;
                graph = new Graph(name);
                break;

            case 2:
                cout << "podaj ilosc miast: ";
                cin >> cities;
                graph = new Graph(cities);
                break;

            case 3:
                cout << "graf w postaci macierzy sasiedztwa: \n";
                graph->display();
                break;

            case 4:
                if (graph != nullptr) {

                    int cadenceTab[1] = { 120 }; //kadencja
                    int timeTab[1] = { 2 };//czas wykonania algorytmu
                    int iterTab[1] = { 5000 };//limit iteracji bez poprawy, po osiagnieciu ktorego jest generowana nowa sciezka
                    int divCadTab[1] = {9}; //dzielnik kadencji (intensyfikacja) w przypadku znalezienia globalnie najlepszego rozwiazania
                    int randNodesTab[1] = { 5 };//liczba poczatkowych losowych wierzcholkow przy generowaniu nowej sciezki
                    int typesTab[1] = {1};//rodzaj sasiedztwa

                    TabuSearch *ts = new TabuSearch();

                    int* path = new int[graph->getSize() + 1];
                    int cost;

                    ts->setSettingsTabu(cadenceTab[0], timeTab[0], iterTab[0], divCadTab[0], randNodesTab[0], typesTab[0]);
                    cost = ts->algorithmTabuSearch(graph->getMatrix());

                    cout << "Koszt: " << cost << endl;
//                    cout << "Sciezka: " ;
//                    for (int i = 0; i < graph->getSize(); i++)
//                        cout << path[i] << " -> ";
//                    cout << path[graph->getSize()];

                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 5:
                if (graph != nullptr) {


                    int* path = new int[graph->getSize() + 1];
                    int cost;


//                    cout << "Koszt: " << cost << endl;
//                    cout << "Sciezka: " ;
//                    for (int i = 0; i < graph->getSize(); i++)
//                        cout << path[i] << " -> ";
//                    cout << path[graph->getSize()];

                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 9:

                system("PAUSE");
                Tests tests;
                tests.startTests();
                //tests.startAutomaticTests();
                break;

            case 0:
                run = false;
                break;

            default:
                break;

        }
    }
}