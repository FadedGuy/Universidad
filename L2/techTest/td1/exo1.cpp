#include <iostream>
#include <string>

/*
Triangle valide
a <= b + c
b <= a + c
c <= a + b

3 cotes egal => equilateral
2 cotes egal => isocele
scalene


Non triangle (negatif ou cote nul)
a > b + c
b > a + c
c > a + b

Cas impossible 
param < 3

*/

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
            this->type = impossible; 
            if((a > (b + c)) || (b > (a + c)) || (c > (a + b))){ //non-triangle
                this->type = nonTriangle; 
            }
            else if(((a + b) > c) && ((a + c) > b) && ((b + c) > a)){ //Triangle valide                this->a = a;
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
};

int main(){
    std::string type_triangle_str[] = {"scalene", "isocele", "equilateral", "nonTriangle", "impossible"};
    //Test 
    Triangle t0(1, 2, 8); //non-triangle
    Triangle t1(-4, 4, -1); //non-triangle
    Triangle t2(0, 5, 3); //cote nul non-triangle
    Triangle t3(6, 5, 3); //scalene
    Triangle t4(7, 4, 4); //isocele
    Triangle t5(4, 4, 4); //equilateral
    Triangle t6; //impossible

    std::cout << type_triangle_str[t0.type] << "\n";
    std::cout << type_triangle_str[t1.type] << "\n";
    std::cout << type_triangle_str[t2.type] << "\n";
    std::cout << type_triangle_str[t3.type] << "\n";
    std::cout << type_triangle_str[t4.type] << "\n";
    std::cout << type_triangle_str[t5.type] << "\n";
    std::cout << type_triangle_str[t6.type] << "\n";

    return 0;
}