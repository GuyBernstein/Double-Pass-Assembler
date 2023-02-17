#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>


#include "utils.h"
#include "code.h" /* for checking reserved words */


#define ERR_OUTPUT_FILE stderr


char *strallocat(char *s0, char* s1)
{
	char *str = (char *)malloc_with_check(strlen(s0) + strlen(s1) + 1);
	strcpy(str, s0);
	strcat(str, s1);
	return str;
}


void *malloc_with_check(long size) 
{
	void *ptr = malloc(size);
	if (ptr == NULL) 
	{
		printf("Error: Fatal: Memory allocation failed.");
		exit(1);
	}
	return ptr;
}

int printf_line_error(line_info line, char *message, ...) 
{ /* Prints the errors into a file, defined above as macro */
	int result;
	va_list args; /* for formatting */
	/* Print file+line */
	fprintf(ERR_OUTPUT_FILE,"Error In %s:%ld: ", line.file_name, line.line_number);

	/* use vprintf to call printf from variable argument function (from stdio.h) with message + format */
	va_start(args, message);
	result = vfprintf(ERR_OUTPUT_FILE, message, args);
	va_end(args);

	fprintf(ERR_OUTPUT_FILE, "\n");
	return result;
}

/* This function recieves a string and an integer
 * preform checks on the first word of the given string
 * if found invalid lable returns print an invalid input message 
 * and return NULL
 * after all the checks returns the lable name */
bool isLabel(line_info line,char *lable)
{
	
	
	
	char *colon;/*a pointer to the colon occurrence in the line*/
	
	
	if(sscanf(line.content,"%s",lable) == 1)/*if able to read a word from line into lable string*/
	{
		
		/* if it was a try to define label, print errors if needed. */
		if ((colon = strchr(lable,':')) )/*check if its able to find colon in the lable*/
		{/*found colon*/
		
			

			/*check if something is after the colon*/
			if(strcmp(colon,":"))
			{/*found that the label isnt over with ':' */
				printf_line_error(line,
			                  "Invalid label name - needs a space after ':' at the the lable %s", lable);
				lable[0] = '\0';
				return TRUE; /* No valid symbol, and no try to define one */
			}
			colon[0] = '\0';/* get rid of the ':' in the label to check for validness*/
			

			if (!is_valid_label_name(lable)) 
			{
				
				printf_line_error(line,
			                  "Invalid label name - cannot be longer than 30 chars, may only start with letter be alphanumeric.");
				lable[0] = '\0';
				return TRUE; /* No valid symbol, and no try to define one */
			}
			
			return FALSE;
		}
		
		lable[0] = '\0';
		return FALSE; /* There was no error */
		
		
		
			
	}
	
	return FALSE; /* cant read a string */
	
}

bool is_valid_label_name(char *name) 
{
	
	/* Check length, first char is alpha and all the others are alphanumeric, and not saved word */
	return name[0] && strlen(name) <= MAX_LABLE_LEN && isalpha(name[0]) && is_alphanumeric_str(name+1)  &&
	       !is_reserved_word(name);
	      
}


bool is_reserved_word(char *name) 
{
	int fun , opc;
	/* check if register or command */
	get_opcode_func(name, &opc, (funct *) &fun);
	if (opc != NONE_OP || get_register_by_name(name) != NONE_REG || find_directive_by_name(name) != NONE_DIRE)
		return TRUE;

	return FALSE;
}

bool is_alphanumeric_str(char *string) 
{
	int i;
	/*check for every char in string if it is non alphanumeric char if it is function returns true*/
	for (i = 0; string[i]; i++) 
		if (!isalpha(string[i]) && !isdigit(string[i])) 
			return FALSE;
	
	return TRUE;
}



struct directive_lookup_item 
{
	char *name;
	directive value;
};

static struct directive_lookup_item
		directive_lookup_table[] = {
		{"string", STRING_DIRE},
		{"data",   DATA_DIRE},
		{"entry",  ENTRY_DIRE},
		{"extern", EXTERN_DIRE},
		{NULL, NONE_DIRE}
};

directive find_directive_by_name(char *name) 
{
	struct directive_lookup_item *curr_item;
	
	for (curr_item = directive_lookup_table; curr_item->name != NULL; curr_item++) 
	
		if (!strcmp(curr_item->name, name) ) 
			return curr_item->value;
		
	
	return NONE_DIRE;
}


int skipSpacesAndTabs(char *s) 
{
	int n=0;
	while(isspace(s[n]))
		n++;
	return n;
}




void removeSpaces(char *str) 
{
	int i;
	/* To keep track of non-space character count */
	int count = 0;
    
	/* Traverse the given string. If current character 
	 * is not space, then place it at index 'count++' */
	for (i = 0; str[i]; i++) 
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			str[count++] = str[i]; /* here count is incremented */
	}
    
	str[count] = '\0'; /* finish the string */
}
