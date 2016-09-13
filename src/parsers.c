#include <string.h>
#include <stdlib.h>
#include "../include/parsers.h"

/* data parsing functions */

void* parser_copychar(const char* param) {
        void* data = malloc(sizeof(char)*(strlen(param)+1));
        strcpy((char*)data, param);
        return data;
}

void* parser_parseint(const char* param) {
       void* data = malloc(sizeof(int));
       *((int*)data) = atoi(param);
       return data;
}
