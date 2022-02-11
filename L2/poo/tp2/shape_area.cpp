#include <cstdio>
#include <cmath>

class shape_t{
    protected: 
        float width;
        float height;
    public:
        virtual float get_area() const{
            return this->get_area();
        }

        virtual void print() const{
            printf("Shape (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }

};

class rectangle_t: shape_t{
    public:
        rectangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        rectangle_t(rectangle_t* rectangle){
            rectangle_t(rectangle->width, rectangle->height);
        }

        virtual float get_area() const{
            return this->width * this->height; 
        }

        virtual void print() const{
            printf("Rectangle (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }
};  

class triangle_t: shape_t{
    public:
        triangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        triangle_t(triangle_t* triangle){
            triangle_t(triangle->width, triangle->height);
        }

        virtual float get_area() const{
            return (this->width * this->height) / 2; 
        }

        virtual void print() const{
            printf("Triangle (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }
};

class circle_t: shape_t{
    public:
        circle_t(float diameter){
            this->width = diameter;
            this->height = diameter;
        }

        circle_t(circle_t* circle){
            circle_t(circle->width);
        }

        virtual float get_area() const{
            return M_PI*((this->width/2) * (this->width/2)); 
        }

        virtual void print() const{
            printf("Circle (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }
};

int main(){
    rectangle_t rectangle(10,20);
    triangle_t triangle(30, 30);
    circle_t circle(40);

    rectangle_t r_c(rectangle);
    triangle_t t_c(triangle);
    circle_t c_c(circle);

    rectangle.print();
    triangle.print();
    circle.print();
    r_c.print();
    t_c.print();
    c_c.print();
    
    return 0;
}