// for(int i = 1; i < nb; i++){
//   j = i;
//   aux = vect[i];
//   while(j > 1 && aux < vect[j]){
//     vect[j] = vect[j+1];
//     j--;
//   }
//   vect[j] = aux;
// }

#include <iostream>
using namespace std;

#define N 100

void rec_inser(int vect[], int val, int inf, int sup)
{
  if(sup >= inf && val < vect[sup])
  {
    vect[sup+1] = vect[sup];
    rec_inser(vect, val, inf, sup-1);
  }else{
    vect[sup+1] = val;
  }
}

main(){
  int vect[N] = {2,4,8}, nb = 3;

  rec_inser(vect, 5, 0,2);

  for(int i = 0; i <= nb; i++){
    cout<<vect[i]<<", ";
  }
  cout<<"\n";
}
