#include <iostream>
using namespace std;

int main(){
  int n, i;
  float val = 3;

  do{
    cout<<"Donner le valeur de n pour la suite: ";
    cin>>n;
  }while(n <= 0);

  for(i = 0; i <= n; i++){
    cout<<val<<"\n";
    val = (val*.5) + 2;
  }
}
