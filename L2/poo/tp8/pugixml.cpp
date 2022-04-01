#include <iostream>
#include <cstring>
#include "pugixml.hpp"

using namespace std;
using namespace pugi;

int main(int argc, char** argv){
    xml_document doc;
    xml_node node;
    xml_parse_result result;
    
    if(argc != 2){
        std::cerr<<"invalid number of arguments\n";
        return 1;
    }

    if(!(result = doc.load_file(argv[1]))){
        cerr << "XML [" << argv[1] << "] unable to be parsed\nError description: " 
             << result.description() << "\n";
        return 1;
    }

    if(strcmp(doc.first_child().name(), (char*) "library") != 0){
        cerr << "File is not a library\n";
        return 1;
    }

    node = doc.first_child();
    cout << node.name() << ":\n\t" << node.first_attribute().name() << ": " << node.first_attribute().value() << "\n";
    
    for(xml_node i = node.first_child(); i; i = i.next_sibling()){
        if(strcmp(i.name(), "days") == 0){ //Days
            cout << "\t" << i.name() << ":\n";
            for(xml_node j = i.first_child(); j; j = j.next_sibling()){
                cout << "\t\t" << j.name() << ": " << j.first_child().value() << "\n";
            }
        }
        else if(strcmp(i.name(), "books") == 0){ //Books
            cout << "\t" << i.name() << ":\n";
            for(xml_node j = i.first_child(); j; j = j.next_sibling()){ //Book
                cout << "\t\t" << j.name() << ":\n";
                for(xml_node k = j.first_child(); k; k = k.next_sibling()){
                    if(strcmp(k.name(), "authors") == 0){
                        cout << "\t\t\t" << k.name() << ":\n";
                        for(xml_node l = k.first_child(); l; l = l.next_sibling()){
                            cout << "\t\t\t\t" << l.name() << ": " << l.first_child().value() << "\n";
                        }
                    }
                    else if(strcmp(k.name(), "publisher") == 0 || strcmp(k.name(), "year") == 0 || strcmp(k.name(), "isbn") == 0){
                        cout << "\t\t\t" << k.name() << ": " << k.first_child().value() << "\n";
                    }
                }
            }
        }
    }

    return 0;
}