#include <iostream>
#include "company.h"

company_t::company_t():
    name("undefined"),
    web("undefined")
    {}


string company_t::get_name() const{
    return this->name;
}


string company_t::get_web() const{
    return this->web;
}

void company_t::handle_e() const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_e();
        cout << "\n";
    }
}

void company_t::handle_i() const{
    cout << *this;
}

void company_t::handle_n() const{
    cout << this->get_name();
}

void company_t::handle_ec(int postal_code) const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_ec(postal_code);
    }
}

void company_t::handle_ecge(int postal_code) const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_ecge(postal_code);
    }
}

void company_t::handle_ecgt(int postal_code) const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_ecgt(postal_code);
    }
}

void company_t::handle_ecle(int postal_code) const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_ecle(postal_code);
    }
}

void company_t::handle_eclt(int postal_code) const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_eclt(postal_code);
    }
}

void company_t::handle_en(string name) const{
    vector<envelope_t>::const_iterator i = this->envelopes.begin();
    for(; i != this->envelopes.end(); ++i){
        i->handle_en(name);
    }
}

void company_t::handle_w() const{
    cout << this->get_web();
}

envelope_t company_t::envelopes_at(int index) const{
    //Either verify before-hand that it's a valid index or catch exception
    try{
        return this->envelopes.at(index);
    }
    catch(out_of_range &e){
        cerr << "an exception ocurred: " << e.what() << "\n";
        return envelope_t();
    }
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


ostream &operator<<(ostream &os, const company_t &company){
    string envelopes_str;
    os << "(" << company.get_name() << ", " << company.get_web() << ", (" 
       << envelopes_str << "))";
       
    return os;
}
