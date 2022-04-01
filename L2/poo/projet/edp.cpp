#include <iostream>
#include "address.h"
#include "company.h"
#include "envelope-c4.h"
#include "envelope-dl.h"
#include "envelope.h"
#include "str2i-error.h"
#include "str2l-error.h"
#include "pugixml.hpp"

using namespace pugi;
using namespace std;

int main(int argc, char** argv){
    xml_document doc;

    if(argc != 2){
        cerr << argv[0] << ": invalid number of arguments\n";
        return 1;
    }    
    if(!(doc.load_file(argv[1]))){
        cerr << argv[0] << ": unable to parse the document\n";
        return 1;
    }

    cout << "EDP> ";

    return 0;
}