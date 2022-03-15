#include <cstdio>
#include <cmath>

class shape_t{
    public:
        float width;
        float height;
        virtual float get_area() const{
            return this->get_area();
        }

        virtual void print() const{
            printf("Shape (width: %.2f, height: %.2f, area: %.2f)\n", this->width, this->height, this->get_area());
        }

        bool operator==(const shape_t &s) const{
            return this->get_area() == s.get_area();
        }

        bool operator!=(const shape_t &s) const{
            return !(this->get_area() == s.get_area());
        }

        bool operator<(const shape_t &s) const{
            return this->get_area() < s.get_area();
        }

        bool operator<=(const shape_t &s) const{
            return this->get_area() <= s.get_area();
        }

        bool operator>(const shape_t &s) const{
            return this->get_area() > s.get_area();
        }

        bool operator>=(const shape_t &s) const{
            return this->get_area() >= s.get_area();
        }

        shape_t &operator++(){
            ++this->width;
            ++this->height;
            return *this;
        }

        shape_t &operator--(){
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

        using shape_t::operator++;
        using shape_t::operator--;

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

        using shape_t::operator++;
        using shape_t::operator--;

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

        using shape_t::operator++;
        using shape_t::operator--;

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
    shape_t shape;
    rectangle_t rectangle(10,20);
    triangle_t triangle(30, 30);
    circle_t circle(40);

    printf("++psr: %f\n", ++rectangle.width);
    printf("--pst: %f\n", --triangle.width);
    printf("psr++: %f\n", rectangle++.width);
    printf("pst--: %f\n", triangle--.width);

    rectangle.print();
    triangle.print();
    circle.print();

    printf("psr == pst: %d\n", rectangle==triangle);
    printf("psr != pst: %d\n", rectangle!=triangle);
    printf("psr < pst: %d\n", rectangle<triangle);
    printf("psr <= pst: %d\n", rectangle<=triangle);
    printf("psr > pst: %d\n", rectangle>triangle);
    printf("psr >= pst: %d\n", rectangle>=triangle);
    
    return 0;
}