#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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

        std::string to_str() const{
            std::ostringstream oss;
            oss << "(\"" << this->name << "\", (";
            for(int i = 0; i < this->nauthors; i++){
                if(i == this->nauthors-1){
                    oss << "\"" << this->authors[i] << "\"";
                }else{
                    oss << "\"" << this->authors[i] << "\", ";
                }
            }
            oss << "), \"" << this->publisher << "\", " << this->year << ", " << this->isbn << ")";
            return oss.str();
        }

        void print() const{
            std::cout << this->to_str();
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

        std::string to_str() const{
            std::ostringstream oss;
            char days_str[7][15] = {"monday", "tueday", "wednesday", "thursday", "friday", "saturday", "sunday"};
            
            oss << "(\"" << this->name << "\", (";
            for(int i = 0; i < this->ndays; i++){
                if(i == this->ndays-1){
                    oss << "\"" << days_str[this->days[i]] << "\"";         
                }else{
                    oss << "\"" << days_str[this->days[i]] << "\", ";         
                }
            }
            oss << "), (";

            for(int i = 0; i < this->nbooks; i++){
                if(i == this->nbooks-1){
                    oss << books[i].to_str();
                }else{
                    oss << books[i].to_str(); 
                    oss << ", ";
                }
            }
            oss << "))\n";
            return oss.str();
        }

        void print() const{
            std::cout << this->to_str();
        }

        library_t &operator+=(const book_t &book){
            this->add_book(book);
            return *this;
        }

        library_t &operator+(const library_t &library) const{
            library_t* lib = new library_t;

            lib->set_name(this->name);
            lib->days = this->days;
            lib->ndays = this->ndays;
            lib->books = this->books;
            lib->nbooks = this->nbooks;

            for(int i = 0; i < library.nbooks; i++){
                *lib+=library.books[i];
            }
            return *lib;    
        }
};

std::ostream &operator<<(std::ostream &os, const library_t &library){
    os << library.to_str();
    return os;
}

int main(){
    book_t b1, b2, b3, b4;
    library_t sciences_lib, novel_lib, new_lib;
    
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
    sciences_lib+=b1;

    b2.set_name((char*) "C++: The Complete Reference");
    b2.add_author((char*) "Herbert Schildt");
    b2.set_publisher((char*) "McGraw-Hill");
    b2.set_year(2003);
    b2.set_isbn(9780070532465);
    sciences_lib+=b2;

    std::cout << sciences_lib;

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
    novel_lib+=b3;

    b4.set_name((char*) "Harry Potter and the Chamber of Secrets");
    b4.add_author((char*) "J. K. Rowling");
    b4.set_publisher((char*) "Bloomsbury");
    b4.set_year(1998);
    b4.set_isbn(9780747538493);
    novel_lib+=b4;

    std::cout << novel_lib;

    new_lib = sciences_lib + novel_lib;
    std::cout << new_lib;

    return 0;
}