#include <cstdio>

class person_t{
    private: 
        char* firstname;
        char* lastname;

    public:
        person_t(char* firstname, char* lastname):
            firstname(firstname),
            lastname(lastname)
            {}
        
        char* get_firstname() const{
            return this->firstname;
        }

        char* get_lastname() const{
            return this->lastname;
        }

        void print() const{
            printf("\"%s\", \"%s\"\n", get_firstname(), get_lastname());
        }
};

class course_t{
    private:
        char* name;

    public:
        course_t():
            name(NULL)
            {}

        course_t(char* name):
            name(name)
            {}
        
        char* get_name() const{
            return this->name;
        }
};

class student_t: public person_t{
    private:
        course_t* courses;
        int ncourses;
    public:
        student_t(char* firstname, char* lastname):
            person_t(firstname, lastname),
            courses(NULL),
            ncourses(0)
            {}

        ~student_t(){
            delete this->courses;
        }

        void add_course(course_t course){
            course_t* tmp = new course_t[this->ncourses+1];

            for(int i = 0; i < this->ncourses; i++){
                tmp[i] = this->courses[i];
            }
            tmp[this->ncourses] = course;
            delete this->courses;
            this->courses = tmp;
            this->ncourses++;
        }

        void print() const{
            printf("(\"%s\", \"%s\", (", get_firstname(), get_lastname());

            for(int i = 0; i < this->ncourses; i++){
                if(i != this->ncourses-1){
                    printf("\"%s\", ", this->courses[i].get_name());
                } else{
                    printf("\"%s\"", this->courses[i].get_name());
                }
            }
            printf("))\n");
        }
};

int main(){
    student_t person1((char*)"Jean", (char*) "Bon");
    student_t person2((char*)"Paul", (char*) "Emploi");
    student_t person3((char*)"Anne", (char*) "Alyse");
    course_t c1((char*) "Techniques de programmation");
    course_t c2((char*) "Programmation orientee objet");
    course_t c3((char*) "Technologie orientee objet");

    person1.add_course(c1);
    person2.add_course(c1);
    person2.add_course(c2);
    person3.add_course(c1);
    person3.add_course(c2);
    person3.add_course(c3);

    person1.print();
    person2.print();
    person3.print();

    person_t* p1 = &person1;
    p1->print();
    person_t* p2 = &person2;
    p2->print();
    person_t* p3 = &person3;
    p3->print();

    return 0;
}