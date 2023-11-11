/*
This header file contains function declarations for finding and processing directives in assembly language code.
It includes declarations.h which contains necessary data structures and function prototypes.
*/

#ifndef _DIRECTIVE_H
#define _DIRECTIVE_H

#include "declarations.h"

/*
 * Function to find directive from index
 * 
 * @param line A struct containing the line information, including the directive to be searched
 * @param index A pointer to an integer that is used to keep track of the current index while searching
 *
 * @returns A directive enum value indicating the type of directive found
 */
directive find_directive_from_index(line_info line, int *index);

/*
 * Function to check valid data
 *
 * @param line A struct containing the line information, including the data to be checked
 * @param data A character pointer to the data string to be checked
 * @param numbers A pointer to an array of shorts that will be populated with the numbers in the data string
 *
 * @returns An integer value indicating whether the data string is valid or not (0 = invalid, 1 = valid)
 */
int checkValidData(line_info line, char *data,short* numbers);

/*
 * Function to process string instruction
 *
 * @param line A struct containing the line information, including the string to be processed
 * @param index An integer representing the current index while processing the string
 * @param data A pointer to an array of shorts that will be populated with the string's ASCII values
 * @param dc A pointer to an integer representing the current data counter
 *
 * @returns A boolean value indicating whether the string was processed successfully or not
 */
bool process_string_instruction(line_info line, int index, short *data, short *dc);

/*
 * Function to check valid string
 *
 * @param line A struct containing the line information, including the string to be checked
 * @param string A character pointer to the string to be checked
 * @param str A pointer to an array of characters that will be populated with the checked string
 *
 * @returns An integer value indicating whether the string is valid or not (0 = invalid, 1 = valid)
 */
int checkValidString(line_info line, char *string,char *str);

/*
 * Function to insert data to array
 *
 * @param input A pointer to an array of shorts containing the input data to be inserted
 * @param output A pointer to an array of shorts that will be populated with the input data
 * @param dc A pointer to an integer representing the current data counter
 * @param count An integer representing the number of shorts to be inserted
 *
 * @returns void
 */
void insertDataToArray(short* input, short* output,short *dc, int count);

/*
 * Function to insert string to array
 *
 * @param input A character pointer to the string to be inserted
 * @param output A pointer to an array of shorts that will be populated with the string's ASCII values
 * @param dc A pointer to an integer representing the current data counter
 *
 * @returns void
 */
void insertStringToArray(char* input, short* output,short *dc);

#endif


