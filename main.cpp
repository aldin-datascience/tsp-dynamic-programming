#include<iostream>
#include"ptp.h"
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

    double udaljenost(double x1, double y1, double x2, double y2)
    {
        return sqrt(pow(x2 - x1, 2) +
                    pow(y2 - y1, 2) * 1.0);
    }

int main(){
    // 6x6 -> ocekivani rezultat : 1248

    /*
    vector<vector<double>>v{
        {0, 64 ,378,519,434,200},
        {64,0,318 ,455, 375,164},
        {378,318, 0,170,265,344},
        {519,455,170,0 ,223,428},
        {434,375,265,223,0,273},
        {200,164,344,428,273,0}
    };
    */


    // Ucitavanje 29 gradova W.Sahare

    vector<vector<double>> wSahara(29, vector<double>(29));

    ifstream fajl("wi29.tsp");

    double x, y;

    int i = 0;

    vector<pair<double,double>>tacke(29);

    while (fajl >> x >> y){
        tacke[i].first = x;
        tacke[i].second = y;
        i++;
    }

    fajl.close();

    int p = 0, q = 0;

    for(int i = 0; i < tacke.size()-1; i++){
        for(int j = 0; j < tacke.size(); j++){
            wSahara[i][j] = wSahara[j][i] = udaljenost(tacke[i].first, tacke[i].second, tacke[j].first, tacke[j].second);
        }
    }

    /* // Ispis 29 x 29

    for(int i = 0; i < wSahara.size(); i++){
        for(int j = 0; j < wSahara.size(); j++){
            cout << wSahara[i][j] << " ";
        }
        cout << endl;
    }
    */

    /* // Ispis tačaka

    for(int i = 0; i < tacke.size(); i++){
        cout << tacke[i].first << " " << tacke[i].second << endl;
    }
    */

    vector<vector<double>>v(20, vector<double>(20)); // Skoro 4 minute za 25 x 25 matricu

    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            if(i == j)
                v[i][j] = 0;
            else
                v[i][j] = rand() % 200 + 50;
        }
    }

    Graf G(v);

    cout << "Hamiltonov ciklus min. tezine: " << G.PTP_Dinamicko(1,0) << endl;

    // cout << endl << G.PTP_Sporo(0) << endl;

    return 0;
}
