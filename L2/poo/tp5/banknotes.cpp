#include <iostream>
#include <limits>

int main(){
    int banknotes[7] = {0,0,0,0,0,0,0};
    int opc = 0;

    do{
        std::cout << "banknote: ";
        std::cin >> opc;
        if(std::cin.bad() || std::cin.eof() || std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opc = 0;
        }

        switch (opc)
        {
        case 5:
            banknotes[0]++;
            break;

        case 10:
            banknotes[1]++;
            break;

        case 20:
            banknotes[2]++;
            break;

        case 50:
            banknotes[3]++;
            break;

        case 100:
            banknotes[4]++;
            break;

        case 200:
            banknotes[5]++;
            break;

        case 500:
            banknotes[6]++;
            break;

        default:
            std::cerr << "invalid banknote value\n";
            break;
        }

        std::cout << banknotes[0] << " banknote(s) of 5 euros\n";
        std::cout << banknotes[1] << " banknote(s) of 10 euros\n";
        std::cout << banknotes[2] << " banknote(s) of 20 euros\n";
        std::cout << banknotes[3] << " banknote(s) of 50 euros\n"; 
        std::cout << banknotes[4] << " banknote(s) of 100 euros\n";
        std::cout << banknotes[5] << " banknote(s) of 200 euros\n";
        std::cout << banknotes[6] << " banknote(s) of 500 euros\n";

    }while(opc != -1);

    std::cout << "exit\n";

    return 0;
}