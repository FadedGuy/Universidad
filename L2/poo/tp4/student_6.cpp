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

class student_t: virtual public person_t{
    private:
        course_t* studied_courses;
        int nstudied_courses;
    public:
        student_t(char* firstname, char* lastname):
            person_t(firstname, lastname),
            studied_courses(NULL),
            nstudied_courses(0)
            {}

        ~student_t(){
            delete this->studied_courses;
        }

        course_t* get_studied_courses() const{
            return this->studied_courses;
        }

        int get_nstudied_courses() const{
            return this->nstudied_courses;
        }

        void add_studied_course(course_t course){
            course_t* tmp = new course_t[this->nstudied_courses+1];

            for(int i = 0; i < this->nstudied_courses; i++){
                tmp[i] = this->studied_courses[i];
            }
            tmp[this->nstudied_courses] = course;
            delete this->studied_courses;
            this->studied_courses = tmp;
            this->nstudied_courses++;
        }

        void print() const{
            printf("Student (\"%s\", \"%s\", (", get_firstname(), get_lastname());

            for(int i = 0; i < this->nstudied_courses; i++){
                if(i != this->nstudied_courses-1){
                    printf("\"%s\", ", this->studied_courses[i].get_name());
                } else{
                    printf("\"%s\"", this->studied_courses[i].get_name());
                }
            }
            printf("))\n");
        }
};

class teacher_t: virtual public person_t{
    private:
        course_t* taught_courses;
        int ntaught_courses;
    public:
        teacher_t(char* firstname, char* lastname):
            person_t(firstname, lastname),
            taught_courses(NULL),
            ntaught_courses(0)
            {}
        
        ~teacher_t(){
            delete taught_courses;
        }

        course_t* get_taught_courses() const{
            return this->taught_courses;
        }

        int get_ntaught_courses() const{
            return this->ntaught_courses;
        }

        void add_taught_course(course_t course){
            course_t* tmp = new course_t[this->ntaught_courses+1];

            for(int i = 0; i < this->ntaught_courses; i++){
                tmp[i] = this->taught_courses[i];
            }
            tmp[this->ntaught_courses] = course;
            delete this->taught_courses;
            this->taught_courses = tmp;
            this->ntaught_courses++;
        }

        void print() const{
            printf("Teacher (\"%s\", \"%s\", (", get_firstname(), get_lastname());
            for(int i = 0; i < this->ntaught_courses; i++){
                if(i != this->ntaught_courses-1){
                    printf("\"%s\", ", this->taught_courses[i].get_name());
                } else{
                    printf("\"%s\"", this->taught_courses[i].get_name());
                }
            }
            printf("))\n");
        }
};

class phd_student_t: public student_t, public teacher_t{
    private:

    public:
        phd_student_t(char* firstname, char* lastname):
            person_t(firstname, lastname),
            student_t(firstname, lastname),
            teacher_t(firstname, lastname)
            {}

        void print() const{
            printf("Ph. D (\"%s\", \"%s\", (", get_firstname(), get_lastname());
            for(int i = 0; i < get_ntaught_courses(); i++){
                if(i != get_ntaught_courses()-1){
                    printf("\"%s\", ", get_taught_courses()[i].get_name());
                } else{
                    printf("\"%s\"", get_taught_courses()[i].get_name());
                }
            }
            printf("), (");
            for(int i = 0; i < get_nstudied_courses(); i++){
                if(i != get_nstudied_courses()-1){
                    printf("\"%s\", ", get_studied_courses()[i].get_name());
                } else{
                    printf("\"%s\"", get_studied_courses()[i].get_name());
                }
            }
            printf("))\n");
        }
};

int main(){
    student_t person1((char*)"Jean", (char*) "Bon");
    student_t person2((char*)"Paul", (char*) "Emploi");
    student_t person3((char*)"Anne", (char*) "Alyse");
    teacher_t teacher1((char*)"Wilfrid", (char*) "Lefer");
    teacher_t teacher2((char*)"Samson", (char*) "Pierre");
    phd_student_t phd1((char*)"Nathan", (char*) "Pas");
    course_t c1((char*) "Techniques de programmation");
    course_t c2((char*) "Programmation orientee objet");
    course_t c3((char*) "Technologie orientee objet");
    course_t c4((char*) "How to write a thesis?");

    person1.add_studied_course(c1);
    person2.add_studied_course(c1);
    person2.add_studied_course(c2);
    person3.add_studied_course(c1);
    person3.add_studied_course(c2);
    person3.add_studied_course(c3);
    teacher1.add_taught_course(c2);
    teacher2.add_taught_course(c1);
    teacher2.add_taught_course(c2);
    phd1.add_taught_course(c4);
    phd1.add_studied_course(c1);
    phd1.add_studied_course(c2);

    person1.print();
    person2.print();
    person3.print();
    teacher1.print();
    teacher2.print();
    phd1.print();

    return 0;
}