#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 10
#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef struct s_polynome{
    int degre;
    float coefficient[MAX_SIZE];
}polynome;

typedef struct s_polynome* POLYNOME;

POLYNOME nul();
POLYNOME construire(POLYNOME p1, float a0);
BOOL estNul(POLYNOME p);

//Normalement il doit etre float mais la spec dit int
float degre(POLYNOME p);
float coefficient(POLYNOME p, int index);
