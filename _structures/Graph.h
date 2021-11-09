// plik reprezentujący graf

#ifndef PEA_P_1_GRAPH_H
#define PEA_P_1_GRAPH_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <time.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <queue>
#include <numeric>
#include "../_extra/Randomize.h"

using namespace std;


class Graph {

private:

    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int size;

public:

    // pusty konstruktor
    Graph();

    // destruktor
    ~Graph();

    // konstruktor który generuje losowy graf
    Graph(int size);

    // konstruktor który przypisuje wskaźnik na macierz
    Graph(Graph* graph);

    // konstruktor który wczytuje dane z pliku
    Graph(string filePath);

    // wypisanie grafu w postaci macierzy sąsiedztwa
    void display();

    // wypisanie ścieżki z podanej tablicy węzłów
    void displayPath(vector<int> path);

    // ustawienie komórki
    void setCell(int x, int y, int value);

    // pobranie komórki
    int getCell(int x, int y);

    // pobranie wielkości macierzy
    int getSize();

    // skopiowanie macierzy
    void copyMatrix(Graph* old);

    // pobranie macierzy
    vector<vector<int>> getMatrix();
};


#endif