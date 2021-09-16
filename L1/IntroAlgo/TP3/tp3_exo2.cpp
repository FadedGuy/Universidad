#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int nombreAlea(int maxi){
    srand(time(NULL));
    return (rand()%maxi);
}

int main(){
    int nbMyst, nb, cpt, tab[10], i;

    for(i = 0; i < 10; i++)
        tab[i] = 0;

    nbMyst = nombreAlea(10);
    cpt = 0;
    
    do{
        cout<<"Donner un nombre entre 0 et 9: ";
        cin>>nb;
        cpt++;

        if(tab[nb] > 0)
            cout<<"Cette nombre a deja ete propose\n";

        if(nb == nbMyst){
            cout<<"\nGagne en "<<cpt<<" coups !!\n";
        }
        else{
            if(nb < nbMyst){
               cout<<"Nombre trop petit!!\n"; 
            }
            else{
                cout<<"Nombre trop grand!!\n";
            }
        }
            
        tab[nb]++;
        
    }while(nb != nbMyst);
}