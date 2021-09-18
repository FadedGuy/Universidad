#include <iostream>
#include <math.h>

#define N 10000

using namespace std;

main(){
  int n, antP, i, racN, j;
  int tab[N], nombres[N];
  // 0 = raye
  cout<<"Donne n: ";
  cin>>n;

  for(i = 1; i <= n; i++){
    tab[i] = 1;
    nombres[i] = i;
  }

  racN = sqrt(n);
  i=2;
  tab[1] = 0;

  while(i <= racN){
    if(tab[i] == 1){
      for(j = i*i; j < n; j+=i){
        tab[j] = 0;
      }
    }
    i++;
  }

  cout<<"0 = raye, 1 = nombre premier\n";
  for(i = 1; i <= n; i++){

    if(tab[i]==1){cout<<i<<"-";}
    //cout<<tab[i]<<",";
  }
  cout<<"\n";
}
