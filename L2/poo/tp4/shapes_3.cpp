#include <cstdio>
#include <cmath>

class musical_instrument_t{
    private: 
        float frequency;
    public:
        musical_instrument_t(float frequency):
            frequency(frequency)
            {}
        
        float get_frequency() const{
            return this->frequency;
        }
};

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

class rectangle_t: public shape_t{
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

class triangle_t: public shape_t, musical_instrument_t{
    public:
        triangle_t(triangle_t* triangle):
            triangle_t(triangle->width, triangle->height, 0)
            {};

        triangle_t(float width, float height, int frequency):
            musical_instrument_t(frequency)
            {
                this->width = width;
                this->height = height;
            };


        virtual float get_area() const{
            return (this->width * this->height) / 2; 
        }

        virtual void print() const{
            printf("Triangle (width: %.2f, height: %.2f, area: %.2f, frequency: %.2f Hz)\n", this->width, this->height, this->get_area(), this->get_frequency());
        }
};

class circle_t: public shape_t{
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
    triangle_t triangle(30, 30, 1047);
    circle_t circle(40);

    rectangle.print();
    triangle.print();
    circle.print();
    
    return 0;
}