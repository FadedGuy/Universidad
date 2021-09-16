#include <iostream>
#include <iomanip>
#include <bitset>
//pour compiler sous linux:
// g++ -o repr representation.cpp
void print_repr(char * p, int size)
{
    std::cerr<<"---------------------------\n";
    std::cerr<<"codage (binaire)\n";
    for (int i=size-1; i>=0; i--)
           std::cerr<<std::bitset<8>(p[i]);
    std::cerr<<std::endl;
    std::cerr<<"codage (hexadécimal)\n";
    for (int i=size-1; i>=0; i--)
    {
       std::cerr<<std::hex<<std::setfill ('0')<<std::setw(2)<<(0xFF & p[i]);
    }
    std::cerr<<std::endl;
}

int main(int argc, char **argv)
{

    char c1=-100;
    char c2= -64;
    char c=c1;
    std::cerr<<"---------------------------\n";
    std::cerr<<"Entier sur 8 bits: "<<(int) c<<'\n';
    print_repr(&c,1);

    short int si1=32700;
    short int si2=70;
//    short int si=-32761;
    short int si=si1+si2;
    std::cerr<<"---------------------------\n";
    std::cerr<<"Entier sur 16 bits: "<<std::dec<<si<<'\n';
    print_repr((char *) &si,2);

    int i=305419896;
    std::cerr<<"---------------------------\n";
    std::cerr<<"Entier sur 32 bits: "<<std::dec<<i<<'\n';
    print_repr((char *) &i,4);

    float f=-0.75;
    std::cerr<<"---------------------------\n";
    std::cerr<<"Réel sur 32 bits: "<<f<<'\n';
    print_repr((char *) &f,4);

    double d=0.2734375;
//    double d=-0.75;
    std::cerr<<"---------------------------\n";
    std::cerr.precision(8);
    std::cerr<<"Réel sur 64 bits: "<<d<<'\n';
    print_repr((char *) &d,8);

    return 0;
}
