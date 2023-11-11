#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declarations.h"
#include "stepOne.h"
#include "utils.h"
#include "directive.h"


 
/*

 * Function to process a single file and perform the first pass, which includes:

 * Processing directives and commands
 * Adding labels to the symbol table
 * Generating machine code and data to be written to file in the second pass
 * Returns TRUE if the first pass was successful, FALSE otherwise. */
bool stepOne(line_info line,line_code* machineCommands, short* machineData, short *ic, short *dc , table *symbol_table)
{

	int j;
	int i = 0;
	directive directive;
	char symbol[MAX_LINE],symbolErr[MAX_LINE];
	int countDataNums = 0;/* a count of how many numbers are in .data directive*/

	
	short validData[MAX_LINE];/*an array of shorts, containing the file .data content*/
	char validString[MAX_LINE];/*the string after the .string in the file*/
	
	char *linePtr;/*a pointer to the file line*/
	
	


	
	
	
	MOVE_TO_NOT_WHITE(line.content, i) /* Move to next non-white char */
	
	if (!line.content[i] || line.content[i] == '\n' || line.content[i] == EOF || line.content[i] == ';')
		return TRUE; /* Empty/Comment line - no errors found (of course) */

	
	
	
	/* if tried to define label, but it's invalid, return that an error occurred, and print a proper message */
	if (!isLabel(line, symbol)) 
		return FALSE;
	
	/* if symbol is not empty (i.e. a label was defined) */
	if(symbol[0] != '\0')
		i += (strlen(symbol) +1) ;/* advance the index to be after the label, and after the ':' */
		
	
	MOVE_TO_NOT_WHITE(line.content, i) /* Move to next not-white char */
	
	/* if line only contains a label, return TRUE */
	if (line.content[i] == '\n') 
		return TRUE; 
		
	/* if already defined as data/external/code  */
	if (find_by_types(*symbol_table, symbol, 3, EXTERNAL_SYMBOL, DATA_SYMBOL, CODE_SYMBOL)) 
	{
		printf_line_error(line, "Symbol %s is already defined.", symbol);
		return FALSE;
	}	
	
	
	/* Check if it's a directive (starting with '.') */
	directive = find_directive_from_index(line, &i);
	
	/* if syntax error found, return FALSE */
	if (directive == ERROR_DIRE) 
		return FALSE;
		
	
	/* is a directive */
	if (directive != NONE_DIRE) 
	{
		/* set linePtr to point to the start of the directive */
		linePtr = line.content+i;
		
		/*found that directive is .string*/
		if (directive == STRING_DIRE)		
		{
			/*check if the string is valid*/
			if((checkValidString(line,linePtr,validString)) == 1)
			{
				/* if there is a label before the string and the string is valid, add to symbol table */
				if(symbol[0] != '\0')
					add_table_item(symbol_table, symbol, *dc, DATA_SYMBOL);
					
				/* insert the string to machineData and increment dc as needed */
				insertStringToArray(validString,machineData,dc);
				return TRUE;
			}
			/* .string directive is not valid */
			else
				return FALSE; 
		}
		/* found that directive is .data */
		else if (directive == DATA_DIRE)
		{
			/*check if the data is valid*/
			if((countDataNums = checkValidData(line,linePtr,validData)) != 0)
			{
				/* if there is a label before the data and the data is valid, add to symbol table */
				if(symbol[0] != '\0')
					add_table_item(symbol_table, symbol, *dc, DATA_SYMBOL);
				
				/* insert the data to machineData and increment dc as needed */
				insertDataToArray(validData,machineData,dc,countDataNums); 
				return TRUE;
			}
			/*.data directive is not valid*/
			else
				return FALSE; 
		}	
		/* if .extern, add to externals symbol table */
		else if (directive == EXTERN_DIRE) 
		{
			
			/* if extern and symbol defined, print error */
			if (symbol[0] != '\0') 
			{
				printf_line_error(line, "Can't define a label to an extern directive.");
				return FALSE;
			}
			/* Read the symbol that follows .extern directive, check if there is more than one symbol */
			j = sscanf(line.content+i,"%s %s",symbol,symbolErr);
			
			/*advance the pointer to after the symbol name*/
			i += strlen(symbol);
			
			/* if no symbol provided or invalid symbol name, print error and return FALSE */
			if (j <= 0 || symbol[0] == '\0' || !is_valid_label_name(symbol)) 
			{
				printf_line_error(line, "Extern directive must be followed by a valid symbol name.");
				return FALSE;	
			}
			
			/* if more than one symbol provided, print error and return FALSE */
			if( j == 2)
			{
				printf_line_error(line, "Can't define more than one symbol to an external directive");
				return FALSE;
			}
			
			/* if already defined as data/external/code */
			if (find_by_types(*symbol_table, symbol, 3, EXTERNAL_SYMBOL, DATA_SYMBOL, CODE_SYMBOL)) 
			{
				printf_line_error(line, "External symbol %s is already defined.", symbol);
				return FALSE;
			}	
			
			add_table_item(symbol_table, symbol, 0, EXTERNAL_SYMBOL); /* Extern value is defaulted to 0 */
			
			
		}
		
		/* if directive is .entry and symbol defined, print error and return FALSE */
		else if (directive == ENTRY_DIRE && symbol[0] != '\0') 
		{
			printf_line_error(line, "Can't define a label to an node directive.");
			return FALSE;
		}
		/* .entry directive is handled in second pass! */
	} /* end if (directive != NONE) */
	
	/* not a directive=>it's a command! */
	else
	{
		/* if symbol defined, add it to the table */	
		if (symbol[0] != '\0')
			add_table_item(symbol_table, symbol, *ic, CODE_SYMBOL);
				
	
		/* Analyze code from start*/
		return process_commands(line, i, ic, machineCommands);
	}
	/* if all went well, return TRUE */
	return TRUE;
	

}

