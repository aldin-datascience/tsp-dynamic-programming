#ifndef PTP_H
#define PTP_H

#include <iostream>
#include <vector>

using namespace std;

class Graf{
    int n; // broj čvorova
    vector<vector<double>> matrica_susjedstva;
    int sviPosjeceni; // Za bazni slučaj rekurzivnog DP algoritma
    vector<vector<int>>dp; // DP 2^n * n matrica za spašavanje rezultata u algoritmu

public:
    Graf(int broj_cvorova); // Kreira graf sa n čvorova
    Graf(vector<vector<double>>); // Kreira graf sa listom susjedstva jednakoj proslijeđenoj matrici
    void dodajGranu(int u, int v, double tezina); // Dodaje granu
    void ispisi(); // Ispis matrice susjedstva

    int PTP_Sporo(int); // O(n!)
    int PTP_Dinamicko(int,int); // O(2^n * n^2)
};

#endif // PTP_H
