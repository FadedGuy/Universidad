#include <iostream>
using namespace std;
#define tailleJeu 3
/*int cnt, i, j;

    for(i = 0; i < tailleJeu; i++){ 
        cnt = 0;
        for(j = 1; j < tailleJeu; j++){
            if(mat[i][j] == mat[i][j-1] && mat[i][j] != 0){
                cnt++;
            }
        }
        if(cnt == tailleJeu-1){
            return true;
        }
    }

    for(i = 0; i < tailleJeu; i++){ 
        cnt = 0;
        for(j = 1; j < tailleJeu; j++){
            if(mat[j][i] == mat[j-1][i] && mat[j][i] != 0){
                cnt++;
            }
        }
        if(cnt == tailleJeu-1){
            return true;
        }
    }

    i = 1;
    j = 1;
    cnt = 0;
    while((i < tailleJeu && j < tailleJeu) && (mat[i][j] == mat[i-1][j-1]) && (mat[i][i] != 0)){
        cnt++;
        if(cnt == tailleJeu-1){
            return true;
        }
        i++;
        j++;
    }

    i = tailleJeu-1;
    j = 0;
    cnt = 0;
    while((i > 0 && j < tailleJeu) && (mat[i][j] == mat[i-1][j+1]) && (mat[i][j] != 0)){
        cnt++;
        if(cnt == tailleJeu-1){
            return true;
        }
        i--;
        j++;
    }
    return false;*/
void initialiserGrille (int mat[][tailleJeu]){
    int i,j;
    for(i = 0; i < tailleJeu; i++){
        for(j = 0; j < tailleJeu; j++){
            mat[i][j] = 0;
        }
    }
}

void afficherGrille(int mat[][tailleJeu]){
    int i, j;
    for(i = 0; i < tailleJeu; i++){
        for(j = 0; j <  tailleJeu; j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    int grille[tailleJeu][tailleJeu], role, tours, toursMax, opcR, opcC;
    bool gagne;

    role = 1; //1 P1, 2 P2
    gagne = false;
    tours = 0;
    toursMax = tailleJeu * tailleJeu;
    initialiserGrille(grille);

    while((tours < toursMax) && (!gagne)){
        afficherGrille(grille);
        cout<<"Tour de P"<<role<<"\n";
        cout<<"Donne le rangee: ";
        cin>>opcR;
        cout<<"Donne le colonne: ";
        cin>>opcC;

        if(((opcR >= 1 && opcR <= tailleJeu) && (opcC >= 1 && opcC <= tailleJeu)) && (grille[opcR-1][opcC-1] == 0)){
            grille[opcR-1][opcC-1] = role;
            
            role == 1 ? role = 2 : role = 1;
            tours++;
        }
        else{
            cout<<"\nRangee ou colonne non valide !\n";
        }
    }

    if(gagne){
        role == 1 ? role = 2:role = 1;
        cout<<"Nous avons un gagnant!!\n\tP"<<role<<"\n";
    }
    else{
        cout<<"\nPersonne ne gagne, egalite!!\n";
    }

    return 1;
}