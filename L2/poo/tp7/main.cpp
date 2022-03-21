#include "book.h"
#include "library.h"

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
    return 0;
}