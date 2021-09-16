#include <iostream>

using namespace std;

void tableMultiplication(int n){
    cout<<"Table de "<<n<<"\n";
    for(int i = 1; i <= 10; i++){
        cout<<n<<" x "<<i<<" = "<<n*i<<"\n";
    }
    cout<<"\n";
}

int main(){
    for(int i = 1; i <= 10; i++){
        tableMultiplication(i);
    }
}