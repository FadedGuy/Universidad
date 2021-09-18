#include <iostream>
using namespace std;

int main(){
  int nom1, nom2, nom3;

  cout << "Donner un nombre: ";
  cin >> nom1;
  cout << "Donner un nombre: ";
  cin >> nom2;
  cout << "Donner un nombre: ";
  cin >> nom3;

  if((nom1 <= nom2) && (nom2 <= nom3))
    cout<<"Ils sont par ordre croissant\n";
  else
    cout<<"Ils ne sont pas par ordre croissant\n";
}
