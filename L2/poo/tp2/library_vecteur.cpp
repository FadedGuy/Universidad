#include <cstdio>
#include <vector>

enum day_t{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

struct book_t{
    char* name;
    std::vector<char*> authors;
    int nauthors;
    char* publisher;
    int year;
    long isbn;

    book_t(){
        this->name = NULL;
        this->nauthors = 0;
        this->publisher = NULL;
        this->year = 0;
        this->isbn = 0;
    }

    ~book_t(){}

    void add_author(char* author){
        this->authors.push_back(author);
        this->nauthors++;
    }

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

struct library_t{
    char* name;
    std::vector<day_t> days;
    int ndays;
    std::vector<book_t> books;
    int nbooks;

    library_t(){
        this->name = NULL;
        this->ndays = 0;
        this->nbooks = 0;
    }

    ~library_t(){}

    void add_day(day_t day){
        this->days.push_back(day);
        this->ndays++;
    }

    void add_book(book_t book){
        this->books.push_back(book);
        this->nbooks++;
    }

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

int main(){
    book_t b1, b2, b3, b4;
    library_t sciences_lib, novel_lib;
    
    sciences_lib.name = (char*)"Sciences Library";
    sciences_lib.add_day(monday);
    sciences_lib.add_day(tuesday);
    sciences_lib.add_day(wednesday);
    sciences_lib.add_day(thursday);

    b1.name = (char*)"The C++ Programming Language";
    b1.add_author((char*)"Bjarne Stroustrup");
    b1.publisher = (char*)"Addison-Wesley";
    b1.year = 2013;
    b1.isbn = 9780321563842;
    sciences_lib.add_book(b1);

    b2.name = (char*)"C++: The Complete Reference";
    b2.add_author((char*)"Herbert Schildt");
    b2.publisher = (char*)"McGraw-Hill";
    b2.year = 2003;
    b2.isbn = 9780070532465;
    sciences_lib.add_book(b2);

    sciences_lib.print();


    novel_lib.name = (char*)"Novel Library";
    novel_lib.add_day(tuesday);
    novel_lib.add_day(wednesday);
    novel_lib.add_day(thursday);
    novel_lib.add_day(friday);

    b3.name = (char*)"Harry Potter and the Philosopher's Stone";
    b3.add_author((char*)"J. K. Rowling");
    b3.publisher = (char*)"Bloomsbury";
    b3.year = 1997;
    b3.isbn = 9780747532699;
    novel_lib.add_book(b3);

    b4.name = (char*)"Harry Potter and the Chamber of Secrets";
    b4.add_author((char*)"J. K. Rowling");
    b4.publisher = (char*)"Bloomsbury";
    b4.year = 1998;
    b4.isbn = 9780747538493;
    novel_lib.add_book(b4);

    novel_lib.print();

    return 0;
}