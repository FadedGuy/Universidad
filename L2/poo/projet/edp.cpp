/*
    In projet file output is given as:
        ./edp.out: message
    do we need to put it in aswell since we have it in main in argv[0]
    or not.
*/

#include <cstdio>
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
        
        if(!strcmp(str_input, "e")){
            cout << "e command\n";
        }
        else if(!strcmp(str_input, "ec")){ 
            cout << "ec command\n";
        }
        else if(!strcmp(str_input, "ecge")){ 
            cout << "ecge command\n";
        }
        else if(!strcmp(str_input, "ecgt")){ 
            cout << "ecgt command\n";
        }
        else if(!strcmp(str_input, "ecle")){ 
            cout << "ecle command\n";
        }
        else if(!strcmp(str_input, "eclt")){ 
            cout << "eclt command\n";
        }
        else if(!strcmp(str_input, "en")){ 
            cout << "en command\n";
        }
        else if(!strcmp(str_input, "h")){ 
            handle_h();
        }
        else if(!strcmp(str_input, "i")){ 
            cout << "i command\n";
        }
        else if(!strcmp(str_input, "n")){ 
            cout << "n command\n";
        }
        else if(!strcmp(str_input, "q")){
            continue;
        }
        else if(!strcmp(str_input, "v")){ 
            handle_v();
        }
        else if(!strcmp(str_input, "w")){ 
            cout << "w command\n";
        }
        else{
            cerr << "invalid command\n";
        }

    }while(strcmp(str_input, "q"));
}

void parse_doc(xml_document doc, company_t company){
    
}

int main(int argc, char** argv){
    company_t company;
    xml_document doc;

    if(argc != 2){
        cerr << argv[0] << ": invalid number of arguments\n";
        return 1;
    }    
    if(!(doc.load_file(argv[1]))){
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }
    // parse_doc(doc, company);

    menu(company);

    return 0;
}