#include "library.h"
#include "book.h"
#include <stdio.h>

/* As stated in library.h */ 

int main()
{
    book_t *libro1 = book_create();
    book_t *libro2 = book_create();
    library_t *libreria1 = library_create();

    book_t *libro3 = book_create();
    book_t *libro4 = book_create();
    library_t *libreria2 = library_create();

    library_set_name(libreria1, "Sciences Library");
    library_add_day(libreria1, monday);
    library_add_day(libreria1, tuesday);
    library_add_day(libreria1, wednesday);
    library_add_day(libreria1, thursday);
    
    book_set_name(libro1, "The C Programming Language");
    book_add_author(libro1, "Brian W. Kernighan");
    book_add_author(libro1, "Dennis M. Ritchie");
    book_set_pubYearIsbn(libro1, "Prentice Hall", 1988, 9780131103627);

    book_set_name(libro2, "C: The Complete Reference");
    book_add_author(libro2, "Herbert Schildt");
    book_set_pubYearIsbn(libro2,"McGraw-Hil Education", 2000, 9780072121247);

    library_add_book(libreria1, *libro1);
    library_add_book(libreria1, *libro2);

    print_library(libreria1);
    
/**************************************************/

    library_set_name(libreria2, "Novel Library");
    library_add_day(libreria2, tuesday);
    library_add_day(libreria2, wednesday);
    library_add_day(libreria2, thursday);
    library_add_day(libreria2, friday);
    
    book_set_name(libro3, "Harry Potter and the Philosopher's Stone");
    book_add_author(libro3, "J. K. Rowling");
    book_set_pubYearIsbn(libro3, "Bloomsbury", 1997, 9780747532699);

    book_set_name(libro4, "Harry Potter and the Chamber of Secrets");
    book_add_author(libro4, "J. K. Rowling");
    book_set_pubYearIsbn(libro4,"Bloomsbury", 1998, 9780747538493);

    library_add_book(libreria2, *libro3);
    library_add_book(libreria2, *libro4);

    print_library(libreria2);

    book_free(libro1);
    book_free(libro2);
    book_free(libro3);
    book_free(libro4);
    library_free(libreria1);
    library_free(libreria2);


    return 0;
}