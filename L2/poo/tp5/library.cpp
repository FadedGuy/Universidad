#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum day_t{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

class book_t{
    private:
        std::string name;
        std::vector<std::string> authors;
        int nauthors;
        std::string publisher;
        int year;
        long isbn;

    public:
        book_t(){
            this->nauthors = 0;
            this->year = 0;
            this->isbn = 0;
        }

        ~book_t(){}

        long get_isbn(){
            return this->isbn;
        }

        void set_name(std::string name){
            this->name = name;
        }

        void set_publisher(std::string publisher){
            this->publisher = publisher;
        }

        void set_year(int year){
            this->year = year;
        }

        void set_isbn(long isbn){
            this->isbn = isbn;
        }

        void add_author(std::string author){
            this->authors.push_back(author);
            this->nauthors++;
        }

        void print() const{
            std::cout << "(\"" << this->name << "\", (";
            for(int i = 0; i < this->nauthors; i++){
                if(i == this->nauthors-1){
                    std::cout << "\"" << this->authors[i] << "\"";
                }else{
                    std::cout << "\"" << this->authors[i] << "\", ";
                }
            }
            std::cout << "), \"" << this->publisher << "\", " << this->year << ", " << this->isbn << ")";
        }
};

class library_t{
    private:
        std::string name;
        std::vector<day_t> days;
        int ndays;
        std::vector<book_t> books;
        int nbooks;

    public:
        library_t(){
            this->ndays = 0;
            this->nbooks = 0;
        }

        ~library_t(){}

        std::vector<long> get_isbns(){
            std::vector<long> isbns;
            for(size_t i = 0; i < this->books.size(); i++){
                isbns.push_back(this->books[i].get_isbn());
            }
            return isbns;
        } 

        void set_name(std::string name){
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
            
            std::cout << "(\"" << this->name << "\", (";
            for(int i = 0; i < this->ndays; i++){
                if(i == this->ndays-1){
                    std::cout << "\"" << days_str[this->days[i]] << "\"";         
                }else{
                    std::cout << "\"" << days_str[this->days[i]] << "\", ";         
                }
            }
            std::cout << "), (";

            for(int i = 0; i < this->nbooks; i++){
                if(i == this->nbooks-1){
                    this->books[i].print();     
                }else{
                    this->books[i].print();  
                    std::cout << ", ";
                }
            }
            std::cout << "))\n";
        }

};

int main(){
    book_t b1, b2, b3, b4;
    library_t sciences_lib, novel_lib;
    std::vector<long> isbn;
    std::vector<long>::iterator i;
    
    sciences_lib.set_name("Sciences Library");
    sciences_lib.add_day(monday);
    sciences_lib.add_day(tuesday);
    sciences_lib.add_day(wednesday);
    sciences_lib.add_day(thursday);

    b1.set_name("The C++ Programming Language");
    b1.add_author("Bjarne Stroustrup");
    b1.set_publisher("Addison-Wesley");
    b1.set_year(2013);
    b1.set_isbn(9780321563842);
    sciences_lib.add_book(b1);

    b2.set_name("C++: The Complete Reference");
    b2.add_author("Herbert Schildt");
    b2.set_publisher("McGraw-Hill");
    b2.set_year(2003);
    b2.set_isbn(9780070532465);
    sciences_lib.add_book(b2);

    sciences_lib.print();

    novel_lib.set_name("Novel Library");
    novel_lib.add_day(tuesday);
    novel_lib.add_day(wednesday);
    novel_lib.add_day(thursday);
    novel_lib.add_day(friday);

    b3.set_name("Harry Potter and the Philosopher's Stone");
    b3.add_author("J. K. Rowling");
    b3.set_publisher("Bloomsbury");
    b3.set_year(1997);
    b3.set_isbn(9780747532699);
    novel_lib.add_book(b3);

    b4.set_name("Harry Potter and the Chamber of Secrets");
    b4.add_author("J. K. Rowling");
    b4.set_publisher("Bloomsbury");
    b4.set_year(1998);
    b4.set_isbn(9780747538493);
    novel_lib.add_book(b4);

    novel_lib.print();

    isbn = sciences_lib.get_isbns();
    std::cout << "Not sorted: \n";
    for(i = isbn.begin(); i != isbn.end(); i++){
        std::cout << *i << "\n";
    }

    std::cout << "Sorted: \n";
    std::sort(isbn.begin(), isbn.end());
    for(i = isbn.begin(); i != isbn.end(); i++){
        std::cout << *i << "\n";
    }
    return 0;
}