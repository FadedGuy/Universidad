#include <iostream>
using namespace std;

int main(){
  int note;
  cout<<"Donner la note: ";
  cin>>note;

  if (note>=16)
    cout<<"TB";
  else
    if (note >= 14)
      cout<<"B";
    else
      if (note >= 12)
        cout<<"AB";
      else
        if (note >= 10)
          cout<<"P";
        else
          cout<<"Ajourne";

  cout<<endl;
}
