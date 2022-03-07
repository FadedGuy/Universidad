#include <cstdio>

//Exo 8
template<typename T> T min(T param1, T param2){
    return param1 > param2 ? param2 : param1;
}

template<typename T> T max(T param1, T param2){
    return param1 > param2 ? param1 : param2;
}

//Exo 9
template<typename T, typename U> T min(T param1, U param2){
    return param1 > param2 ? param2 : param1;
}

template<typename T, typename U> T max(T param1, U param2){
    return param1 > param2 ? param1 : param2;
}

//Exo 11
template<typename T, typename U> T min(T param1, U param2, bool debug){
    if(debug){
        printf("debug: min function called\n");
    }
    return param1 > param2 ? param2 : param1;
}

template<typename T, typename U> T max(T param1, U param2, bool debug){
    if(debug){
        printf("debug: max function called\n");
    }
    return param1 > param2 ? param1 : param2;
}

int main(){
    printf("min(%d, %d, %d) = %d\n", 10, 42, false, min(10,42, false));    
    printf("min(%f, %f, %d) = %f\n", 9.99, 3.14, false, min(9.99, 3.14, false));    
    printf("min(%f, %d, %d) = %f\n", 9.99, 10, false, min(9.99, 10, false));    
    printf("max(%d, %d, %d) = %d\n", 10, 42, false, max(10,42, false));    
    printf("max(%f, %f, %d) = %f\n", 9.99, 3.14, false, max(9.99, 3.14, false));    
    printf("max(%f, %d, %d) = %f\n", 9.99, 10, false, max(9.99, 10, false));    
    printf("min(%d, %d, %d) = %d\n", 10, 42, true, min(10,42, true));    
    printf("min(%f, %f, %d) = %f\n", 9.99, 3.14, true, min(9.99, 3.14, true));    
    printf("min(%f, %d, %d) = %f\n", 9.99, 10, true, min(9.99, 10, true));    
    printf("max(%d, %d, %d) = %d\n", 10, 42, true, max(10,42, true));    
    printf("max(%f, %f, %d) = %f\n", 9.99, 3.14, true, max(9.99, 3.14, true));    
    printf("max(%f, %d, %d) = %f\n", 9.99, 10, true, max(9.99, 10, true));    
   

    return 0;
}