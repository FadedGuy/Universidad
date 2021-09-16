#include <iostream>
#include <ctime>

using namespace std;

long fib(long n)
{
    if(n<=1){
        return(n);
    }
    else{
        return(fib(n-1) + fib(n-2));
    }
}

main()
{
    int n = 43;
    long cur = 1, ant = 0, aux = 0;
    time_t avant, apres;

    
    //cout<<"Donne n:"; cin>>n;
    avant = time(NULL);
    cout<<fib(n+1)<<"\n";
    apres = time(NULL);
    cout<<apres-avant<<"\n";

    avant = time(NULL);
    while(n--){
        ant = cur + aux;
        aux = cur;
        cur = ant;
    }
    apres = time(NULL);
    cout<<apres-avant<<"\n";

    cout<<cur<<"\n";    
}