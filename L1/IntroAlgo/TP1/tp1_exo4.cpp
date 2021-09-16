#include <iostream>
using namespace std;

int main(){
  int a, p, n;

  do{
    cout<<"Donner un nombre strictement positif : ";
    cin >> a;
  }while(a <= 0);

  cout<<"Les termes de la suite sont : \n";

  p = a;
  n = 1;

  if(p != 1){
    while(p != 1){
      if(p % 2 == 0){
        p = p/2;
      }
      else{
        p = (3*p) + 1;
      }
      cout<<"U("<<n<<") = "<<p<<endl;
      n++;
    }
  }
  else{
    cout<<"U(1) = 1\n";
  }

}
