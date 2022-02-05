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

namespace oop = poo;

int main(){
    printf("poo::var: %d\n", oop::var);
    printf("poo::fct(): %d\n", oop::fct());
    printf("poo::tp1::var: %d\n", oop::tp1::var);
    printf("poo::tp1::fct(): %d\n", oop::tp1::fct());


    return 0;
}