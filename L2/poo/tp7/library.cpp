#include "library.h"

library_t::library_t(){
    this->name = NULL;
    this->ndays = 0;
    this->nbooks = 0;
}

library_t::~library_t(){}

void library_t::set_name(char* name){
    this->name = name;
}

void library_t::add_day(day_t day){
    this->days.push_back(day);
    this->ndays++;
}

void library_t::add_book(book_t book){
    this->books.push_back(book);
    this->nbooks++;
}

void library_t::print() const{
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