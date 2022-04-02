#include <iostream>
#include "envelope.h"

envelope_t::envelope_t():
    height(0),
    width(0)
    {}

int envelope_t::get_height() const {
    return this->height;
}

priority_t envelope_t::get_priority() const {
    return this->priority;
}

address_t envelope_t::get_recipient() const {
    return this->recipient;
}

address_t envelope_t::get_sender() const {
    return this->sender;
}

int envelope_t::get_width() const {
    return this->width;
}

void envelope_t::handle_e() const{
    cout << *this;
}

void envelope_t::handle_ec(int postal_code) const{
    
}

void envelope_t::handle_ecge(int postal_code) const{
    
}

void envelope_t::handle_ecgt(int postal_code) const{
    
}

void envelope_t::handle_ecle(int postal_code) const{
    
}

void envelope_t::handle_eclt(int postal_code) const{
    
}

void envelope_t::handle_en(string name) const{
    
}

void envelope_t::set_priority(priority_t priority){
    this->priority = priority;
}

void envelope_t::set_recipient(address_t recipient){
    this->recipient = recipient;
}

void envelope_t::set_sender(address_t sender){
    this->sender = sender;
}


ostream &operator<<(ostream &os, const envelope_t &envelope){
    os << "(" << envelope.get_sender() << " -> " << envelope.get_recipient() << " [" 
       << envelope.get_priority() << "] " << envelope.get_width() << "x" << envelope.get_height() << ")";

    return os;
}