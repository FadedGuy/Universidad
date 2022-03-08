#include <iostream>

int main(){
    int note = 21;

    while(!(note >= 0 && note <= 20)){
        std::cout <<"mark: ";
        std::cin >> note;
    }

    if(note <= 10){
        std::cout <<"failing\n";
    }
    else if(note <= 12){
        std::cout <<"satisfactory\n";
    }
    else if(note <= 16){
        std::cout <<"good\n";
    }
    else{
        std::cout <<"excellent\n";
    }

    return 0;
}