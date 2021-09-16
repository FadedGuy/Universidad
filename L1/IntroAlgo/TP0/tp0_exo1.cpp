#include <iostream>
using namespace std;

int main(){
  int i, n, som;

  cout << "Donner la valeur de n: ";
  cin >> n;

  som = 0;

  for(i = 1; i <= n; i++)
    som = som + 100 + 2*i;

  cout << "A ses " << n << " ans, Marie aura donc " << som << " euros." << endl;
}
