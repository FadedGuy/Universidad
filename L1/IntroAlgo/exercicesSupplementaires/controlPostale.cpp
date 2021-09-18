#include <iostream>
using namespace std;

int main(){
  int a, b, c, max;

  cout<<"Donner les 3 dimensiones: ";
  cin>>a;
  max = a;
  cin>>b;
  if(b > max)
    max = b;
  cin>>c;
  if(c > max)
    max = c;

  if(((a+b+c) <= 100) && (max <= 60)){
    if((a*b >= 70) || (a*c >= 70) || (b*c >= 70))
      cout<<"Accepte\n";
    else
      cout<<"Refuse\n";
  }
  else
    cout<<"Refuse\n";
}
