#ifndef _UTILS_H
#define _UTILS_H

#include "declarations.h"


/** moves the index to the next place in string where the char isn't white */
#define MOVE_TO_NOT_WHITE(string, index) \
        for (;string[(index)] && (string[(index)] == '\t' || string[(index)] == ' '); (++(index)))\
        	;

/* function declaration */



directive find_directive_by_name(char *name);


bool is_valid_label_name(char *name);
bool is_reserved_word(char *name);
bool is_alphanumeric_str(char *string);

int printf_line_error(line_info line, char *message, ...);
char *strallocat(char *s0, char* s1);
void *malloc_with_check(long size);
bool isLabel(line_info line, char *symbol_dest);
int isDirective(char *line);
void removeSpaces(char *str) ;
int skipSpacesAndTabs(char *s) ;












#endif


