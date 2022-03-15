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

        virtual shape_t &operator++(){
            ++this->width;
            ++this->height;
            return *this;
        }

        virtual shape_t &operator--(){
            --this->width;
            --this->height;
            return *this;
        }
};

class rectangle_t: public shape_t{
    public:
        rectangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        virtual float get_area() const{
            return this->width * this->height; 
        }

        virtual void print() const{
            printf("Rectangle (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }

        rectangle_t operator++(int){
            rectangle_t r = *this;
            ++this->width;
            ++this->height;
            return r;
        }

        rectangle_t operator--(int){
            rectangle_t r = *this;
            --this->width;
            --this->height;
            return r;
        }
};  

class triangle_t: public shape_t{
    public:
        triangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        virtual float get_area() const{
            return (this->width * this->height) / 2; 
        }

        virtual void print() const{
            printf("Triangle (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }

        triangle_t operator++(int){
            triangle_t r = *this;
            ++this->width;
            ++this->height;
            return r;
        }

        triangle_t operator--(int){
            triangle_t r = *this;
            --this->width;
            --this->height;
            return r;
        }
};

class circle_t: public shape_t{
    public:
        circle_t(float diameter){
            this->width = diameter;
            this->height = diameter;
        }

        virtual float get_area() const{
            return M_PI*((this->width/2) * (this->width/2)); 
        }

        virtual void print() const{
            printf("Circle (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }

        circle_t operator++(int){
            circle_t r = *this;
            ++this->width;
            ++this->height;
            return r;
        }

        circle_t operator--(int){
            circle_t r = *this;
            --this->width;
            --this->height;
            return r;
        }
};

int main(){
    rectangle_t rectangle(10,20);
    triangle_t triangle(30, 30);
    circle_t circle(40);

    printf("++ %d", ++rectangle);

    rectangle.print();
    triangle.print();
    circle.print();
    
    return 0;
}