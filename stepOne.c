#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declarations.h"
#include "stepOne.h"
#include "utils.h"
#include "directive.h"
#include "code.h"


static bool process_code(line_info line, int i, long *ic, short* machineCommands);


bool stepOne(line_info line, short* machineCommands, short* machineData, long *IC, long *dc , table *symbol_table)
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

	
	
	
	/* if tried to define label, but it's invalid, return that an error occurred. */
	if (isLabel(line, symbol)) 
		return FALSE;
	


	if (symbol[0] != '\0') 
		for (; line.content[i] != ':'; i++); /* if symbol detected, start analyzing from it's deceleration end */
			i++;
			
	
	MOVE_TO_NOT_WHITE(line.content, i) /* Move to next not-white char */
	
	if (line.content[i] == '\n') 
		return TRUE; /* Label-only line - skip */
		
	/* if already defined as data/external/code and not empty line */
	if (find_by_types(*symbol_table, symbol, 3, EXTERNAL_SYMBOL, DATA_SYMBOL, CODE_SYMBOL)) {
		printf_line_error(line, "Symbol %s is already defined.", symbol);
		return FALSE;
	}	
	
	
	/* Check if it's a directive (starting with '.') */
	directive = find_directive_from_index(line, &i);
	
	
	if (directive == ERROR_DIRE) 
	/* Syntax error found */
		return FALSE;
		
	
	/* is a directive */
	if (directive != NONE_DIRE) 
	{
		
		/* if .string or .data, and symbol defined, put it into the symbol table */
		if((directive == DATA_DIRE || directive == STRING_DIRE) && symbol[0] != '\0')
			/* is data or string, add DC with the symbol to the table as data */
			add_table_item(symbol_table, symbol, *dc, DATA_SYMBOL);
			
		
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
			add_table_item(symbol_table, symbol, 0, EXTERNAL_SYMBOL); /* Extern value is defaulted to 0 */
			
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
	else 
	{
		/* if symbol defined, add it to the table */
		if (symbol[0] != '\0')
			add_table_item(symbol_table, symbol, *IC, CODE_SYMBOL);
		line.content += strlen(symbol);
		/* Analyze code */
		return process_code(line, i, IC, machineCommands);
	}
	
	return TRUE;
}


static bool process_code(line_info line, int i, long *ic, short* machineCommands) 
{
	char operation[8]; /* stores the string of the current code instruction */
	char *operands[2]; /* 2 strings, each for operand */
	opcode curr_opcode; /* the current opcode and funct values */
	funct curr_funct;
	long ic_before;
	int j, operand_count;
	

	
	/* Skip white chars */
	MOVE_TO_NOT_WHITE(line.content, i)
	
	/* if not too big instruction, copy it: */
	if(sscanf(line.content,"%6s",operation) == 1)
		printf("operation %s\n",operation);
	
	/* Get opcode & funct by command name into curr_opcode/curr_funct */
	get_opcode_func(operation, &curr_opcode, &curr_funct);
	/* If invalid operation (opcode is NONE_OP=-1), print and skip processing the line. */
	if (curr_opcode == NONE_OP) 
	{
		printf_line_error(line, "Unrecognized instruction: %s", operation);
		return FALSE; /* an error occurred */
	}
	return FALSE;
}


