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

void rec_tri_ins(int vect[], int inf, int nb)
{
  if(inf < nb){
    rec_inser(vect, vect[inf], 0, inf-1);
    rec_tri_ins(vect, inf+1, nb);
  }
}

main(){
  int vect[N] = {55,94,70,54,16,41,74,50,39,97,92,25,88,72,17,100,20,86,87,56,67}, nb = 21;

  rec_tri_ins(vect, 1, nb);

  for(int i = 0; i < nb; i++){
    cout<<vect[i]<<",";
  }
  cout<<"\n";
}
