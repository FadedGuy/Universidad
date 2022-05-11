#include <iostream>

using namespace std;

typedef int ELEMENT;

void look(ELEMENT cle, ELEMENT tab[], int taille, bool &trouve, int A){
    int droit, gauche;
    gauche = 0; 
    droit = taille-1;
    trouve = false;

    while(gauche <= droit && trouve == false){
        A = (droit + gauche) / 2;
        if(tab[A] == cle){
            trouve = true;
        }
        else{
            if(tab[A] < cle){
                gauche = A+1;
            }
            else{
                droit = A-1;
            }
        }
    }
}

int main(){
    // Tous les noeuds
    // ELEMENT cle = 14;
    // ELEMENT cle = 2;
    // ELEMENT cle = 5;
    // ELEMENT cle = 12;
    ELEMENT cle = 1;
    ELEMENT tab[] = {1, 2, 3, 4, 5, 7, 10, 12};

    // Tous les arcs
    // ELEMENT cle = 8;
    // ELEMENT cle = 3;
    // ELEMENT cle = 6;
    // ELEMENT cle = 7;
    // ELEMENT cle = 4;
    // ELEMENT tab[] = {4, 5, 6, 7};    

    // Chemins independants
    // ELEMENT cle = 6;
    // ELEMENT tab[] = {4, 5, 6, 7};

    int taille = sizeof(tab) / sizeof(ELEMENT);
    bool trouve;
    int A;

    look(cle, tab, taille, trouve, A);
    cout << (trouve ? "Trouve" : "Non trouve") << "\n";

    return 0;
}