/**
 * Processes a command line by extracting the command string, getting the corresponding opcode, 
 * and then calling the appropriate function to process the command based on its opcode group. 
 * Returns TRUE if the command was processed successfully, or FALSE if there was an error.
 **/
bool process_commands(line_info line, int i, short *ic,line_code* machineCommands) 
{

	char command[MAX_LINE]; /* stores the string of the current command */
	char temp_line[MAX_LINE];/* a buffer of the command content to check for validness*/
	opcode curr_opcode; /* the current opcode */
	
	/* Skip white chars */
	MOVE_TO_NOT_WHITE(line.content, i)
	
	/* Get the command string */
	sscanf(line.content+i,"%s",command);
	
	
	/* Get opcode by command name into curr_opcode */
	get_opcode(command, &curr_opcode);
	
	/* If invalid command (opcode is NONE_OP=-1), print and skip processing the line. */
	if (curr_opcode == NONE_OP ) 
	{
		printf_line_error(line, "Unrecognized command: %s", command);
		return FALSE; /* an error occurred */
	}
	/* Set i to point to the end of the command string */
	i += strlen(command);
	
	
	MOVE_TO_NOT_WHITE(line.content, i);/*move to the next non white char*/
	
	/* Copy the rest of the line (command content) to temp_line */
	strcpy(temp_line,line.content+i);
	
	/* Process the group command and return the result */
	
	if ((curr_opcode >= MOV_OP && curr_opcode<=SUB_OP) || curr_opcode == LEA_OP) 
	{ /*opcode is in first group */
		if(!firstGroup(line,curr_opcode,temp_line,ic,machineCommands,command))
			return FALSE;
	}
	else if (curr_opcode >=NOT_OP && curr_opcode<=JSR_OP) 
	{ /*opcode is in second group */
		if(!secondGroup(line,curr_opcode,temp_line,ic,machineCommands, command))
			return FALSE;
	}
	else
	{
		if(!thirdGroup(line,curr_opcode,temp_line,ic,machineCommands,command))
			return FALSE;
	}
	
	/* If all went well, return TRUE */
	return TRUE;
}
































