#include <cstdio>

class shape_t{
    public:
        float width;
        float height;

        float get_width() const{
            return this->width;
        }

        float get_height() const{
            return this->height;
        }

        virtual void print() const{
            printf("Shape (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};

class rectangle_t: shape_t{
    public:
        rectangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        virtual void print() const{
            printf("Rectangle (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};  

class triangle_t: shape_t{
    public:
        triangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        virtual void print() const{
            printf("Triangle (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};

class circle_t: shape_t{
    public:
        circle_t(float diameter){
            this->width = diameter;
            this->height = diameter;
        }

        virtual void print() const{
            printf("Circle (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};

int main(){
    shape_t shape;
    rectangle_t rectangle(10,20);
    triangle_t triangle(30, 30);
    circle_t circle(40);

    shape.width = 2.5;
    shape.height = 3.6;
    shape.print();

    rectangle.print();
    triangle.print();
    circle.print();


    shape_t* shape_p_new;
    rectangle_t* rectangle_p_new;
    triangle_t* triangle_p_new;
    circle_t* circle_p_new;

    shape_p_new = new shape_t;
    shape_p_new->width = 2.5;
    shape_p_new->height = 3.6;
    rectangle_p_new = new rectangle_t(10,20);
    triangle_p_new = new triangle_t(30,30);
    circle_p_new = new circle_t(40);

    shape_p_new->print();
    rectangle_p_new->print();
    triangle_p_new->print();
    circle_p_new->print();
    
    return 0;
}