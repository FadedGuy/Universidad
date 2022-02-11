#include <cstdio>

enum day_t{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

typedef day_t d_t;

struct book_t{
    char name[100];
    char authors[10][100];
    int nauthors;
    char publisher[100];
    int year;
    long isbn;

    void print(){
        printf("(\"%s\", (", this->name);
        for(int i = 0; i < this->nauthors; i++){
            if(i == this->nauthors-1){
                printf("\"%s\"", this->authors[i]);                
            }else{
                printf("\"%s\", ", this->authors[i]);
            }
        }
        printf("), \"%s\", %d, %ld)", this->publisher, this->year, this->isbn);
    }
};

typedef book_t b_t;

struct library_t{
    char name[100];
    d_t days[7];
    int ndays;
    b_t books[100];
    int nbooks;

    void print(){
        char days_str[7][15] = {"monday", "tueday", "wednesday", "thursday", "friday", "saturday", "sunday"};
        
        printf("(\"%s\", (", this->name);
        for(int i = 0; i < this->ndays; i++){
            if(i == this->ndays-1){
                printf("\"%s\"", days_str[this->days[i]]);                
            }else{
                printf("\"%s\", ", days_str[this->days[i]]);
            }
        }
        printf("), (");

        for(int i = 0; i < this->nbooks; i++){
            if(i == this->nbooks-1){
                this->books[i].print();     
            }else{
                this->books[i].print();  
                printf(", ");
            }
        }
        printf("))\n");
    }
};

typedef library_t l_t;

int main(){
    l_t sciences_lib = {"Sciences Library", 
                                {monday, tuesday, wednesday, thursday}, 
                                4,
                                {
                                    {
                                        "The C++ Programming Language",
                                        {"Bjarne Stroustrup"},
                                        1,
                                        "Addison-Wesley",
                                        2013,
                                        9780321563842
                                    },
                                    {
                                        "C++: The Complete Reference",
                                        {"Herbert Schildt"},
                                        1,
                                        "McGraw-Hill",
                                        2003,
                                        9780070532465
                                    }
                                },
                                2
                                };;

    l_t novel_lib = {"Novel Library", 
                            {tuesday, wednesday, thursday, friday}, 
                            4,
                            {
                                {
                                    "Harry Potter and the Philosopher's Stone",
                                    {"J. K. Rowling"},
                                    1,
                                    "Bloomsbury",
                                    1997,
                                    9780747532699
                                },
                                {
                                    "Harry Potter and the Chamber of Secrets",
                                    {"J. K. Rowling"},
                                    1,
                                    "Bloomsbury",
                                    1998,
                                    9780747538493
                                }
                            },
                            2
                            };;

    sciences_lib.print();
    novel_lib.print();
    return 0;
}