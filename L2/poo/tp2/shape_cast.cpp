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

        void print() const{
            printf("Rectangle (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};  

class triangle_t: shape_t{
    public:
        triangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        void print() const{
            printf("Triangle (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};

class circle_t: shape_t{
    public:
        circle_t(float diameter){
            this->width = diameter;
            this->height = diameter;
        }

        void print() const{
            printf("Circle (width: %.2f, height: %.2f)\n", this->get_width(), this->get_height());
        }
};

int main(){
    shape_t shape;
    shape.width = 2.5;
    shape.height = 3.6;

    rectangle_t rectangle(10,20);
    triangle_t triangle(30, 30);
    circle_t circle(40);
    
    shape_t* shape_p = dynamic_cast<shape_t*>(&shape);
    if(shape_p == NULL){
        printf("Error on dynamic cast\n");
        return 1;
    }
    shape_p->print();

    rectangle_t* rectangle_p = dynamic_cast<rectangle_t*>(&rectangle);
    if(rectangle_p == NULL){
        printf("Error on dynamic cast\n");
        return 1;
    }
    rectangle_p->print();

    triangle_t* triangle_p = dynamic_cast<triangle_t*>(&triangle);
    if(triangle_p == NULL){
        printf("Error on dynamic cast\n");
        return 1;
    }
    triangle_p->print();

    circle_t* circle_p = dynamic_cast<circle_t*>(&circle);
    if(circle_p == NULL){
        printf("Error on dynamic cast\n");
        return 1;
    }
    circle_p->print();


    return 0;
}