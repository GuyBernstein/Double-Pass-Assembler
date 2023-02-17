#ifndef _DIRECTIVE_H
#define _DIRECTIVE_H

#include "declarations.h"


directive find_directive_from_index(line_info line, int *index);

int checkValidData(line_info line, char *data,short* numbers);
bool process_string_instruction(line_info line, int index, short *data, long *dc);
int checkValidString(line_info line, char *string,char *str);
bool insertDataToArray(short* input, short* output,long* dc);
bool insertStringToArray(char* input, short* output,long* dc);





#endif


