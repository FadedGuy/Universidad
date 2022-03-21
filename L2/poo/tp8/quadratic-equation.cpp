#include <cstdio>
#include <cstdlib>
#include <cmath>

void quadratic_equation(double a, double b, double c, int* nsol, double* sol1, double* sol2){
    double det = pow(b, 2) - (4 * a * c);
    if(det < 0){
        nsol = 0;
    }else if(det == 0){
        *nsol = 1;
        *sol1 = (-b / (2 * a));
    }else{
        *nsol = 2;
        *sol1 = ((-b) - sqrt(det) / (2 * a));
        *sol2 = ((-b) + sqrt(det) / (2 * a));
    }
}

int main(int argc, char** argv){
    double a, b, c, sol1, sol2;
    int nsol = 0;
    char* pEnd;

    if(argc != 4){
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    a = strtod(argv[1], &pEnd);
    b = strtod(argv[2], &pEnd);
    c = strtod(argv[3], NULL);

    if(a == 0){
        fprintf(stderr, "invalid number for the first argument\n");
        return 1;
    }
    if(b == 0){
        fprintf(stderr, "invalid number for the second argument\n");
        return 1;
    }
    if(c == 0){
        fprintf(stderr, "invalid number for the third argument\n");
        return 1;
    }

    quadratic_equation(a, b, c, &nsol, &sol1, &sol2);
    printf("%d solution", nsol);
    if(nsol == 0){
        printf("s\n");
    }else if(nsol == 1){
        printf(": %lf\n", sol1);
    }else{
        printf("s: %lf and %lf\n", sol1, sol2);
    }

    return 0;
}