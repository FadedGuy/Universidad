#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char** argv){
    double a, b;
    char* pEnd;

    if(argc != 3){
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    a = strtod(argv[1], &pEnd);
    b = strtod(argv[2], NULL);

    if(a == 0){
        fprintf(stderr, "invalid number for the first argument\n");
        return 1;
    }
    if(b == 0){
        fprintf(stderr, "invalid number for the second argument\n");
        return 1;
    }

    printf("hypothenuse = %lf\n", sqrt(pow(a, 2) + pow(b, 2)));

    return 0;
}