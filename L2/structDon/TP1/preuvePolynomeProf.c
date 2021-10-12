#include <stdio.h>
#include <stdlib.h>
#include "polynome.c"

int main(int argc, char *argv[])
{
POLYNOME   p, p1;
 int i, succes;
float a0;
/* Allocation mémoire et vérification  */
p  = malloc( sizeof( struct un_polynome) );
p1 = malloc( sizeof( struct un_polynome) );
if( p == NULL || p1 == NULL   )
               {
               printf("Allocation impossible \n");
               exit(EXIT_FAILURE);
                };

/*  Vérifier l’implémentation du constructeur Nul() */
p = Nul() ;
/* Initialiser l'indice succes */
succes= 1;
/* Vérification avec l’accesseur estNul */
/* Vérifier la propriété :   estNul(p ) = True */
if ( !estNul(p) )    succes = 0;

/* Vérification avec l’accesseur Degre */
/* Vérifier la propriété :  Degre(p ) = 0   */
if (Degre(p ) != 0)   succes = 0

/* Vérification avec l’accesseur Coefficient */
/*Vérifier la propriété :   i • Coefficient(p ,i) = 0    */
for (i=0; i< MaxSize; i++) 
                             if (Coefficient(p ,i) != 0   ) succes =0 

/* Bilan de la vérification */
if (succes !=1 )
               {printf ("\n Implémentation incorrecte du constructeur Nul() ");   
               printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
               exit(EXIT_FAILURE);
                };

/*Vérifier l’implémentation du constructeur "Construire(p1,a0)" */

/* ne pas oublier de saisir le polynome p1  */
printf("\n saisir un polynome: p1 est le premier argument");

/* ne pas oublier de saisir le réel a0 */
printf("\n saisir un reel: a0 est le second argument");
  
/* Apres la saisie de p1 et a0,  appliquer "Construire" pour créer un polynome p  */
 p = Construire( p1,a0);
/* réinitialiser la variable succes  */ 
succes=0 ;

/* Vérification avec l’accesseur estNul */
/* vérification de la propriété :   estNul(p) = True   estNul(p1) = True   a0 = 0    */
if ( estNul(p))   if ( estNul(p1)   &&  a0 == 0  )  succes=1;
if ( estNul(p1) && a0 == 0)   if (estNul(p) )   success = succes+1;

/*Bilan de la vérification   */
if (succes != 2 )
             { printf( “\n Implémentation de Construire(estNul) incorrecte”) ;
             printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
             exit(EXIT_FAILURE);
              };

/* Vérification avec l’accesseur Degre */
/* réinitialiser la variable « succès »  */
succes =0;
/* vérification de la propriété :    Degre(p) = 0    estNul(p1) = True    */
if ( Degre(p) ==0 )    if ( estNul(p1)  )   succes =1;
if ( estNul(p1)   if ( Degre(p) ==0 )       succes =  succes + 1;

/* vérification de la propriété :    Degre(p) = Degre(p1)+1    estNul(p1) = False  */
if ( Degre(p) = Degre(p1) +1  )  if ( !estNul(p1) )         succes =  succes + 1;
if ( !estNul(p1))   if( Degre(p) == Degre(p1) +1 )        succes =  succes + 1;

/* Bilan de la vérification */
if (succes !=4) 
        { printf( “\n Implémentation de Construire (Degré) incorrecte”) ;
        printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
         exit(EXIT_FAILURE);
         };

/* Vérification avec l’accesseur Coefficient */
/* réinitialiser la variable succès  */
succes=1;
/* vérification de la propriété :  Coefficient(p,0)  = a0      */
if (coefficient(p, 0)  != a0) )  success = 0 ;

/* vérification de la propriété :   estNul(p1) = True      ( i> 0  Coefficient(p, i) =0    )  */
if ( estNul(p1))  for(i=1; i< MaxSize;  i++)   if (  Coefficient(p,i)  !=0  ) success = 0 ;

/* vérification de la propriété :  
/* estNul(p1) = False  (i1  i Degre(p1)+1  Coefficient(p, i) =Coefficient(p1,i-1))  */
if (!estNul(p1 ) )   for(i=1; i<= Degre(p1)+1 ; i++)  
                                              if ( Coefficient(p, i) != Coefficient(p1,i-1)  ) success = 0 ;

/* vérification de la propriété :  estNul(p1) = False     i> Degre(p1)+1  Coefficient(Construire( p1,a0), i) = 0  */  
 if (!estNul(p1 ) )   for(i= Degre(p1)+2;  i<= MaxSize ; i++) 
                                              if ( Coefficient(p, i) != 0  ) success = 0 ;

/* Bilan de la verification */
if (succes ==0)
        { printf( “\n Implémentation de Construire (Coefficient) incorrecte”) ;
        printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
        exit(EXIT_FAILURE);
               };
printf("L'implementation du type abstrait est vérifiée"); 
printf("Fin normale de la vérification de l'implémentation du type abstrait");
return EXIT_SUCCESS;
}
