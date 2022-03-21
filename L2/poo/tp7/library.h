#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include "book.h"

enum day_t{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

class library_t{
    private:
        char* name;
        std::vector<day_t> days;
        int ndays;
        std::vector<book_t> books;
        int nbooks;

    public:
        library_t();

        ~library_t();

        void set_name(char*);

        void add_day(day_t);
        void add_book(book_t);

        void print() const;
};

#endif