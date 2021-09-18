#include <iostream>
#define NB 100
using namespace std;

void lireElements(int& nb, int *tab){
  int i;
  cout<<"Combien de nombres: ";
  cin>> nb;
  for(i = 0; i < nb; i++){
    cout<<"Donner le nombre: ";
    cin>>tab[i];
  }
}

void triInsertion(int nb, int *tab){
  int i,j, aux;
  for(i = 1; i < nb; i++){
    aux = tab[i];
    j = i-1;
    while(j >= 0 && aux < tab[j]){
      tab[j+1] = tab[j];
      j = j-1;
    }
    tab[j+1] = aux;
  }
}

void ecrireElements(int nb, int tab[NB]){
  int i;
  for(i = 0; i < nb; i++){
    cout<<tab[i]<<", ";
  }
  cout<<"\n";
}

main(){
  int nb, tab[NB];

  lireElements(nb, tab);
  triInsertion(nb, tab);
  ecrireElements(nb, tab);
}
