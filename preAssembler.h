/*
This header file contains declarations for the pre-assembly process in the assembly language compiler. 
It includes utils.h and declarations.h for necessary data structures and function prototypes.
*/

#ifndef _PREASSEMBLER_H
#define _PREASSEMBLER_H

#include "utils.h"
#include "declarations.h"

/*
 * Function to perform pre-assembly process
 *
 * @param ipf A pointer to a FILE structure representing the input file
 * @param fileName A character pointer to the name of the input file
 *
 * @returns A boolean value indicating whether the pre-assembly process was successful or not
 */
bool preAssembler(FILE *ipf, char* fileName);

/*
 * A struct to represent a macro in the pre-assembly process
 *
 * @param name A character array representing the name of the macro
 * @param content A character array representing the content of the macro
 */
typedef struct macro {
    char name[MAX_MCR];
    char content[MAX_MCR];
} macro;

#endif


