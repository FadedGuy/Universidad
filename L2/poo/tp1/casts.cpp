#include <cstdio>

int main(){
    long int c = 421;
    printf("cast: %d\n", (int)c);
    printf("cast (fn notation): %d\n", int(c));
    printf("static cast: %d\n", static_cast<int>(c));

    return 0;
}