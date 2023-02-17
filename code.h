/* Helper functions to process and analyze code */
#ifndef _CODE_H
#define _CODE_H

#include "declarations.h"

/**
 * Detects the opcode and the funct of a command by it's name
 * @param cmd The command name (string)
 * @param opcode_out The opcode value destination
 * @param funct_out The funct value destination
 */
void get_opcode_func(char* cmd, opcode *opcode_out, funct *funct_out);

/**
 * Returns the register enum value by it's name
 * @param name The name of the register
 * @return The enum value of the register if found. otherwise, returns NONE_REG
 */
reg get_register_by_name(char *name);


#endif
