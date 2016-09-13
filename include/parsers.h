#ifndef PARSERS_H
#define PARSERS_H

typedef void* (*parser_func_p)(const char*);

void* parser_copychar(const char* param);
void* parser_parseint(const char* param);

#endif
