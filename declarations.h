#ifndef _DECLERATIONS_H
#define _DECLERATIONS_H

/* We print to stderr for errors*/
#define ERR_OUTPUT_FILE stderr

/* Maximum length of a single source line */
#define MAX_LINE 80

/* Maximum number of macros allowed */
#define MAX_MCR 256

/* Size of the "endmcr" string */
#define MCR_END_SIZE 6

/* Maximum length of a label allowed */
#define MAX_LABLE_LEN 30

/* Initializing IC to be 100 */
#define IC_START_VALUE 100

/* Total number of memory cells */
#define MEMORYSIZE 256

/* Total number of directives that we use in assembly */
#define NUM_OF_DIRECTIVES 4

/* Total number of functions that we use in assembly */
#define NUM_OF_FUNCS 16

/* The range between 14 bits of numbers */
#define SHRT_MIN_14_BITS -8192
#define SHRT_MAX_14_BITS 8192

/* The maximum number of operands for the functions in assembly that we use */
#define MAX_TOKENS 2

/* for function use to take note if its second or first group */
#define FIRSTGROUPTARGET 0
#define FIRSTGROUPSOURCE 1
#define SECONDGROUP 2

/*
 * Macro that moves the given string pointer to the next non-whitespace character
 */
#define MOVE_TO_NOT_WHITE(string, index) \
        for (;string[(index)] && (string[(index)] == '\t' || string[(index)] == ' '); (++(index)))\
        	;

/* Macro for freeing memory allocated for files */
#define FREE_FILES(file1,file2,file3) \
	free(file1); \
	free(file2); \
	free(file3);

/* Boolean type used in the program */
typedef enum booleans {
	FALSE = 0, 
	TRUE = 1
} bool;

/* Struct that keeps the information of the line in the file */
typedef struct line_info {
	/* Line number in file */
	short line_number;
	/* File name */
	char *file_name;
	/* Line content (source) */
	char *content;
} line_info;

/*
	This union represents a line of code, including any associated label and binary code.
	It will be used in step two of the code execution process.
*/
typedef union line_code {

	short code; /* A short integer representing the binary code associated with this line of code.*/

	struct {
    		line_info line; /* Represents a line of code.*/
    		char label[MAX_LABLE_LEN]; /* Represents a label associated with a line of code.*/
    		short code; /* A short integer representing the binary code associated with this line of code.*/
	} code_info;
} line_code;

/* Enumeration for directive types (.data, .entry, etc.) */
typedef enum directive {
	DATA_DIRE,      /* .data directive */
	EXTERN_DIRE,    /* .extern directive */
	ENTRY_DIRE,     /* .entry directive */
	STRING_DIRE,    /* .string directive */
	NONE_DIRE,      /* Not found */
	ERROR_DIRE      /* Parsing/syntax error */
} directive;

/* Enumeration for command opcodes, with NONE_OP for not found */
typedef enum opcodes {
	MOV_OP,
	CMP_OP,
	ADD_OP,
	SUB_OP,
	NOT_OP,
	CLR_OP,
	LEA_OP,
	INC_OP,
   	DEC_OP,
	JMP_OP,
	BNE_OP,
	RED_OP,
  	PRN_OP,
	JSR_OP,
	RTS_OP,
	STOP_OP,

	/* Failed/Error */
	NONE_OP = -1
} opcode;

/* Enumeration for registers - r0->r7 + not found */
typedef enum registers {
	R0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	NONE_REG = -1
} reg;



/** Operand addressing type */
typedef enum addressing_types 
{
	/** Immediate addressing (0) */
	IMMEDIATE_ADDR ,
	/** Direct addressing (1) */
	DIRECT_ADDR ,
	/** Relative addressing (2) */
	RELATIVE_ADDR ,
	/** Register addressing (3)*/
	REGISTER_ADDR ,
	/** Failed/Not found that its an addressing */
	NONE_ADDR = -1
} addressing_type;

/** Operand encoding type */
typedef enum encoding_types 
{
	/** Absolute encoding (0) */
	ABSOLUTE,
	/** External encoding (1) */
	EXTERNAL,
	/** Relocatable encoding (2) */
	RELOCATEBLE


} encoding_types;


#endif














