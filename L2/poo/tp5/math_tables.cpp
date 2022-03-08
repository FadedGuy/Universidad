#include <iostream>
#include <limits>
#include <cstdio>

int get_spaces(int num){
    int sum = 0;
    while(num != 0){
        num /= 10;
        sum++;
    }
    return sum;
}

int main(){
    char op;
    int n_lines, n_col, spaces = 1, cnt = 0;

    do{
        std::cout << "operator: ";
        std::cin >> op;
        if(std::cin.bad() || std::cin.eof() || std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            op = '+';
        }
    }while(op != '+' && op != '-' && op != '*' && op != '/' && op != '%');

    do{
        std::cout << "number of lines: ";
        std::cin >> n_lines;
        if(std::cin.bad() || std::cin.eof() || std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            n_lines = 0;
        }
    }while(n_lines <= 0);

    do{
        std::cout << "number of columns: ";
        std::cin >> n_col;
        if(std::cin.bad() || std::cin.eof() || std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            n_col = 0;
        }
    }while(n_col <= 0);

    switch (op){
    case '+':
        spaces += get_spaces((n_lines-1) + (n_col-1));
        break;
    case '-':
        spaces += get_spaces(n_col-1)+1;
        break;
    case '*':
        spaces += get_spaces((n_lines-1) * (n_col-1));
        break;
    case '/':
        spaces += get_spaces((n_lines-1));
        break;
    case '%':
        spaces += get_spaces(n_col-1);
        break;
    }

    std::cout << op;
    cnt++;
    for(int  i = 0; i < spaces-2; i++){
        std::cout << " ";
        cnt++;
    }
    std::cout << "|";
    cnt++;
    for(int i = 0; i < n_col; i++){
        std::cout << i;
        cnt++;
        for(int  j = 0; j < spaces-1; j++){
            std::cout << " ";
            cnt++;
        }
    }
    std::cout << "\n";
    
    for(int i = 0; i < cnt; i++){
        std::cout << "-";
    }
    std::cout << "\n";

    for(int i = 0; i < n_lines; i++){
        for(int j = -2; j < n_col; j++){
            if(j == -2){
                std::cout << i;
                for(int  k = 0; k < spaces-2; k++){
                    std::cout << " ";
                }
            } 
            else if(j == -1){
                std::cout << "|";
            }
            else{
                if(j == 0 && op == '/'){
                    std::cout << "E";
                    for(int  k = 0; k < spaces-2; k++){
                        std::cout << " ";
                    }
                }
                else{
                    switch (op){
                        case '+':
                            std::cout << j+i;
                            cnt = j+i;
                            break;
                        case '-':
                            std::cout << j-i;
                            cnt = j-i;                            
                            break;
                        case '*':
                            std::cout << j*i;
                            cnt = j*i;
                            break;
                        case '/':
                            std::cout << j/i;
                            cnt = j/i;
                            break;
                        case '%':
                            std::cout << j%i;
                            cnt = j%i;
                            break;
                    }
                    for(int  k = 0; k < (cnt < 0 ? spaces-2 : spaces-1); k++){
                        std::cout << " ";
                    }
                }
            }
        }
        std::cout << "\n";
    }

    return 0;
}