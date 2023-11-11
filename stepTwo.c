#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stepTwo.h"
#include "utils.h"





/* This function processes a single line in the second pass of an assembly file.
   It checks if the line is empty or a comment, and if not, it processes the line as a directive or a label.
   If the line is an entry directive, it adds the label to the symbol table.
*/
bool stepTwo(line_info line, table *symbol_table) 
{
	char *indexOfColon; /* Pointer to the location of the colon character in the line */
	char *entryName = ".entry"; /* String that represents the ".entry" directive */
	char *token;/* Pointer to the current token in the line */
	table_node *node;/* Pointer to a node in the symbol table */
	int i = 0;/* Index of the current character in the line */
	
	
	/* Move to next non-white char */
	MOVE_TO_NOT_WHITE(line.content, i) 
	
	/* Empty/Comment line - no errors found (of course) */
	if (!line.content[i] || line.content[i] == '\n' || line.content[i] == EOF || line.content[i] == ';')
		return TRUE; 
		
	indexOfColon = strchr(line.content, ':');
	
	/*check for label */
	if (indexOfColon != NULL) 
		i = indexOfColon - line.content + 1;/*advance the index to after the lable*/

	MOVE_TO_NOT_WHITE(line.content, i)


	/* Check for directive */
	if (line.content[i] == '.') 
	{
		/*if it's entry we add it to the symbol table*/
		if (strncmp(entryName, line.content, strlen(entryName)) == 0) 
		{
			i += strlen(entryName);/*advance the index to after the .entry */
			MOVE_TO_NOT_WHITE(line.content, i)
			token = strtok(line.content + i, " \n\t");/*get the .entry content*/
			/* if point to nothing after .entry*/
			if (token == NULL) 
			{
				printf_line_error(line, "Invalid - no label name for .entry directive.");
				return FALSE;
			}
			/* check if the symbol is not in the table */
			if (find_by_types(*symbol_table, token, 1, ENTRY_SYMBOL) == NULL) 
			{
				
				token = strtok(line.content + i, "\n"); /*get name of label*/
				if (token[0] == '&') 
					token++;
				/* if symbol is not defined as data/code */
				if ((node = find_by_types(*symbol_table, token, 2, DATA_SYMBOL, CODE_SYMBOL)) == NULL) 
				{
					/* if defined as external print error */
					if ((node = find_by_types(*symbol_table, token, 1, EXTERNAL_SYMBOL)) != NULL) 
					{
						printf_line_error(line, "The symbol %s is already defined as external, can't redefine as entry",
						                  node->key);
						return FALSE;
					}
					/* cant define a node symbol that isnt defined as data/code in the file */
					printf_line_error(line, "The symbol %s for .entry is undefined.", token);
					return FALSE;
				}
				add_table_item(symbol_table, token, node->value, ENTRY_SYMBOL);
			}
			
		}
	}
	return TRUE;
}

/* This function processes the operand of an instruction in the second pass of an assembly file.
   It finds the node of the label in the symbol table, sets the address of the machine code word and 
   "lights" the right ARE bits according to the label type (external/relocatable).
*/
bool process_spass_operand(line_info line,short ic,line_code* machineCommands,table *symbol_table) 
{
	int labelValue; /* stores the address of the label */
	table_node *node; /* stores the node of the label in the symbol table */
	
	/* Find the node of the label in the symbol table */
	node = find_by_types(*symbol_table, machineCommands->code_info.label, 3, DATA_SYMBOL, CODE_SYMBOL, EXTERNAL_SYMBOL);
	
	/* If the node is not found in the symbol table, print an error message and return FALSE */
	if (node == NULL) 
	{
		printf_line_error(line, "The symbol %s not found", machineCommands->code_info.label);
		return FALSE;
	}
	/*found symbol*/
	
	labelValue = node->value;
	machineCommands->code_info.code  = labelValue<<2;/*set the adress of the machine code word*/

	
	/*"light" the right ARE bits*/
	if (node->type == EXTERNAL_SYMBOL)
	{
		/* Add to externals reference table if it's an external. increase ic because it's the next word */
		add_table_item(symbol_table, machineCommands->code_info.label, (ic) + IC_START_VALUE, EXTERNAL_REFERENCE);
		machineCommands->code_info.code  |= EXTERNAL; /*external ARE*/
	}
	else
		machineCommands->code_info.code  |= RELOCATEBLE; /*relocatable ARE*/
		 
		

	return TRUE;
}



