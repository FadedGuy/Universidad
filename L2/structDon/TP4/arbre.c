#include "arbre.h"

tree arbreVide(){
    return NULL;
}


forest foretVide(){
    return NULL;
}

BOOL estArbreVide(tree t){
    return t == NULL;
}

BOOL estForetVide(forest f){
    return f == NULL;
}
