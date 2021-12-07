#include "matrice.h"

void vecteurVide(double *x, int n) {
    for(int i = 0; i < n; i++) {
        x[i] = 0;
    }
}

void afficheV(double *x, int n) {
    for(int i = 0; i < n; i++) {
        printf("%+.2f\n", x[i]);
    }
}

void afficheM(double *A, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%+.2f    ", A[i*n+j]);
        }
        printf("\n");
    }
}

void prodMV(double *A, double *x, double *y, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            y[i] += A[i*n+j] * x[j];
        }
    }
}

void prodMM(double *A, double *B, double *C, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                C[i*n+j] += A[i*n+k] * B[k*n+j];
            }
        }
    }
}

void descente(double *L, double *b, double *y, int n) {
    double sum = 0;

    for(int j = 0; j < n; j++) {
        sum = 0;
        for(int i = 0; i < j; i++) {
            sum += L[j*n+i] * y[i];
        }
        y[j] = b[j] - sum;
    }
}

void remontee(double *U, double *y, double *x, int n) {
    double sum;

    for(int j = n-1; j >= 0; j--) {
        sum = 0;
        for(int i = j+1; i < n; i++) {
            sum += U[j*n+i] * x[i];
        }
        x[j] = (y[j]- sum) / U[j*n+j];
    }
}

void decompositionLU(double *A, double *L, double *U, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            U[i*n+j] = A[i*n+j];
        }   
    }

    for(int r = 0; r < n; r++) {
        L[r*n+r] = 1;
        for(int i = r+1; i < n; i++) {
            L[i*n+r] = U[i*n+r] / U[r*n+r];
            L[r*n+i] = 0;
            U[i*n+r] = 0;
            for(int j = r+1; j < n; j++) {
                U[i*n+j] -= L[i*n+r]*U[r*n+j];
            }
        }
    }
}

void resSystemeLineaire(double *A, double *b, double *x, int n) {
    double L[n*n];
    double U[n*n];
    double y[n];

    vecteurVide(L, n*n);
    vecteurVide(U, n*n);

    decompositionLU(A, L, U, n);

    descente(L, b, y, n);
    remontee(U, y, x, n);
}