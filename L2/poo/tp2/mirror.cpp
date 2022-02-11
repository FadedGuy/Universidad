#include <cstdio>
#include <cstring>

void mirror(const char* str, char* res){
    int j = 0;
    for(int i = strlen(str)-1; i >= 0; i--){
        res[j] = str[i];
        j++;
    }
    res[j] = '\0';
}

int main(int argc, char** argv){
    if(argc != 2 || strlen(argv[1]) > 10){
        argc != 2 ? fprintf(stderr, "Invalid number of arguments\n") : fprintf(stderr, "the string length is greater than 10\n");
        return 1;
    }

    char res[11];
    mirror(argv[1], res);
    printf("\"%s\"\n", res);
    return 0;
}