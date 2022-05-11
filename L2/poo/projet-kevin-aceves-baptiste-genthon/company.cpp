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
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
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
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
        i->handle_ec(postal_code);
    }
}

void company_t::handle_ecge(int postal_code) const{
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
        i->handle_ecge(postal_code);
    }
}

void company_t::handle_ecgt(int postal_code) const{
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
        i->handle_ecgt(postal_code);
    }
}

void company_t::handle_ecle(int postal_code) const{
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
        i->handle_ecle(postal_code);
    }
}

void company_t::handle_eclt(int postal_code) const{
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
        i->handle_eclt(postal_code);
    }
}

void company_t::handle_en(string name) const{
    for(vector<envelope_t>::const_iterator i = this->envelopes.begin(); i != this->envelopes.end(); ++i){
        i->handle_en(name);
    }
}

void company_t::handle_w() const{
    cout << this->get_web();
}

envelope_t company_t::envelopes_at(int index) const{
    //Verify it is a valid index
    if(index >= 0 && index < envelopes_size()){
        return this->envelopes.at(index);
    }

    return envelope_t();
}

void company_t::envelopes_push_back(envelope_t envelope){
    this->envelopes.push_back(envelope);
}

int company_t::envelopes_size() const{
    return envelopes.size();
}

void company_t::set_name(string name){
    this->name = name;
}

void company_t::set_web(string web){
    this->web = web;
}

ostream &operator<<(ostream &os, const company_t &company){
    os << "(" << company.get_name() << ", " << company.get_web() << ", (" ;

    for(int i = 0; i < company.envelopes_size(); i++){
        envelope_t envelope = company.envelopes_at(i);
        os << envelope;
        if(i != company.envelopes_size()-1){
            os << ", ";
        }
    }
    os << "))";  
    
    return os;
}
