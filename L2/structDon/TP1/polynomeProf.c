#include "polynome.h"

/*Créer un polynôme nul*/
POLYNOME Nul()  
    {
     POLYNOME  p;
     int i;
     p = malloc(sizeof(struct un_polynome));
     if(p== NULL)
               {
               fprintf(stderr,"Allocation impossible \n");
               exit(EXIT_FAILURE);
                }
                else
	 {
                p->sonDegre = 0;
  	for(i=0;  i<=MaxSize-1;  i++)   p-> sonCoefficient[i] = 0;      
              }
    return p;
    }

/*
Construire un polynôme non nul */
POLYNOME Construire(POLYNOME p1, float a0)  
  { 
  POLYNOME  p;
  int i;
  p = malloc(sizeof(struct un_polynome));
  if(p== NULL)
            {
            fprintf(stderr,"Allocation impossible \n");
            exit(EXIT_FAILURE);
            }
 else
          {
           if( estNul(p1)) 
        	           {p->sonDegre = 0;
        	             p->sonCoefficient[0] = a0;
     	             for(i=1;  i<=MaxSize-1;  i++)   p->sonCoefficient[i] = 0;
                      }
           else
 	          {p->sonDegre = p1->sonDegre +1;
  	           p->sonCoefficient[0] = a0 ;
   	          for(i=1;  i<=p1->sonDegre+1;  i++)   p->sonCoefficient[i] =p1->sonCoefficient[i-1];                             
                          for(i=p1->sonDegre+2; i<=MaxSize-1; i++)  p->sonCoefficient[i] = 0;
                  } 
        }                                         
  return p;
}






/*Calculer le  degré d’un polynôme */
int Degre(POLYNOME p)  
        {return p->sonDegre;
        }

/*Calculer le coefficient de rang i d’un polynôme */
float Coefficient(POLYNOME p, int i)  
        {return p->sonCoefficient[i];
        }

/*Tester si le polynôme  est nul*/
BOOLEEN estNul(POLYNOME  p)  
         {int i;
         if (p->sonDegre != 0) return FAUX;
         for(i=0;  i<= p-> sonDegre;  i++)   if (p-> sonCoefficient[i] != 0) return FAUX;
         return VRAI;
        }
}
