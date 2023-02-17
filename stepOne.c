#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declarations.h"
#include "stepOne.h"
#include "utils.h"
#include "directive.h"


bool stepOne(line_info line, short* machineCommands, short* machineData, long *IC, long *dc )
{

	int j;
	int i = 0;
	directive directive;
	char symbol[MAX_LINE];
	

	
	short validData[MAX_LINE];/*an array of shorts, containing the file .data content*/
	char validString[MAX_LINE];/*the string after the .string in the file*/
	
	char *linePtr;/*a pointer to the file line*/
	
	


	
	
	
	MOVE_TO_NOT_WHITE(line.content, i) /* Move to next non-white char */
	
	if (!line.content[i] || line.content[i] == '\n' || line.content[i] == EOF || line.content[i] == ';')
		return TRUE; /* Empty/Comment line - no errors found (of course) */

		
		


	if (symbol[0] != '\0') 
		for (; line.content[i] != ':'; i++); /* if symbol detected, start analyzing from it's deceleration end */
			i++;
			
	
	MOVE_TO_NOT_WHITE(line.content, i) /* Move to next not-white char */
	
	if (line.content[i] == '\n') 
		return TRUE; /* Label-only line - skip */	
	
	/* if already defined as data/external/code and not empty line */
	
	
	/* Check if it's a directive (starting with '.') */
	directive = find_directive_from_index(line, &i);
	
	
	if (directive == ERROR_DIRE) 
	/* Syntax error found */
		return FALSE;
		
	
	/* is a directive */
	if (directive != NONE_DIRE) 
	{
			
		/* if .string or .data, and symbol defined, put it into the symbol table */
		if((directive == DATA_DIRE || directive == STRING_DIRE) && symbol[0] != '\0');
			/* is data or string, add DC with the symbol to the table as data */
			
		
		/*found that directive is .string*/
		if (directive == STRING_DIRE)		
		{
			linePtr = line.content+i;
			if((checkValidString(line,linePtr,validString)) == 1)
				return insertStringToArray(validString,machineData,dc); 
		}
		/* found that directive is .data */
		else if (directive == DATA_DIRE)
		{
			
			linePtr = line.content+i;
			if((checkValidData(line,linePtr,validData)) == 1)
				return insertDataToArray(validData,machineData,dc); 
		}	
		/* if .extern, add to externals symbol table */
		else if (directive == EXTERN_DIRE) 
		{
			
			MOVE_TO_NOT_WHITE(line.content, i)
			/* if external symbol detected, start analyzing from it's deceleration end */
			for (j = 0; line.content[i] && line.content[i] != '\n' && line.content[i] != '\t' &&
				line.content[i] != ' ' && line.content[i] != EOF; i++, j++) 
			{
				symbol[j] = line.content[i];
			}
			symbol[j] = '\0';/*end the string*/
			
			/* If invalid external label name, it's an error */
			if (!is_valid_label_name(symbol)) 
			{
				printf_line_error(line, "Invalid external label name: %s", symbol);
				return TRUE;
			}
			
		}
		
		/* if entry and symbol defined, print error */
		else if (directive == ENTRY_DIRE && symbol[0] != '\0') 
		{
			printf_line_error(line, "Can't define a label to an entry directive.");
			return FALSE;
		}
		/* .entry is handled in second pass! */
	} /* end if (directive != NONE) */
	
	/* not a directive=>it's a command! */
	
	
				
			
		
	
	return TRUE;
}


































