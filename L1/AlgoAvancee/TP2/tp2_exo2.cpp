#include <iostream>
using namespace std;

int vec[16] = {5,1,7,17,0};

void Rec_inser(int val, int inf, int sup, int vec[16]){
    int aux;
    if(inf < sup && val > vec[inf]){
        vec[inf] = val;
        Rec_inser(vec[inf], inf+1, sup, vec);
    }
}

main(){
    Rec_inser(10,0,4,vec);
    for(int i = 0; i < 5; i++){
        cout<<vec[i]<<", ";
    }
}