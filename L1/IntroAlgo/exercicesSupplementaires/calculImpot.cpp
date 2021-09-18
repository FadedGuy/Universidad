#include <iostream>
using namespace std;

int main(){
  float R, N, QF;

  cout<<"Donner le revenu imposable: ";
  cin>>R;
  cout<<"Donner le nombre de parts: ";
  cin>>N;

  QF = R/N;

  cout<<"Le montant de l'impot est: ";
  if(QF <= 4121)
    cout<<"0\n";
  else{
    if(QF <= 8104){
      cout<<((R * 0.075) - (309.08 * N))<<"\n";
    }
    else{
      if(QF <= 14264){
        cout<<((R * 0.21) - (1403.12 * N))<<"\n";
      }
      else{
        if(QF <= 23096){
          cout<<((R * .31) - (2829.52 * N))<<"\n";
        }
        else{
          if(QF <= 37579){
            cout<<((R * 0.41) - (5139.12 * N))<<"\n";
          }
          else{
            if(QF <= 46343){
              cout<<((R * 0.4675) - (7299.91 * N))<<"\n";
            }
            else
              cout<<((R * 0.5275) - (10080.49 * N))<<"\n";
          }
        }
      }
    }
  }
}
