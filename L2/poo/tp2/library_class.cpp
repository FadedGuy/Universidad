#include <cstdio>
#include <vector>

enum day_t{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

class book_t{
    private:
        char* name;
        std::vector<char*> authors;
        int nauthors;
        char* publisher;
        int year;
        long isbn;

    public:
        book_t(){
            this->name = NULL;
            this->nauthors = 0;
            this->publisher = NULL;
            this->year = 0;
            this->isbn = 0;
        }

        ~book_t(){}

        void set_name(char* name){
            this->name = name;
        }

        void set_publisher(char* publisher){
            this->publisher = publisher;
        }

        void set_year(int year){
            this->year = year;
        }

        void set_isbn(long isbn){
            this->isbn = isbn;
        }

        void add_author(char* author){
            this->authors.push_back(author);
            this->nauthors++;
        }

        void print() const{
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

        void print(char separator) const{
            this->print('(', ')', separator);
        }

        void print(char before, char after) const{
            this->print(before, after, ',');
        }
        
        void print(char before, char after, char separator) const{
            printf("%c\"%s\"%c %c", before, this->name, separator, before);
            for(int i = 0; i < this->nauthors; i++){
                if(i == this->nauthors-1){
                    printf("\"%s\"", this->authors[i]);                
                }else{
                    printf("\"%s\"%c ", this->authors[i], separator);
                }
            }
            printf("%c%c \"%s\"%c %d%c %ld%c", after, separator, this->publisher, separator, this->year, separator, this->isbn, after);
        }
};

class library_t{
    private:
        char* name;
        std::vector<day_t> days;
        int ndays;
        std::vector<book_t> books;
        int nbooks;

    public:
        library_t(){
            this->name = NULL;
            this->ndays = 0;
            this->nbooks = 0;
        }

        ~library_t(){}

        void set_name(char* name){
            this->name = name;
        }

        void add_day(day_t day){
            this->days.push_back(day);
            this->ndays++;
        }

        void add_book(book_t book){
            this->books.push_back(book);
            this->nbooks++;
        }

        void print() const{
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

        void print(char separator) const{
            this->print('(', ')', separator);
        }

        void print(char before, char after) const{
            this->print(before, after, ',');
        }

        void print(char before, char after, char separator) const{
            char days_str[7][15] = {"monday", "tueday", "wednesday", "thursday", "friday", "saturday", "sunday"};
            
            printf("%c\"%s\"%c %c", before, this->name, separator, before);
            for(int i = 0; i < this->ndays; i++){
                if(i == this->ndays-1){
                    printf("\"%s\"", days_str[this->days[i]]);                
                }else{
                    printf("\"%s\", ", days_str[this->days[i]]);
                }
            }
            printf("%c%c %c", after, separator, before);

            for(int i = 0; i < this->nbooks; i++){
                if(i == this->nbooks-1){
                    this->books[i].print(before, after, separator);     
                }else{
                    this->books[i].print(before, after, separator);  
                    printf("%c ", separator);
                }
            }
            printf("%c%c\n", after, after);
        }        
};

int main(){
    book_t b1, b2, b3, b4;
    library_t sciences_lib, novel_lib;
    
    sciences_lib.set_name((char*) "Sciences Library");
    sciences_lib.add_day(monday);
    sciences_lib.add_day(tuesday);
    sciences_lib.add_day(wednesday);
    sciences_lib.add_day(thursday);

    b1.set_name((char*) "The C++ Programming Language");
    b1.add_author((char*) "Bjarne Stroustrup");
    b1.set_publisher((char*) "Addison-Wesley");
    b1.set_year(2013);
    b1.set_isbn(9780321563842);
    sciences_lib.add_book(b1);

    b2.set_name((char*) "C++: The Complete Reference");
    b2.add_author((char*) "Herbert Schildt");
    b2.set_publisher((char*) "McGraw-Hill");
    b2.set_year(2003);
    b2.set_isbn(9780070532465);
    sciences_lib.add_book(b2);

    sciences_lib.print();
    sciences_lib.print(';');
    sciences_lib.print('[', ']');
    sciences_lib.print('[', ']', ';');

    novel_lib.set_name((char*) "Novel Library");
    novel_lib.add_day(tuesday);
    novel_lib.add_day(wednesday);
    novel_lib.add_day(thursday);
    novel_lib.add_day(friday);

    b3.set_name((char*) "Harry Potter and the Philosopher's Stone");
    b3.add_author((char*) "J. K. Rowling");
    b3.set_publisher((char*) "Bloomsbury");
    b3.set_year(1997);
    b3.set_isbn(9780747532699);
    novel_lib.add_book(b3);

    b4.set_name((char*) "Harry Potter and the Chamber of Secrets");
    b4.add_author((char*) "J. K. Rowling");
    b4.set_publisher((char*) "Bloomsbury");
    b4.set_year(1998);
    b4.set_isbn(9780747538493);
    novel_lib.add_book(b4);

    novel_lib.print();
    novel_lib.print(';');
    novel_lib.print('[', ']');
    novel_lib.print('[', ']', ';');

    return 0;
}