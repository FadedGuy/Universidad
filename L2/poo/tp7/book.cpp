#include "book.h"

book_t::book_t(){
    this->name = NULL;
    this->nauthors = 0;
    this->publisher = NULL;
    this->year = 0;
    this->isbn = 0;
}

book_t::~book_t(){}

void book_t::set_name(char* name){
    this->name = name;
}

void book_t::set_publisher(char* publisher){
    this->publisher = publisher;
}

void book_t::set_year(int year){
    this->year = year;
}

void book_t::set_isbn(long isbn){
    this->isbn = isbn;
}

void book_t::add_author(char* author){
    this->authors.push_back(author);
    this->nauthors++;
}

void book_t::print() const{
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