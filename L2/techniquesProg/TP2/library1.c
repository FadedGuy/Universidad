#include <stdio.h>

struct book_s
{
    char name[100];
    char authors[10][100];
    int nAuthors;
    char publisher[100];
    int year;
    long isbn;
};

enum day_e
{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

struct library_s
{
    char name[100];
    enum day_e days[7];
    int nDays;
    struct book_s books[100];
    int nBooks;
};

void book_print(struct book_s book)
{   
    int i;
    printf("(\"%s\" ,(", book.name);
    for(i = 0; i < book.nAuthors; i++)
    {   
        printf("\"%s\"", book.authors[i]);
        if(i != book.nAuthors-1)
        {
            printf(", ");
        }
    }
    printf("), \"%s\", %d, %ld)", book.publisher, book.year, book.isbn);
}

void library_print(struct library_s library)
{
    int i;
    printf("(\"%s\", (", library.name);
    for(i = 0; i < library.nDays; i++)
    {   
        printf("\"");
        switch(library.days[i])
        {
            case 0:
                printf("monday");
                break;
            case 1:
                printf("tuesday");
                break;
            case 2:
                printf("wednesday");
                break;
            case 3:
                printf("thursday");
                break;
            case 4:
                printf("friday");
                break;
            case 5:
                printf("saturday");
                break;
            case 6:
                printf("sunday");
                break;
            default:
                break;
        }
        printf("\"");
        if(i != library.nDays-1)
        {
            printf(", ");
        }
    }
    printf("), (");
    for(i = 0; i < library.nBooks; i++)
    {
        book_print(library.books[i]); 
    }
    printf("))\n");
}

int main()
{
    struct library_s sciencesLibrary = {"Sciences Library", 
                                       {monday, tuesday, wednesday, thursday},
                                        4, 
                                        {
                                            {
                                                "The C Programming Language", 
                                                {"Brian W. Kernighan", "Dennis M. Ritchie"}, 
                                                2, 
                                                "Prentice Hall", 
                                                1988, 
                                                9780131103627
                                            },
                                            {
                                                "C: The Complete Reference",
                                                {"Herbert Schildt"},
                                                1,
                                                "McGraw-Hill Education",
                                                2000,
                                                9780072121247
                                            }
                                        }, 
                                        2};

    struct library_s novelLibrary = {"Novel Library", 
                                    {tuesday, wednesday, thursday, friday},
                                    4,
                                    {
                                        {
                                            "Harry Potter and the Philospher's Stone",
                                            {"J. K. Rowling"},
                                            1,
                                            "Bloomsbury",
                                            1977,
                                            9780747532699
                                        }, 
                                        {
                                            "Harry Potter and the Chamber of Secrets",
                                            {"J. K. Rowling"},
                                            1,
                                            "Bloomsbury",
                                            1988,
                                            9780747538493
                                        }
                                    },
                                    2};

    library_print(sciencesLibrary);
    library_print(novelLibrary);

    return 0;
}