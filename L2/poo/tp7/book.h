#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <vector>

class book_t{
    private:
        char* name;
        std::vector<char*> authors;
        int nauthors;
        char* publisher;
        int year;
        long isbn;

    public:
        book_t();

        ~book_t();

        void set_name(char*);
        void set_publisher(char*);
        void set_year(int);
        void set_isbn(long);

        void add_author(char*);

        void print() const;
};

#endif