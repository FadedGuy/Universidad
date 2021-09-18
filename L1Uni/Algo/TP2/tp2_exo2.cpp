#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int nombreAlea(int maxi){
  srand(time(NULL));
  return (rand()%maxi);
}

int main(){
  int nbMyst, nb, cpt;

  nbMyst = nombreAlea(10);

  cout<<"Donner un nombre entre 0 et 9: ";
  cin>>nb;
  cpt = 1;

  while(nb != nbMyst){
    if(nb < nbMyst)
      cout<<"Nombre trop petit!!\n";
    else
      cout<<"Nombre trop grand!!\n";
    cout<<"Donner un nombre entre  0 et 9: ";
    cin >> nb;

    cpt++;
  }
  cout<<"\n\n\nGagne en "<<cpt<<" coups!!!\n";
}
