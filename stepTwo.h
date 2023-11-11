/*
This header file contains function declarations for the second pass of the assembly language compiler.
It includes declarations.h and table.h for necessary data structures and function prototypes.
*/

#ifndef _SECOND_PASS_H
#define _SECOND_PASS_H

#include "declarations.h"
#include "table.h"

/*
 * Function to perform the second pass of the assembly language compilation process
 *
 * @param line A struct containing the line information to be processed
 * @param symbol_table A pointer to a table struct containing symbols found in the input assembly code
 *
 * @returns A boolean value indicating whether the second pass of the assembly language compilation process was successful or not
 */
bool stepTwo(line_info line, table *symbol_table);

/*
 * Function to process operands during the second pass of the assembly language compilation process
 *
 * @param line A struct containing the line information to be processed
 * @param ic An integer representing the current instruction counter
 * @param machineCommands A pointer to an array of line_code structs containing the machine code generated from the input assembly code
 * @param symbol_table A pointer to a table struct containing symbols found in the input assembly code
 *
 * @returns A boolean value indicating whether the operand was processed successfully or not
 */
bool process_spass_operand(line_info line,short ic,line_code* machineCommands,table *symbol_table);

#endif


