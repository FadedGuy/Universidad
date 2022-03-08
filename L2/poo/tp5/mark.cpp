#include <iostream>
#include <limits>

int main(){
    int note = 21;

    while(!(note >= 0 && note <= 20)){
        std::cout <<"mark: ";
        std::cin >> note;
        if(std::cin.bad() || std::cin.eof() || std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            note = 21;
        }
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