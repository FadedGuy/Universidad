#include <iostream>
using namespace std;

void lireElements(int tab[], int& taille){
    int newElement;
    cout<<"Donne le nouvelle element: ";
    cin >> newElement;

    tab[taille] = newElement;
    taille++;
    cout<<"Nouvelle element ajoute\n";
}

void afficherElements(int tab[], int taille){
    if(taille == 0){
        cout<<"Pas de elements sur le tableau\n";
    }
    else{
        int i;
        for(i = 0; i < taille; i++){
            cout<<tab[i]<<"\n";
        }
        cout<<"\n";
    }
}

void inverserTab(int tab[], int taille){
    int i, j, aux;
    i = 0;
    j = taille - 1;
    if(taille > 0){
        while (i < j){
            aux = tab[i];
            tab[i] = tab[j];
            tab[j] = aux;
            i++;
            j--;
        }
        cout<<"Les elements sont inverse\n";
    }
    else{
        cout<<"Pas de elements dans le tableau\n";
    }
    
}

void supprimerSeuil(int tab[], int& taille){
    int seuil;

    if(taille > 0){
        cout<<"Donne le seuil: ";
        cin>>seuil;
        int i;
        i = -1;
        while(i < taille){
            i++;
            if(tab[i] > seuil){
                tab[i] = tab[taille-1];
                taille--;
                i=-1;
            }
            
        }
        cout<<"Fini\n";
    }
    else{
        cout<<"Pas de elements sur le tableau\n";
    }
}

int main(){
    int tab[100];
    int taille, opM;

    taille = 0;
    do{
        cout<<"\t-MENU-\n";
        cout<<"1. Lire les elements de tableau\n";
        cout<<"2. Afficher les elements de tableau\n";
        cout<<"3. Inverser l'ordre des elements de tableau\n";
        cout<<"4. Supprimer les elements superieurs a un seuil de tableau\n";
        cout<<"5. Sortir\n";
        cout<<"Seleccione votre option: ";
        cin>>opM;

        switch(opM){
        case 1:
            lireElements(tab, taille);
            break;
        case 2:
            afficherElements(tab, taille);
            break;
        case 3:
            inverserTab(tab, taille);
            break;
        case 4:
            supprimerSeuil(tab, taille);
            break;
        case 5:
            cout<<"Au revoir!\n";
            break;
        default:
            cout<<"Option non valide\n";
            break;
        }
    }while(opM != 5);
}