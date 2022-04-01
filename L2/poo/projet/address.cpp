#include "address.h"

address_t::address_t():
    city(NULL),
    country(NULL),
    name(NULL),
    postal_code(0),
    street(NULL)
    {}

string address_t::get_city() const{
    return this->city;
}

string address_t::get_country() const{
    return this->country;
}

string address_t::get_name() const{
    return this->name;
}

int address_t::get_postal_code() const{
    return this->postal_code;
}

string address_t::get_street() const{
    return this->street;
}

void address_t::set_city(string city){
    this->city = city;
}

void address_t::set_country(string country){
    this->country = country;
}

void address_t::set_name(string name){
    this->name = name;
}

void address_t::set_postal_code(int postal_code){
    this->postal_code = postal_code;
}

void address_t::set_street(string street){
    this->street = street;
}


ostream &operator<<(ostream &os, const address_t &address);