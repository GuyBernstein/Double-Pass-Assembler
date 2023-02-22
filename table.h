/* Implements a dynamically-allocated symbol table */
#ifndef _TABLE_H
#define _TABLE_H

/** A symbol type */
typedef enum symbol_type {
	CODE_SYMBOL,
	DATA_SYMBOL,
	EXTERNAL_SYMBOL,
	/** Address that contains a reference to (a usage of) external symbol */
	EXTERNAL_REFERENCE,
	ENTRY_SYMBOL
} symbol_type;

/** pointer to table entry is just a table. */
typedef struct entry* table;

/** A single table entry */
typedef struct entry {
	/** Next entry in table */
	table next;
	/** Address of the symbol */
	long value;
	/** Key (symbol name) is a string (aka char*) */
	char *key;
	/** Symbol type */
	symbol_type type;
} table_entry;

/**
 * Adds an item to the table, keeping it sorted.
 */
void add_table_item(table *tab, char *key, long value, symbol_type type);

/**
 * free all the memory required by the table.
 */
void free_table(table tab);

/**
 * Adds the value to add into the value of each entry
 */


table_entry *find_by_types(table tab,char *key, int symbol_count, ...);

#endif
