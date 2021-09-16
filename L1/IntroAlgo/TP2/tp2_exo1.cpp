/*
b) Le boucle repeter se execute 1 fois seulment
21
c)


#include <iostream>
using namespace std;

int main(){
    int j, u, v, k;

    j = 0;
    k = 0;

    do{
      if(j % 2 == 1){
        u = j;
        while(u > 0){
          k++;
          u = u/2;
        }
      }
      else{
        for(v = -1; v <= j-1;v++){
          k += 2;
        }
      }
      j++;
    }while(j < 5);

    cout<<k<<endl;
}

*/
#include <iostream>
using namespace std;

int main(){
    int j, u, v, k;

    j = 0;
    k = 0;

    for(j; j < 5; j++){
      if(j % 2 == 1){
        u = j;
        while(u > 0){
          k++;
          u /= 2;
        }
      }
      else{
        for(v = -1; v <= j-1; v++){
          k += 2;
        }
      }
    }

    cout<<k<<endl;
}
