#include <iostream>
using namespace std;

int nRetourner(int& nBoites, int type){
  int n = 0;
  while(nBoites - type >= 0){
    n++;
    nBoites -= type;
  }
  return n;
}

int main(){
  int nBoites;

  cout<<"Nombre de boites commandees: ";
  cin>>nBoites;

  if(nBoites >= 10 && nBoites % 10 == 0){
    while(nBoites != 0){
      if(nBoites >= 300){
        cout<<nRetourner(nBoites, 300)<<" geant\n";
      }
      else{
        if(nBoites >= 100){
          cout<<nRetourner(nBoites, 100)<<" grand\n";
        }
        else{
          if(nBoites >= 50){
            cout<<nRetourner(nBoites, 50)<<" normal\n";
          }
          else{
            cout<<nRetourner(nBoites, 10)<<" petit\n";
          }
        }
      }
    }
  }
  else{
    if(nBoites < 10){
      cout<<"Pas de boites necesite\n";
    }
    else{
      cout<<"Nombre n'est pas multiple de 10\n";
    }
  }
}
