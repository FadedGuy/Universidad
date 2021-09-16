#include <iostream>
using namespace std;

int main(){
    int n = 7;
    int mat[100][100];
    
    int i,j,k,init,fin;
    init = 1;
    fin = n;
    k = (n+1)/2;
    while (k != 0)
    {
        for(i = init; i <= fin; i++){
            for(j = init; j <= fin; j++){
                if((i==init)||(j==init)||(i==fin)||(j==fin)){
                    mat[i][j] = k;
                    mat[n-i+1][n-j+1] = k;
                } 
            }
        }
        init++;
        fin--;
        k--;
    }
    
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            cout<<mat[i][j];
        }
        cout<<endl;
    }
}