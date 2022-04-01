#include "company.h"

company_t::company_t():
    name(NULL),
    web(NULL)
    {}


string company_t::get_name() const{
    return this->name;
}


string company_t::get_web() const{
    return this->web;
}

void company_t::handle_e() const{

}

void company_t::handle_i() const{

}

void company_t::handle_n() const{

}

void company_t::handle_ec(int postal_code) const{

}

void company_t::handle_ecge(int postal_code) const{

}

void company_t::handle_ecgt(int postal_code) const{

}

void company_t::handle_ecle(int postal_code) const{

}

void company_t::handle_eclt(int postal_code) const{

}

void company_t::handle_en(string name) const{

}

void company_t::handle_w() const{

}

envelope_t company_t::envelopes_at(int index) const{
    //Delete when coding this, it's just for the compiler
    envelope_t env;
    return env;
}

void company_t::envelopes_push_back(envelope_t envelope){
    this->envelopes.push_back(envelope);
}

int company_t::envelopes_size() const{
    return envelopes.size(); // size returns the number of elements in vector envelopes
}

void company_t::set_name(string name){
    this->name = name;
}

void company_t::set_web(string web){
    this->web = web;
}


ostream &operator<<(ostream &os, const company_t &company);
