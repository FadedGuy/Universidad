/*
a,b,c = [0, MAX]

Non triangle (cote nul ou non valide) (2)
a || b || c = 0                       C1
a > b + c                             C2
b > a + c
c > a + b


Triangle valide (3)
a && b && c = (0, MAX]
a <= b + c  
b <= a + c
c <= a + b

3 cotes egal => equilateral           C3
2 cotes egal => isocele               C4
tous cotes dif => scalene             C5


Cas impossible (1)
param < 3                             C6


Test aux limites
Si un des 3 valeurs est:

lim inf 0 => -1, 0, 1 => invalide, invalide, valide
lim sup MAX => MAX-1, MAX, MAX+1 => valide, valide, invalide

invalide est non-triangle - valide est un triangle

...

DT de test limites
() impossible
(-1, 5, 4) invalide
(0, 0, 0) invalide
(0, 3, 1) invalide
(4, 3, MAX+1) invalide
(1, 5, 4) valide
(3, MAX-1, 6) valide
(MAX, 4, 7) valide

*/
#include <iostream>
#include <string>
#include <cfloat>

enum type_triangle{
    scalene, isocele, equilateral, nonTriangle, impossible
}; 

class Triangle{
    public:
        float a;
        float b;
        float c;
        type_triangle type;
        
        Triangle():
            type(impossible)
            {}

        Triangle(float a):
            type(impossible)
            {}

        Triangle(float a, float b):
            type(impossible)
            {}

        Triangle(float a, float b, float c){
            if(a < 0 || b < 0 || c < 0){
                this->type = impossible; 
            }
            else if(((a > (b + c)) || (b > (a + c)) || (c > (a + b))) || (a == 0 && b == 0 && c == 0)){ //non-triangle
                this->type = nonTriangle; 
            }
            else if(((a + b) > c) && ((a + c) > b) && ((b + c) > a)){ //Triangle valide
                this->a = a;
                this->b = b;
                this->c = c;

                if(a == b && b == c){
                    this->type = equilateral;
                }
                else if((a == b && c != a) || (b == c && a != b) || (a == c && b != a)){
                    this->type = isocele;
                }
                else{
                    this->type = scalene;
                }
            }
        }

        void print_type() const{
            std::string type_triangle_str[] = {"scalene", "isocele", "equilateral", "nonTriangle", "impossible"};
            std::cout << type_triangle_str[this->type] << "\n";
        }
};

int main(){
    //Test 
    Triangle t1(0, 3, 1);
    Triangle t2(-1, 5, 4);
    Triangle t3(4, 3, FLT_MAX+1);
    Triangle t4(4, 4, 4);
    Triangle t5(3, 6, 6);
    Triangle t6(3, 5, 4);
    Triangle t7;

    t1.print_type();
    t2.print_type();
    t3.print_type();
    t4.print_type();
    t5.print_type();
    t6.print_type();
    t7.print_type();

    return 0;
}