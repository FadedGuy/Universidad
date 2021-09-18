#include <iostream>
using namespace std;

int main(){
  int n, ant, i;
  bool croissant;

  croissant = true;

  cout<<"Donner un nombre: ";
  cin>>n;
  ant = n;
  for(i = 2; i <= 3; i++){
    cout<<"Donner un nombre: ";
    cin>>n;
    if (n >= ant)
      ant = n;
    else
      croissant = false;
  }

  if (croissant)
    cout<<"Ils sont par ordre croissant"<<endl;
  else
    cout<<"Ils ne sont pas par ordre croissant"<<endl;
}
