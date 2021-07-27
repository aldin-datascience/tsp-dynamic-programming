#include "ptp.h"
#include <bits/stdc++.h>
#include <cmath>

Graf::Graf(int broj_cvorova):n(broj_cvorova){
   matrica_susjedstva.resize(n);
   for(int i = 0; i < matrica_susjedstva.size(); i++)
        matrica_susjedstva[i].resize(n);

    // za PTP Dinamičko
    sviPosjeceni = (1 << n) - 1;
    dp.resize((int)pow(2,n), vector<int>(n));

    for(int i = 0; i < (1<<n); i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = -1;
        }
    }
}

Graf::Graf(vector<vector<double>>v){
    n = v.size();
    matrica_susjedstva.resize(n);
    for(int i = 0; i < matrica_susjedstva.size(); i++)
        matrica_susjedstva[i].resize(n);

    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size(); j++){
            matrica_susjedstva[i][j] = v[i][j];
        }
    }

    // za PTP Dinamičko

    sviPosjeceni = (1 << n) - 1;
    dp.resize((int)pow(2,n), vector<int>(n));

    for(int i = 0; i < (1<<n); i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = -1;
        }
    }

}

void Graf::dodajGranu(int u, int v, double tezina) {
    matrica_susjedstva[u][v] = matrica_susjedstva[v][u] = tezina;
}

void Graf::ispisi(){
    for(int i = 0; i < matrica_susjedstva.size(); i++){
        cout << i << " : ";
        for(int j = 0; j < matrica_susjedstva.size(); j++){
            cout << matrica_susjedstva[i][j] << " ";
        }
        cout << endl;
    }
}

int Graf::PTP_Sporo(int pocetni){

    // Sačuvaj sve vrhove osim početnog
    vector<int> vrhovi;
    for(int i = 0; i < n; i++){
        if(i != pocetni)
            vrhovi.push_back(i);
    }

    // Hamiltonov ciklus min. težine
    int min_put = INT_MAX;

    do {

        // Težina trenutnog puta
        int tezina_trenutnog = 0;

        // Izračunaj težinu trenutnog puta
        int k = pocetni;
        for (int i = 0; i < vrhovi.size(); i++) {
            tezina_trenutnog += matrica_susjedstva[k][vrhovi[i]];
            k = vrhovi[i];
        }

        tezina_trenutnog += matrica_susjedstva[k][pocetni];

        // Update min
        min_put = min(min_put, tezina_trenutnog);

    } while (
        next_permutation(vrhovi.begin(), vrhovi.end())
        );

    return min_put;
}

/* Rekurzivno bez DP

int Graf::PTP_Dinamicko(int biti, int trenutni){ // biti (do sada posjećeni gradovi)

    // Bazni slučaj rekurzije, ako su svi gradovi posjećeni vrati težinu od trenutnog nazad do početnog
    if(biti == sviPosjeceni){
        return matrica_susjedstva[trenutni][0];
    }

    int rezultat = INT_MAX;

    // Od trenutnog želimo doći do svih neposjećenih gradova
    for(int i = 0; i < n; i++){
        if((biti&(1 << i)) == 0){ // Ako grad nije posjećen
            // Rezultat je udaljenost od trenutnog do grada (i) + rekurzivno udaljenost grada (i) od ostatka gradova
            int noviRezultat = matrica_susjedstva[trenutni][i] + PTP_Dinamicko(biti|(1 << i), i);
            rezultat = min(rezultat,noviRezultat);
        }
    }

    return rezultat;
}

*/

int Graf::PTP_Dinamicko(int biti, int trenutni){ // biti (do sada posjećeni gradovi)

    // Bazni slučaj rekurzije, ako su svi gradovi posjećeni vrati težinu od trenutnog nazad do početnog
    if(biti == sviPosjeceni){
        return matrica_susjedstva[trenutni][0];
    }

    // Provjera rezultata u dp
    if(dp[biti][trenutni] != -1){
        return dp[biti][trenutni];
    }

    int rezultat = INT_MAX;

    // Od trenutnog želimo doći do svih neposjećenih gradova
    for(int i = 0; i < n; i++){
        if((biti&(1 << i)) == 0){ // Ako grad nije posjećen
            // Rezultat je udaljenost od trenutnog do grada (i) + rekurzivno udaljenost grada (i) od ostatka gradova
            int noviRezultat = matrica_susjedstva[trenutni][i] + PTP_Dinamicko(biti|(1 << i), i);
            rezultat = min(rezultat,noviRezultat);
        }
    }

    // Spašava rezultat u dp i vraća ga
    return dp[biti][trenutni] = rezultat;
}

