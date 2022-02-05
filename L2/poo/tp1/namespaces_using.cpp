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
    using namespace poo;
    printf("poo::var: %d\n", var);
    printf("poo::fct(): %d\n", fct());
    printf("poo::tp1::var: %d\n", tp1::var);
    printf("poo::tp1::fct(): %d\n", tp1::fct());


    return 0;
}