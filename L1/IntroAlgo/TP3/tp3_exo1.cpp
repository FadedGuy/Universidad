#include <iostream>
using namespace std;

int main(){
    int nbE, min, max, x, i, contInf;
    float moyenne, tab[50];

    moyenne = 0;

    cout << "Donner le nombre des elements: ";
    cin >> nbE;

    cout<< "Donner le valeur de x: ";
    cin >> x;

    //Remplir tableau
    for(i = 0; i < nbE; i++){ 
        cout<<"Donner un element: ";
        cin >> tab[i];
    }

    //Obtenir moyenne
    for(i = 0; i < nbE; i++)
        moyenne+=tab[i];
    moyenne /= nbE;
        
    //Obtenir min, max
    min = tab[0]; 
    max = tab[0];
    for(i = 1; i < nbE; i++){
        if(min > tab[i])
            min = tab[i];
        if(max < tab[i])
            max = tab[i];
    }

    //Calculer si plus de x elements inferieurs
    i = 0;
    contInf = 0;
    while (i < nbE && contInf <= x){
        if(tab[i] < moyenne)
            contInf++;
        i++;
    }
    
 
    cout << "Moyenne: " << moyenne << "\n";
    cout << "Min et max: " << min << ", " << max << "\n";

    if(contInf > x){
        cout << "Il y a plus de " << x << " elements inferieurs a la moyenne\n";
    }
    else{
        cout << "Il n'y a pas plus de " << x << " elements inferieurs a la moyenne (" << contInf << ")\n";
    }
}