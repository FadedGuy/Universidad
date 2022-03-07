#include <cstdio>
#include <cmath>

template<typename T> class shape_t{
    public:
        float width;
        float height;

        float get_width() const{
            return this->width;
        }

        float get_height() const{
            return this->height;
        }

};

template<typename T> class rectangle_t: shape_t<T>{
    public:
        rectangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        virtual float get_area() const{
            return this->width * this->height; 
        }
};  

template<typename T> class triangle_t: shape_t<T>{
    public:
        triangle_t(float width, float height){
            this->width = width;
            this->height = height;
        }

        virtual float get_area() const{
            return (this->width * this->height) / 2; 
        }
};

template<typename T> class circle_t: shape_t<T>{
    public:
        circle_t(float diameter){
            this->width = diameter;
            this->height = diameter;
        }

        virtual float get_area() const{
            return M_PI*((this->width/2) * (this->width/2)); 
        }
};

int main(){
    rectangle_t<int> rectangle(10,20);
    triangle_t<int> triangle(30, 30);
    circle_t<int> circle(40);
    rectangle_t<float> rectangle1(10,20);
    triangle_t<float> triangle1(30, 30);
    circle_t<float> circle1(40);

    printf("ps1->get_area() = %f\n", rectangle.get_area());
    printf("ps2->get_area() = %f\n", triangle.get_area());
    printf("ps3->get_area() = %f\n", circle.get_area());
    printf("ps4->get_area() = %f\n", rectangle1.get_area());
    printf("ps5->get_area() = %f\n", triangle1.get_area());
    printf("ps6->get_area() = %f\n", circle1.get_area());
    
    return 0;
}