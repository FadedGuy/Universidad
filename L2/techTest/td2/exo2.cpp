#include <iostream>
#include <cmath>
#include <string>

// Parametres de fiabilite
#define N0 1
#define N1 2
#define N2 3

using namespace std;

enum typesMissiles {
    A, B, C, inconnu
};

typesMissiles recon_signature_radar(int count0, int count1, int count2){
    if(count0 < N0 || count1 < N1 || count2 < N2){
        return inconnu;
    }
    if(log(count0) >= log(count1 + (4 * count2))){
        return A;
    }
    if(log(count1) >= log(2 * count2)){
        return B;
    }
    
    return C;
}

int main(){
    string typesMissiles_str[] = {"A", "B", "C", "inconnu"};

    // Tous les noueds
    // int count0 = 0, count1 = 1, count2 = 2;
    // int count0 = 25, count1 = 3, count2 = 4;
    // int count0 = 10, count1 = 15, count2 = 4;
    // int count0 = 3, count1 = 4, count2 = 7;

    // Tous les arcs
    int count0 = 2, count1 = 1, count2 = 5;
    // int count0 = 20, count1 = 3, count2 = 4;
    // int count0 = 11, count1 = 15, count2 = 4;
    // int count0 = 3, count1 = 4, count2 = 7;

    cout << "Missile type: " << typesMissiles_str[recon_signature_radar(count0, count1, count2)] << "\n";

    return 0;
}