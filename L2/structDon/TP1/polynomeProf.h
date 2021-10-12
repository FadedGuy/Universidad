#include    <stdio.h>
#include  <stdlib.h>
#include  <ctype.h>
#define	MaxSize   10
#define 	FAUX   	  0
#define 	VRAI   	  1
typedef     int 	BOOLEEN;
/*
Proposer un type CONCRET pour implémenter le type ABSTRAIT des polynômes
*/   	
typedef   struct un_polynome 
          {
           int    sonDegre ;
	float  sonCoefficient[MaxSize] ;
          }  polynome;

/*  définition du type des polynômes: un type pointeur vers un objet de type polynôme */
typedef  struct un_polynome *  POLYNOME;   

/*
 créer un polynôme nul*/ 
POLYNOME Nul() ; 

/*
 construire le polynôme "p1*x + a0" */
POLYNOME Construire(POLYNOME p1, float a0);  

/*
calculer le degré d’un polynôme */
int Degre(POLYNOME p);

/*
 calculer le coefficient de rang i d’un polynôme */ 
float Coefficient(POLYNOME p, int i) ;

/*
 tester si un polynôme  est un polynôme nul*/
BOOLEEN estNul(POLYNOME  p); 

