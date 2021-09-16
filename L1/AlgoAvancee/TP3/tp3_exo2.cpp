#include <iostream>

using namespace std;

int partition(int t[], int premier, int dernier){
    int gauche, droit, elt, aux;

    int pivot = t[dernier];
    int i = (premier-1);
    for(int j = premier; j<=dernier; j++){
        if(t[j] < pivot){
            i++;
            aux = t[i];
            t[i] = t[j];
            t[j] = aux;
        }
    }
    aux = t[i+1];
    t[i+1] = t[dernier];
    t[dernier] = aux;
    return(i+1);
}

void quickSort(int t[], int premier, int dernier){
    int pivot;
    if(premier < dernier){
        pivot = partition(t, premier, dernier);
        quickSort(t, premier, pivot-1);
        quickSort(t, pivot+1, dernier);
    }
}

main()
{
    int tab[] = {5,3,1,6,7,9,10,15,2,67,61,9,0,-1};
    int nb = 13;
    quickSort(tab, 0, nb);
    for(int i = 0; i <= nb; i++){
        cout<<tab[i]<<", ";
    }
}