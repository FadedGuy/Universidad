/*
    In projet file output is given as:
        ./edp.out: message
    do we need to put it in aswell since we have it in main in argv[0]
    or not.

    convert param to int in menu() and change argument on functions that use it
*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "address.h"
#include "company.h"
#include "envelope-c4.h"
#include "envelope-dl.h"
#include "envelope.h"
#include "str2i-error.h"
#include "str2l-error.h"
#include "pugixml.hpp"

#define BUFFER 21

using namespace pugi;
using namespace std;

void handle_h(){
    cout << "e: prints the envelopes\n" 
         << "ec CODE: prints the envelopes with the sender postal code equal to CODE\n"
         << "ecge CODE: prints the envelopes with the sender postal code greater than or equal to CODE\n"
         << "ecgt CODE: prints the envelopes with the sender postal code greater than CODE\n"
         << "ecle CODE: prints the envelopes with the sender postal code less than or equal to CODE\n"
         << "eclt CODE: prints the envelopes with the sender postal code less than CODE\n"
         << "en NAME: prints the envelopes with the sender name containing NAME\n"
         << "h: prints this help\n"
         << "i: prints information about the company\n"
         << "n: prints the company name\n"
         << "q: quits EDP\n"
         << "v: prints the EDP version\n"
         << "w: prints the company web address\n";
}

void handle_v(){
    cout << "EDP (Envelope Delivery Program) 20220422\n\n"
         << "Copyright (C) 2022 Kevin Aceves and Baptiste Genthon.\n\n"
         << "Written by Kevin Aceves <kevin.aceves-siordia@etud.unit-pau.fr> and Baptiste Genthon <baptiste.genthon@etud.univ-pau.fr>.\n";
}

void menu(company_t company){
    char str_input[BUFFER];
    char* command;
    char* param;
    int len_input = 0;
    int c;

    do{
        cout << "EDP> ";
        fgets(str_input, BUFFER, stdin);
        len_input = strlen(str_input)-1;

        if(str_input[len_input] != '\n'){
            while((c = getchar ()) != '\n' && c != EOF);
        }
        else{
            str_input[len_input] = '\0';
        }
        
        command = str_input;
        param = strstr(str_input, " ");
        if(param != NULL){
            param = param + 1;
            command[len_input-strlen(param)-1] = '\0';
        }
        
        if(len_input > 18){
            cerr << "too many characters for the command\n";
        }
        else if(!strcmp(str_input, "e")){
            company.handle_e();
        }
        else if(!strcmp(str_input, "ec")){ 
            company.handle_ec(0);
        }
        else if(!strcmp(str_input, "ecge")){ 
            company.handle_ecge(0);
        }
        else if(!strcmp(str_input, "ecgt")){ 
            company.handle_ecgt(0);
        }
        else if(!strcmp(str_input, "ecle")){ 
            company.handle_ecle(0);
        }
        else if(!strcmp(str_input, "eclt")){ 
            company.handle_eclt(0);
        }
        else if(!strcmp(str_input, "en")){ 
            company.handle_en("");
        }
        else if(!strcmp(str_input, "h")){ 
            handle_h();
        }
        else if(!strcmp(str_input, "i")){ 
            company.handle_i();
            cout << "\n";
        }
        else if(!strcmp(str_input, "n")){ 
            company.handle_n();
            cout << "\n";
        }
        else if(!strcmp(str_input, "q")){
            continue;
        }
        else if(!strcmp(str_input, "v")){ 
            handle_v();
        }
        else if(!strcmp(str_input, "w")){ 
            company.handle_w();
            cout << "\n";
        }
        else{
            cerr << "invalid command\n";
        }

    }while(strcmp(str_input, "q"));
}

// Remember since sender and recipient are the same class we cna just make a function with the same behavior sending either sender or recipient on the if, rather than the same code
void parse_address(xml_node node, address_t* address){
    for(xml_node i = node.first_child(); i; i = i.next_sibling()) {
        if(strcmp(i.name(), "city") == 0){
            address->set_city(i.first_child().value());
        } 
        else if(strcmp(i.name(), "country") == 0){
            address->set_country(i.first_child().value());
        }
        else if(strcmp(i.name(), "name") == 0){
            address->set_name(i.first_child().value());
        }
        else if(strcmp(i.name(), "postal-code") == 0){
            long val = 0;
            val = strtol(i.first_child().value(), NULL, 10);
            address->set_postal_code(val);
        } 
        else if(strcmp(i.name(), "street") == 0){
            address->set_street(i.first_child().value());
        }
    }
}

// Same goes for envelope c4 and dl, since they are childs of envelope we can do the same thing
void parse_envelope(xml_node node, envelope_t* envelope){
    for(xml_node k = node.first_child(); k; k = k.next_sibling()) {
        if(strcmp(k.name(), "priority") == 0) {
            if(strcmp(k.value(), "low")){
                envelope->set_priority(low);
            }
            else if(strcmp(k.value(), "medium")){
                envelope->set_priority(medium);
            }
            else if(strcmp(k.value(), "high")){
                envelope->set_priority(high);
            }
            else{
                envelope->set_priority(undefined);
            }
            
        } 
        else if(strcmp(k.name(), "recipient") == 0) {
            address_t recipient;
            parse_address(k, &recipient);
            envelope->set_recipient(recipient);
        } 
        else if(strcmp(k.name(), "sender") == 0) {
            address_t sender;
            parse_address(k, &sender);
            envelope->set_sender(sender);
        }
    }
}

int parse_doc(xml_node node, company_t* company){
    if(strcmp(node.first_attribute().name(), "name") == 0) {
        company->set_name(node.first_attribute().value());
    }

    for(xml_node i = node.first_child(); i; i = i.next_sibling()) {
        if(strcmp(i.name(), "envelopes") == 0) {
            for(xml_node j = i.first_child(); j; j = j.next_sibling()) {
                envelope_c4_t envelope_c4;
                envelope_dl_t envelope_dl;

                if(strcmp(j.first_attribute().value(), "c4")) {
                    parse_envelope(j, &envelope_c4);
                    company->envelopes_push_back(envelope_c4);
                } else if(strcmp(j.first_attribute().value(), "dl")) {
                    parse_envelope(j, &envelope_dl);
                    company->envelopes_push_back(envelope_dl);
                }
            }
        }
        else if(strcmp(i.name(), "web") == 0) {
            company->set_web(i.first_child().value());
        }
     }
     
     return 0;
}

int main(int argc, char** argv){
    company_t company;
    xml_document doc;

    if(argc != 2){
        cerr << argv[0] << ": invalid number of arguments\n";
        return 1;
    }

    if(!(doc.load_file(argv[1]))){ //Load file
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }
    if(strcmp(doc.first_child().name(), (char*) "company") != 0){ //Check if its a company
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }
    if(parse_doc(doc.first_child(), &company)){ //Parse to company
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }

    menu(company);

    return 0;
}