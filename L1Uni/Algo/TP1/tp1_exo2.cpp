#include <iostream>
using namespace std;

int main() {
   int i, n, som;

   som = 0;

   for (i = 1; i <= 10; i++){
      cout<<"Donner le nombre "<<i<<": ";
      cin>>n;
      som += n;
    }

   cout <<"La somme =  " << som << endl;
}
