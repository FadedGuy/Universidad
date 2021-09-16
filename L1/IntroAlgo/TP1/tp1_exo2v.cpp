#include <iostream>
using namespace std;

int main(){
  int n1, n2, n3, i;

  cout<<"Donner un nombre: ";
  cin>>n1;
  cout<<"Donner un nombre: ";
  cin>>n2;
  cout<<"Donner un nombre: ";
  cin>>n3;
  
  if(n1 <= n2 && n2 <= n3)
    cout<<"Ils sont par ordre croissant\n";
  else
    cout<<"Ils ne sont pas par ordre croissant\n";
  
}
