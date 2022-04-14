/*

    Echoue de code
    Confirmar mensajes de error
    Convertir parametro a long solo si es necesario, no hacer el calculo antes
    Confirmar la conversion en CP a int y del param a LONG usando strol y distintos verificaciones
*/
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
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
         << "Written by Kevin Aceves <kevin.aceves-siordia@etud.univ-pau.fr> and Baptiste Genthon <baptiste.genthon@etud.univ-pau.fr>.\n";
}

bool validParamCodePostal(char* p1, int p2){
    //If conversion was valid
    if(p1 != NULL && p2 != -1){
        return true;
    }

    return false;
}

// Remember since sender and recipient are the same class we cna just make a function with the same behavior sending either sender or recipient on the if, rather than the same code
int parse_address(xml_node node, address_t* address){
    for(xml_node i = node.first_child(); i; i = i.next_sibling()) {
        if(!strcmp(i.name(), "city")){
            address->set_city(i.first_child().value());
        } 
        else if(!strcmp(i.name(), "country")){
            address->set_country(i.first_child().value());
        }
        else if(!strcmp(i.name(), "name")){
            address->set_name(i.first_child().value());
        }
        else if(!strcmp(i.name(), "postal-code")){
            errno = 0;
            char* temp;
            int val = 0;
                        
            val = strtol(i.first_child().value(), &temp, 10);

            if(temp == i.first_child().value() || *temp != '\0' || ((val == INT_MIN || val == INT_MAX) && errno == ERANGE)){
                throw str2i_error(i.first_child().value());
                return 1;
            }
            address->set_postal_code(val);
        } 
        else if(!strcmp(i.name(), "street")){
            address->set_street(i.first_child().value());
        }
    }

    return 0;
}

// Same goes for envelope c4 and dl, since they are childs of envelope we can do the same thing
int parse_envelope(xml_node node, envelope_t* envelope){
    for(xml_node i = node.first_child(); i; i = i.next_sibling()) {
        if(!strcmp(i.name(), "priority")) {
            if(strcmp(i.value(), "low")){
                envelope->set_priority(low);
            }
            else if(strcmp(i.value(), "medium")){
                envelope->set_priority(medium);
            }
            else if(strcmp(i.value(), "high")){
                envelope->set_priority(high);
            }
            else{
                envelope->set_priority(undefined);
            }
            
        } 
        else if(!strcmp(i.name(), "recipient")) {
            address_t recipient;
            if(parse_address(i, &recipient)){
                return 1;
            }
            envelope->set_recipient(recipient);
        } 
        else if(!strcmp(i.name(), "sender")) {
            address_t sender;
            if(parse_address(i, &sender)){
                return 1;
            }
            envelope->set_sender(sender);
        }
    }

    return 0;
}

// Parses document from node into company
int parse_doc(xml_node node, company_t* company){
    // Get company name
    if(!strcmp(node.first_attribute().name(), "name")){
        company->set_name(node.first_attribute().value());
    }

    // Iterate through company nodes (i.e envelopes, web)
    for(xml_node i = node.first_child(); i; i = i.next_sibling()){
        if(!strcmp(i.name(), "envelopes")) {
            for(xml_node j = i.first_child(); j; j = j.next_sibling()){
                if(strcmp(j.first_attribute().value(), "c4")) {
                    envelope_c4_t envelope_c4;
                    if(parse_envelope(j, &envelope_c4)){
                        return 1;
                    }
                    company->envelopes_push_back(envelope_c4);
                } 
                else if(strcmp(j.first_attribute().value(), "dl")){
                    envelope_dl_t envelope_dl;
                    if(parse_envelope(j, &envelope_dl)){
                        return 1;
                    }
                    company->envelopes_push_back(envelope_dl);
                }
            }
        }
        else if(!strcmp(i.name(), "web")) {
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

    if(!(doc.load_file(argv[1]))){ // Load file
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }

    if(strcmp(doc.first_child().name(), (char*) "company")){ // Check if its a company
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }

    try{
        parse_doc(doc.first_child(), &company); // Parse to company
    }
    catch(str2i_error &e){
        cerr << argv[0] << ": an exception occurred (" << e.what() << ")\n";
        return 1;
    }

    char str_input[BUFFER];
    char* command;
    do{
        char* param;
        int len_input = 0;
        long paramInt = 0;
        int c;
        
        cout << "EDP> ";
        fgets(str_input, BUFFER, stdin);
        len_input = strlen(str_input)-1;

        // If true clean the buffer, if false erase \n
        if(str_input[len_input] != '\n'){
            while((c = getchar ()) != '\n' && c != EOF);
        }
        else{
            str_input[len_input] = '\0';
        }
        
        // If there is an space, it will set command to before the space, and param after the space from str_input
        command = str_input;
        param = strstr(str_input, " ");
        if(param != NULL){
            param = param + 1;
            command[len_input-strlen(param)-1] = '\0';

            // Converts param to long in another variable
            errno = 0;
            char* temp;
            paramInt = strtol(param, &temp, 10);
            
            if(temp == param || *temp != '\0' || ((paramInt == LONG_MIN || paramInt == LONG_MAX) && errno == ERANGE)){
                paramInt = -1;
            }
            // Conversion ended with paramLong = param with type long if it worked, or error code 1 if not
            // We will be using param or paramLong depending whether we need to pass a string or an int
        }
        
        if(len_input > 18){
            cerr << argv[0] << " too many characters for the command\n";
        }
        else if(!strcmp(command, "e")){
            company.handle_e();
        }
        else if(!strcmp(command, "ec")){ 
            if(validParamCodePostal(param, paramInt)){
                company.handle_ec(paramInt);
            }
        }
        else if(!strcmp(command, "ecge")){ 
            if(validParamCodePostal(param, paramInt)){
                company.handle_ecge(paramInt);
            }
        }
        else if(!strcmp(command, "ecgt")){ 
            if(validParamCodePostal(param, paramInt)){
                company.handle_ecgt(paramInt);
            }
        }
        else if(!strcmp(command, "ecle")){ 
            if(validParamCodePostal(param, paramInt)){
                company.handle_ecle(paramInt);
            }
        }
        else if(!strcmp(command, "eclt")){ 
            if(validParamCodePostal(param, paramInt)){
                company.handle_eclt(paramInt);
            }
        }
        else if(!strcmp(command, "en")){ 
            if(param != NULL){
                company.handle_en(param);
            }
            else{
                cerr << argv[0] << " invalid parameter for the en command\n";
            }
        }
        else if(!strcmp(command, "h")){ 
            handle_h();
        }
        else if(!strcmp(command, "i")){ 
            company.handle_i();
            cout << "\n";
        }
        else if(!strcmp(command, "n")){ 
            company.handle_n();
            cout << "\n";
        }
        else if(!strcmp(command, "q")){
            continue;
        }
        else if(!strcmp(command, "v")){ 
            handle_v();
        }
        else if(!strcmp(command, "w")){ 
            company.handle_w();
            cout << "\n";
        }
        else if(strlen(command) > 0){
            cerr << argv[0] << " invalid command\n";
        }
    }while(strcmp(command, "q"));

    return 0;
}