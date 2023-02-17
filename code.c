#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include "code.h"
#include "utils.h"




/**
 * A single lookup table element
 */
struct cmd_lookup_element 
{
	char *cmd;
	opcode op;
	funct fun;
};


/**
 * A lookup table for opcode & funct by command name
 */
static struct cmd_lookup_element lookup_table[] = 
{
		{"mov", MOV_OP, NONE_FUNCT},
		{"cmp",CMP_OP, NONE_FUNCT},
		{"add",ADD_OP, ADD_FUNCT},
		{"sub",SUB_OP, SUB_FUNCT},
		{"lea",LEA_OP, NONE_FUNCT},
		{"clr",CLR_OP, CLR_FUNCT},
		{"not",NOT_OP, NOT_FUNCT},
		{"inc",INC_OP, INC_FUNCT},
		{"dec",DEC_OP, DEC_FUNCT},
		{"jmp",JMP_OP, JMP_FUNCT},
		{"bne",BNE_OP, BNE_FUNCT},
		{"jsr",JSR_OP, JSR_FUNCT},
		{"red",RED_OP, NONE_FUNCT},
		{"prn",PRN_OP, NONE_FUNCT},
		{"rts",RTS_OP, NONE_FUNCT},
		{"stop",STOP_OP, NONE_FUNCT},
		{NULL, NONE_OP, NONE_FUNCT}
};


reg get_register_by_name(char *name) 
{
	if (name[0] == 'r' && isdigit(name[1]) && name[2] == '\0') 
	{
		int digit = name[1] - '0'; /* convert digit ascii char to actual single digit */
		if (digit >= R0 && digit <= R7) 
			return digit;
	}
	return NONE_REG; /* No match */
}

void get_opcode_func(char *cmd, opcode *opcode_out, funct *funct_out) 
{
	struct cmd_lookup_element *e;
	*opcode_out = NONE_OP;
	*funct_out = NONE_FUNCT;
	/* iterate through the lookup table, if commands are same return the opcode of found. */
	for (e = lookup_table; e->cmd != NULL; e++) 
	{
		if (!strcmp(e->cmd, cmd) ) 
		{
			*opcode_out = e->op;
			*funct_out = e->fun;
			return;
		}
	}
}














