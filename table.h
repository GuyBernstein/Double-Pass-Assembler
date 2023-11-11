/* Implements a dynamically-allocated symbol table */

#ifndef _TABLE_H
#define _TABLE_H

#include "declarations.h"

/** A symbol type */
typedef enum symbol_type {
    CODE_SYMBOL,        /* Symbol contains code */
    DATA_SYMBOL,        /* Symbol contains data */
    EXTERNAL_SYMBOL,    /* Symbol is external */
    EXTERNAL_REFERENCE, /* Symbol is a reference to an external symbol */
    ENTRY_SYMBOL        /* Symbol is an entry point */
} symbol_type;

/** pointer to table node is just a table. */
typedef struct node* table;

/** A single table node */
typedef struct node 
{
    table next;     /* Next node in table */
    short value;    /* Address of the symbol */
    char *key;      /* Key (symbol name) is a string (aka char*) */
    symbol_type type;   /* Symbol type */
} table_node;

/**
 * Print the contents of the symbol table.
 * @param tab Pointer to the symbol table.
 */
void print_table(table tab);

/**
 * Add an item to the symbol table.
 * @param tab Pointer to the symbol table.
 * @param key The key (symbol name) for the new item.
 * @param value The value (address) for the new item.
 * @param type The type of the new item.
 */
void add_table_item(table *tab, char *key, short value, symbol_type type);

/**
 * Free all the memory used by the symbol table.
 * @param tab Pointer to the symbol table.
 */
void free_table(table tab);

/**
 * Find a node in the symbol table by key and type.
 * @param tab Pointer to the symbol table.
 * @param key The key (symbol name) to search for.
 * @param symbol_count The number of symbol types to search for.
 * @param ... A variable number of arguments of type symbol_type to search for.
 * @return Pointer to the found node or NULL if not found.
 */
table_node *find_by_types(table tab,char *key, int symbol_count, ...);

/**
 * Add a value to the value field of each node of a specific symbol type.
 * @param tab Pointer to the symbol table.
 * @param to_add The value to add to each node of the specified type.
 * @param type The symbol type to modify.
 */
void add_value_to_type(table tab, short to_add, symbol_type type);

/**
 * Create an output file with a list of symbols of a specific type.
 * @param head Pointer to the first node in the symbol table.
 * @param type The type of symbols to include in the output file.
 * @param file_name The name of the output file to create.
 * @return True if the output file was successfully created, false otherwise.
 */
bool create_output_file(table_node* head, symbol_type type, char *file_name);

#endif
