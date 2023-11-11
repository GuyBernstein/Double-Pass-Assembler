/*
This header file contains function declarations for various utility functions used in the assembly language compiler.
It includes declarations.h for necessary data structures and function prototypes.
*/


#ifndef _UTILS_H
#define _UTILS_H

#include "declarations.h"





/*
 * Function to find a directive enum value by name
 *
 * @param name A character pointer to the name of the directive to find
 *
 * @returns A directive enum value indicating the type of directive found
 */
directive find_directive_by_name(char *name);

/*
 * Function to check if a label name is valid
 *
 * @param name A character pointer to the name of the label to check
 *
 * @returns A boolean value indicating whether the label name is valid or not
 */
bool is_valid_label_name(char *name);

/*
 * Function to check if a given name is a reserved word
 *
 * @param name A character pointer to the name to check
 *
 * @returns A boolean value indicating whether the given name is a reserved word or not
 */
bool is_reserved_word(char *name);

/*
 * Function to check if a given string is alphanumeric
 *
 * @param string A character pointer to the string to check
 *
 * @returns A boolean value indicating whether the given string is alphanumeric or not
 */
bool is_alphanumeric_str(char *string);

/*
 * Function to print an error message for a given line
 *
 * @param line A struct containing the line information for which the error message is being printed
 * @param message A character pointer to the error message to be printed
 *
 * @returns An integer value indicating the number of characters printed
 */
int printf_line_error(line_info line, char *message, ...);

/*
 * Function to concatenate two strings and allocate memory for the result
 *
 * @param s0 A character pointer to the first string to be concatenated
 * @param s1 A character pointer to the second string to be concatenated
 *
 * @returns A character pointer to the result of the concatenation
 */
char *strallocat(char *s0, char* s1);

/*
 * Function to allocate memory with error checking
 *
 * @param size An integer representing the size of memory to be allocated
 *
 * @returns A pointer to the allocated memory
 */
void *malloc_with_check(short size);

/*
 * Function to check if a given line contains a label
 *
 * @param line A struct containing the line information to be checked
 * @param symbol_dest A character pointer to the destination buffer for the label, if found
 *
 * @returns A boolean value indicating whether the line contains a label or not
 */
bool isLabel(line_info line, char *symbol_dest);

/*
 * Function to remove spaces from a string
 *
 * @param str A character pointer to the string from which spaces are to be removed
 */
void removeSpaces(char *str);

/*
 * Function to skip spaces and tabs in a string
 *
 * @param s A character pointer to the string in which spaces and tabs are to be skipped
 *
 * @returns An integer representing the number of characters skipped
 */
int skipSpacesAndTabs(char *s);

/*
 * Functions to process different groups of commands
 *
 * @param line A struct containing the line information to be processed
 * @param opcode An integer representing the opcode for the current command
 * @param linePtr A character pointer to the current position in the line to be processed
 * @param ic A pointer to an integer representing the current instruction counter
 * @param machineCommands A pointer to an array of line_code unions that will be populated with the machine code generated from the input assembly code
 * @param command A character pointer to the name of the current command being processed
 *
 * @returns A boolean value indicating whether the current command was processed successfully or not
 */
bool firstGroup(line_info line,int opcode,char* linePtr, short *ic, line_code* machineCommands,char *command);
bool secondGroup(line_info line,int opcode,char* linePtr, short *ic, line_code* machineCommands, char *command);
bool thirdGroup(line_info line,int opcode,char* linePtr, short *ic,line_code* machineCommands, char *command);

/*
 * Function to generate a word in the machine code from the given parameters
 * @param A_R_E An integer representing the A_R_E field of the word
 * @param target An integer representing the target register field of the word
 * @param source An integer representing the source register field of the word
 * @param opcode An integer representing the opcode field of the word
 * @param targetParm An integer representing the target parameter field of the word
 * @param sourceParm An integer representing the source parameter field of the word
 * @param ic A pointer to an integer representing the current instruction counter
 * @param machineCommands A pointer to an array of line_code unions that will be populated with the machine code generated from the input assembly code
 */
void make_word(int A_R_E,int target,int source,int opcode,int targetParm,int sourceParm,short *ic,line_code* machineCommands);

/*
 * Function to save a label found in the input assembly code
 * @param line A struct containing the line information where the label was found
 * @param label A character pointer to the label to be saved
 * @param ic A pointer to an integer representing the current instruction counter
 * @param machineCommands A pointer to an array of line_code unions that will be populated with the machine code generated from the input assembly code
 */
void save_label(line_info line,char* label,short *ic,line_code* machineCommands);

/*
 * Function to check if a jump command has parameters
 * @param line A struct containing the line information to be checked
 * @param opcode An integer representing the opcode for the current command
 * @param linePtr A character pointer to the current position in the line to be processed
 * @param ic A pointer to an integer representing the current instruction counter
 * @param machineCommands A pointer to an array of line_code unions that will be populated with the machine code generated from the input assembly code
 * @returns A boolean value indicating whether the jump command has parameters or not
 */
bool check_if_jump_with_parameters(line_info line,int opcode,char* linePtr,short *ic,line_code* machineCommands);

/*
 * Function to check if an operand is a number and set a flag and value accordingly
 * @param line A struct containing the line information to be checked
 * @param operand A character pointer to the operand to be checked
 * @param flag A pointer to an integer that will be set to 1 if the operand is a number, and 0 otherwise
 * @param value A pointer to an integer that will be set to the value of the operand if it is a number
 */
void check_if_number(line_info line,char* operand,int *flag, int *value);

/*
 * Function to convert the machine code from binary to dots for output to a file
 * @param machineCommands A pointer to an array of line_code unions containing the machine code generated from the input assembly code
 * @param machineData A pointer to an array of shorts containing the machine data generated from the input assembly code
 * @param ic A pointer to an integer representing the current instruction counter
 * @param dc A pointer to an integer representing the current data counter
 * @param output A pointer to the file where the machine code in dots will be written
 */
void binaryToDots(line_code* machineCommands,short* machineData,short *ic,short *dc, FILE *output);

/*
 * Function to get the opcode for a given command
 * @param cmd A character pointer to the command for which the opcode is to be retrieved
 * @param opcode_out A pointer to an opcode enum value that will be set to the opcode of the given command
 */
void get_opcode(char *cmd, opcode *opcode_out);

/*
 * Function to get the register enum value by name
 * @param name A character pointer to the name of the register to be retrieved
 * @returns A reg enum value representing the register with the given name
 */
reg get_register_by_name(char *name);

/*
 * Function to check if a given operand is valid for a given command
 * @param line A struct containing the line information to be checked
 * @param command A character pointer to the command for which the operand is being checked
 * @param targetOp A character pointer to the target operand being checked
 * @param opcode An integer representing the opcode for the current command
 * @param targetdAddress A pointer to an integer that will be set to the addressing mode of the target operand
 * @param targetValue A pointer to an integer that will be set to the value of the target operand, if it is a number
 * @param whichGroup An integer representing the current group of commands being processed
 * @returns A boolean value indicating whether the operand is valid or not
 */
bool check_operand_validity(line_info line, char* command, char* targetOp, int opcode, int* targetdAddress, int* targetValue, int whichGroup);






#endif



