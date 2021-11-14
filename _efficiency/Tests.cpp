#include "Tests.h"



long long int read_QPC() {

    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((long long int)count.QuadPart);
}



void Tests::startTests() {

    Graph *graph = new Graph();
    int instanceSize;
    int* path;
    int reps;
    int alg;
    int key = 1;
    long long int frequency, start, elapsed;
    long long int sum = 0;


    ofstream file;
    file.open("C:/Users/matic/Desktop/current projects/PEA_P-2/results.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }



    cout << "podaj liczbe miast:  ,  podaj liczbe powtorzen:  ,  wybierz: [1] - TS,  [2] - SA";
    cin >> instanceSize; cin >> reps; cin >> alg;


    while (key == 1) {


        for (int i = 0; i < reps; ++i) {

            graph = new Graph(instanceSize);
            path = new int[instanceSize + 1];


            if (alg == 1) {

                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();



                elapsed = read_QPC() - start;
                sum += (1000000.0 * elapsed) / frequency;

                file << "TS: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
            }


            if (alg == 2) {

                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();



                elapsed = read_QPC() - start;
                sum += (1000000.0 * elapsed) / frequency;

                file << "SA: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
            }

            sum = 0;
        }


        cout << "[x] - wyjscie,  [1] - dalej"; cin >> key;
        if (key == 1) {

            cout << "podaj liczbe miast:  ,  podaj liczbe powtorzen:  ,  wybierz: [1] - TS,  [2] - SA";
            cin >> instanceSize; cin >> reps; cin >> alg;
        }
    }


    file.close();
}



void Tests::startAutomaticTests() {

    Graph *graph;
    int* path;
    long long int frequency, start, elapsed;
    long long int sum = 0;


    ofstream file;
    file.open("C:/Users/matic/Desktop/current projects/PEA_P-2/results.txt");

    if(!file.is_open()) {

        cout << "plik nie jest otwarty";
    }


    int reps = 100;
    int instanceSize = 4;


    for (int i = 0; i < 14; ++i) {

        instanceSize += 1;


        for (int i = 0; i < reps; ++i) {

            graph = new Graph(instanceSize);

            // TS


            path = new int[instanceSize + 1];

            QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
            start = read_QPC();



            elapsed = read_QPC() - start;
            sum += (1000000.0 * elapsed) / frequency;
        }
        file << "TS: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
        sum = 0;



        for (int i = 0; i < reps; ++i) {

            graph = new Graph(instanceSize);

            // SA


            path = new int[instanceSize + 1];

            QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
            start = read_QPC();



            elapsed = read_QPC() - start;
            sum += (1000000.0 * elapsed) / frequency;
        }
        file << "SA: " << instanceSize << " miast,  czas [us]:  suma: " << setprecision(0) << sum << ", średnia: " << setprecision(0) << sum / reps << endl;
        sum = 0;
    }


    file.close();
}