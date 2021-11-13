#include "Menu.h"



Menu::Menu() {

}



Menu::~Menu() {

}


long long int read_QPC2() {

    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((long long int)count.QuadPart);
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
                "  [5] - algorytm SA - symulowane wyżarzanie \n"
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



                    int* path = new int[graph->getSize() + 1];
                    int cost;

                    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                    start = read_QPC2();



                    elapsed = read_QPC2() - start;
                    cout << "Czas: " << setprecision(5) << (1000000.0 * elapsed) / frequency << " us" << endl;

                    cout << "Koszt: " << cost << endl;
                    cout << "Sciezka: " ;
                    for (int i = 0; i < graph->getSize(); i++)
                        cout << path[i] << " -> ";
                    cout << path[graph->getSize()];

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

                    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                    start = read_QPC2();



                    elapsed = read_QPC2() - start;
                    cout << "Czas: " << setprecision(5) << (1000000.0 * elapsed) / frequency << " us" << endl;

                    cout << "Koszt: " << cost << endl;
                    cout << "Sciezka: " ;
                    for (int i = 0; i < graph->getSize(); i++)
                        cout << path[i] << " -> ";
                    cout << path[graph->getSize()];

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