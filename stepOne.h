/*
This header file contains function declarations for the first pass of the assembly language compiler.
It includes declarations.h and table.h for necessary data structures and function prototypes.
*/

#ifndef _STEPONE_H
#define _STEPONE_H

#include "declarations.h"
#include "table.h"

/*
 * Function to perform the first pass of the assembly language compilation process
 *
 * @param line A struct containing the line information to be processed
 * @param machineCommands A pointer to an array of line_code structs that will be populated with the machine code generated from the input assembly code
 * @param machineData A pointer to an array of shorts that will be populated with the machine data generated from the input assembly code
 * @param ic A pointer to an integer representing the current instruction counter
 * @param dc A pointer to an integer representing the current data counter
 * @param symbol_table A pointer to a table struct that will be populated with symbols found in the input assembly code
 *
 * @returns A boolean value indicating whether the first pass of the assembly language compilation process was successful or not
 */
bool stepOne(line_info line, line_code* machineCommands, short* machineData, short *ic, short *dc, table *symbol_table);

/*
 * Function to process commands during the first pass of the assembly language compilation process
 *
 * @param line A struct containing the line information to be processed
 * @param i An integer representing the current index while processing the command
 * @param ic A pointer to an integer representing the current instruction counter
 * @param machineCommands A pointer to an array of line_code structs that will be populated with the machine code generated from the input assembly code
 *
 * @returns A boolean value indicating whether the command was processed successfully or not
 */
bool process_commands(line_info line, int i, short *ic, line_code* machineCommands);

#endif


