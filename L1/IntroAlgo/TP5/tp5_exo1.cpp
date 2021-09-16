#include <iostream>
#include <stdlib.h>
using namespace std;
#define tailleJeu 3

void initialiserGrille(int mat[][tailleJeu]){
    int i, j;
    for(i = 0; i < tailleJeu; i++){
        for(j = 0; j < tailleJeu; j++){
            mat[i][j] = 0;
        }
    }
}

void afficherGrille(int mat[][tailleJeu]){
    int i, j;
    for(i = 0; i < tailleJeu; i++){
        cout<<"";
        for(j = 0; j < tailleJeu; j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<"\n";
    }
}

bool verifierGagne(int mat[][tailleJeu], int x, int y, int role){
    int cnt1, cnt2, i;
    cnt1 = 0;
    cnt2 = 0;
    for(i = 0; i < tailleJeu; i++){
        if(mat[x][i] == role){
            cnt1++;
        }
        if(mat[i][y] == role){
            cnt2++;
        }
    }

    if(y2 - y1 == x2 - x1){
        cout<<"Diag\n";
    }
    else{
        cout<<"Algo\n";
    }

    if(cnt1 == tailleJeu || cnt2 == tailleJeu){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    int grille[tailleJeu][tailleJeu], tours, maxTours, opcR, opcC, role;
    bool gagne; //1 = P1, 2 = P2

    tours = 0;
    maxTours = tailleJeu*tailleJeu;
    role = 1;
    gagne = false;
    initialiserGrille(grille);

    while((tours < maxTours) && (!gagne)){
        afficherGrille(grille);
        cout<<"Tour de P"<<role<<"\n";
        cout<<"Donne le rangee: ";
        cin>>opcR;
        cout<<"Donne le colonne: ";
        cin>>opcC;

        if(((opcR >= 1 && opcR <= tailleJeu) && (opcC >= 1 && opcC <= tailleJeu)) && (grille[opcR-1][opcC-1] == 0)){
            grille[opcR-1][opcC-1] = role;
            gagne = verifierGagne(grille, opcR-1, opcC-1, role);
            role == 1 ? role = 2:role = 1;
            tours++;
        }
        else{
            cout<<"\nRangee ou colonne non valide\n";
        }
    }

    afficherGrille(grille);

    if(gagne){
        role == 1 ? role = 2:role = 1;
        cout<<"Nous avons un gagnant!!\n\tP"<<role<<"\n";
    }
    else{
        cout<<"Personne ne gagne, egalite!!\n";
    }
    return 1;
}