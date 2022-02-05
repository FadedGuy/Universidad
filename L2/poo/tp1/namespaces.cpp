#include <cstdio>

namespace poo{
    int var = 1;
    int fct(){
        return var;
    }

    namespace tp1{
        int var = 2;
        int fct(){
            return var;
        }
    }
}

int main(){
    printf("poo::var: %d\n", poo::var);
    printf("poo::fct(): %d\n", poo::fct());
    printf("poo::tp1::var: %d\n", poo::tp1::var);
    printf("poo::tp1::fct(): %d\n", poo::tp1::fct());


    return 0;
}