#include <iostream>
using namespace std;

#define N 100

void miroir(int nb, int na, char vectI[]){
  if(na <= nb){
    vectI[nb] = vectI[na];
    miroir(nb-1, na+1, vectI);
  }
}

main()
{
  int nb = 5;
  char vectI[N*2] = {'b', 'e', 'i', 'b', 'i'};

  miroir(nb*2-1, 0, vectI);

  for(int i = 0; i < nb*2; i++){
    cout<<vectI[i];
  }
  cout<<endl;
}
