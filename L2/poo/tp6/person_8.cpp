#include <iostream>

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

        std::string to_str() const{
            std::string s;
            s += ("\"" + std::string(get_firstname()) + "\", \"" + std::string(get_lastname()) + "\"\n");
            return s; 
        }

        void print() const{
            std::cout << this->to_str();
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

        course_t operator[](int index) const{
            return this->courses[index];
        }

        std::string to_str() const{
            std::string s;
            s += ("(\"" + std::string(get_firstname()) + "\", \"" + std::string(get_lastname()) + "\", (");
            
            for(int i = 0; i < this->ncourses; i++){
                if(i != this->ncourses-1){
                    s += ("\"" + std::string(this->courses[i].get_name()) + "\",");
                } else{
                    s += ("\"" + std::string(this->courses[i].get_name()) + "\"");
                }
            }
            s += "))\n";
            
            return s;
        }

        void print() const{
            std::cout << this->to_str();
        }
};

std::ostream &operator<<(std::ostream &os, const person_t &p){
    os << p.to_str();
    return os;
}

std::ostream &operator<<(std::ostream &os, const student_t &s){
    os << s.to_str();
    return os;
}

int main(){
    student_t student1((char*)"Jean", (char*) "Bon");
    student_t student2((char*)"Paul", (char*) "Emploi");
    student_t student3((char*)"Anne", (char*) "Alyse");
    course_t c1((char*) "Techniques de programmation");
    course_t c2((char*) "Programmation orientee objet");
    course_t c3((char*) "Technologie orientee objet");

    student1.add_course(c1);
    student2.add_course(c1);
    student2.add_course(c2);
    student3.add_course(c1);
    student3.add_course(c2);
    student3.add_course(c3);

    std::cout << student1 << student2 << student3;

    std::cout << "s3[0].get_name(): " << student3[0].get_name() << "\n";
    std::cout << "s3[1].get_name(): " << student3[1].get_name() << "\n";
    std::cout << "s3[2].get_name(): " << student3[2].get_name() << "\n";

    return 0;
}