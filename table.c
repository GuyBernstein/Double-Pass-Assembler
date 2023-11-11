
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "table.h"
#include "utils.h"

/* This function adds an item to a table. */
/* It takes in the table head, a key, a value, and a symbol type as parameters. */
void add_table_item(table *head, char *key, short value, symbol_type type) 
{
	/* Declare local variables */
	char *temp_key; /* Temporary variable to hold the key */
	table prev_node, curr_node, new_node; /* Pointers to previous, current, and new nodes */

	/* Allocate memory for the new node */
	new_node = (table) malloc_with_check(sizeof(table_node));

	/* Allocate memory for the temporary key */
	temp_key = (char *) malloc_with_check(strlen(key) + 1);

	/* Copy the key into the temporary variable */
	strcpy(temp_key, key);

	/* Assign the values to the new node */
	new_node->key = temp_key;
	new_node->value = value;
	new_node->type = type;

	/* If the table is null or the new node's value is less than the head's value, set the new node as the head */
	if ((*head) == NULL || (*head)->value > value) 
	{
		new_node->next = (*head);
		(*head) = new_node;
		return;
	}

	/* Insert the new table node, keeping it sorted */
	curr_node = (*head)->next;
	prev_node = *head;

	while (curr_node != NULL && curr_node->value < value) 
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	/*set the next pointer to not lose the list*/
	new_node->next = curr_node;
	prev_node->next = new_node;
}

/* This function frees the memory allocated for a table. */
/* It takes in the table head as a parameter. */
void free_table(table head) 
{
	/* Declare local variables */
	table prev_node, curr_node = head;

	/* Traverse the list and free each node */
	while (curr_node != NULL) 
	{
		prev_node = curr_node;
		curr_node = curr_node->next;

		/* Free the memory allocated for the key */
		free(prev_node->key);

		/* Free the memory allocated for the node */
		free(prev_node);
	}
}

    
/* This function adds a value to a specific symbol type in a table. */
/* It takes in the table head, the value to add, and the symbol type as parameters. */
void add_value_to_type(table head, short to_add, symbol_type type) 
{
	/* Declare a table(the list) */
	table curr_node;

	/* Traverse the list and add the value to each node with the same symbol type */
	for (curr_node = head; curr_node != NULL; curr_node = curr_node->next)
	{
		if (curr_node->type == type) 
			curr_node->value += to_add;
	}	
}


/* This function finds a node in a table by a given key and list of valid symbol types. 
 * It takes in the table head, the key to search for, the number of valid symbol types, 
 * and a variable list of symbol types as parameters. */
table_node *find_by_types(table head, char *key, int symbol_count, ...) 
{
	int i;
	/* Allocate memory for an array of valid symbol types */
	symbol_type *valid_symbol_types = malloc_with_check((symbol_count) * sizeof(int));

	/* Build the list of valid symbol types from the variable argument list */
	va_list arglist;
	va_start(arglist, symbol_count);
	for (i = 0; i < symbol_count; i++) 
		valid_symbol_types[i] = va_arg(arglist, symbol_type);
	va_end(arglist);

	/* If the table is empty, there is nothing to search, so return NULL */
	if (head == NULL) 
	{
		free(valid_symbol_types);
		return NULL;
	}

	/* Iterate over the table and the array of valid symbol types */
	do {
		for (i = 0; i < symbol_count; i++) 
		{
			/* If the symbol type matches and the key matches, return the node */
			if (valid_symbol_types[i] == head->type && strcmp(key, head->key) == 0) 
			{
				free(valid_symbol_types);
				return head;
			}
		}
	} while ((head = head->next) != NULL);

	/* If the node is not found, free the memory allocated for the valid symbol types and return NULL */
	free(valid_symbol_types);
	return NULL;
}

/*
 * Create an output file for a given symbol type containing all nodes of that type.
 * If no nodes of the given type exist, no file is created.
 * Return false only if cant open file(because then needs to write a message and coninue the program in assemble.c)
 */
bool create_output_file(table_node* head, symbol_type type, char *file_name) 
{
	char* fileName;
	FILE* fp;
	table_node* current = head;
	
	/* Check if there are any nodes with the desired type */
    	while (current != NULL) 
    	{
        	if (current->type == type) 
        	{
            		break;
        	}
        	current = current->next;
    	}
    	if (current == NULL) 
    	{
        /* No nodes with the desired type, do not create output file */
        	return TRUE;
    	}
    	
	/* Determine the output file name based on the symbol type */
  	switch (type) 
  	{
  		case EXTERNAL_REFERENCE:
			fileName = strallocat(file_name, ".ext");
            		break;
        	case ENTRY_SYMBOL:
            		fileName = strallocat(file_name, ".ent");
            		break;
        	default:
            		/* Invalid symbol type, do nothing */
            		return TRUE;
    	}
	
	
    	/* Open the output file for writing */
    	fp = fopen(fileName, "w");
    	if (fp == NULL) 
    	{
		free(fileName);
        	return FALSE;
    	}
    	

    	/* Traverse the list and write matching nodes to the output file */
    	current = head;
    	while (current != NULL) 
    	{
        	if (current->type == type) 
        	{
            		fprintf(fp, "%s %d\n", current->key, current->value);
        	}
        	current = current->next;
    	}

    	/* Close the output file and free filename*/
    	free(fileName);
    	fclose(fp);
    	return TRUE;
}



    








