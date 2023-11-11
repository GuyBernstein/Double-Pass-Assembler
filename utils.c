#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>


#include "utils.h"


/* This function concatenates two strings and returns a newly allocated string with the result. */
char *strallocat(char *s0, char* s1)
{
	/* Allocate memory for the result string */
	char *str = (char *)malloc_with_check(strlen(s0) + strlen(s1) + 1);
	
	/* Copy the first string into the result string */
	strcpy(str, s0);
	
	/* Concatenate the second string onto the result string */
	strcat(str, s1);
	
	/* Return the result string */
	return str;
}

/* This function allocates memory with error checking. If allocation fails, it prints an error message and exits. */
void *malloc_with_check(short size) 
{
	/* Allocate memory */
	void *ptr = malloc(size);
	
	/* If allocation fails, print an error message and exit the program */
	if (ptr == NULL) 
	{
		printf("Error: Fatal: Memory allocation failed.");
		exit(1);
	}
	
	/* Return the allocated memory */
	return ptr;
}

/* This function prints an error message with a line number and file name, and returns the number of characters printed. */
int printf_line_error(line_info line, char *message, ...) 
{ 
	int result;  /* Number of characters printed */
	va_list args; /* Variable arguments list */
	
	/* Print file name and line number */
	fprintf(ERR_OUTPUT_FILE,"Error In %s:%d: ", line.file_name, line.line_number);

	/* use vprintf to call printf from variable argument function (from stdio.h) with message + format */
	va_start(args, message);
	result = vfprintf(ERR_OUTPUT_FILE, message, args);
	va_end(args);

	fprintf(ERR_OUTPUT_FILE, "\n");
	/* Return the number of characters printed */
	return result;
}

/* This function receives a line and a string pointer, preforms checks on the first word of the given line, and returns the label name.
 * If the label is invalid, it prints an error message and returns NULL. */
bool isLabel(line_info line,char *label)
{
	
	
	
	char *colon;/*a pointer to the colon occurrence in the line*/
	
	/* Try to read a word from the line into a label string */
	if(sscanf(line.content,"%s",label) == 1)
	{
		
		/* If it was an attempt to define a label, perform further checks */
		if ((colon = strchr(label,':')) )
		{/*found colon*/
		
			

			/*check if something is after the colon*/
			if(strcmp(colon,":"))
			{/*found that the label isnt over with ':' */
				printf_line_error(line,
			        	"Invalid label name - needs a space after ':' in the the lable: %s", label);
				return FALSE;
			}
			colon[0] = '\0';/* Remove the ':' from the label to check for validity */
			
			/* Check if the label is longer than the maximum allowed length */
			if(strlen(label) > MAX_LABLE_LEN)
			{
				printf_line_error(line,
					"Invalid label name - cannot be shorter than 30 chars in the label: %s", label);
				return FALSE;
			}
			
			/* Check if the label starts with a letter */
			if(!isalpha(label[0]))
			{
				printf_line_error(line,
					"Invalid label name - may only start with a letter in the label: %s", label);
				return FALSE;
			}
			
			/* Check if the label contains only letters or numbers */
			if(!is_alphanumeric_str(label+1))/*plus one because we want have checked already the first char*/
			{
				printf_line_error(line,
					"Invalid label name - may only be with letters or numbers in the label: %s", label);
				return FALSE;
			}
			
			/* Check if the label is a reserved word */
			if(is_reserved_word(label))
			{
				printf_line_error(line,
					"Invalid label name - may not be a reserved word, in the the lable: %s", label);
				return FALSE;
			}
			
			
			return TRUE; /* The label is valid */
		}
		
		label[0] = '\0';
		return TRUE; /* There was no attempt to define a label */
		
		
		
			
	}
	return FALSE; /* Could not read a string */
	
}


/* This function checks if a given string is a valid label name.

 * It checks the length, first character is a letter, and the rest of the characters are alphanumeric,
 * and it's not a reserved word.
 * If all these conditions are satisfied, it returns TRUE; otherwise, it returns FALSE.
 */
bool is_valid_label_name(char *name) 
{
	
	return name[0] && strlen(name) <= MAX_LABLE_LEN && isalpha(name[0]) && is_alphanumeric_str(name+1)  &&
	       !is_reserved_word(name);
	      
}

/* This function checks if a given string is a reserved word.
 * It returns TRUE if the given string is a command or register, 
 * otherwise returns FALSE.*/
bool is_reserved_word(char *name) 
{
	int opc;
	/* Check if the given string is a command, register, or directive. */
	get_opcode(name, &opc);
	if (opc != NONE_OP || get_register_by_name(name) != NONE_REG || find_directive_by_name(name) != NONE_DIRE)
		return TRUE;

	return FALSE;
}
/* This function checks if all characters in a given string are alphanumeric.
 * If it contains a non-alphanumeric character, it returns FALSE;
 * otherwise, it returns TRUE.
*/
bool is_alphanumeric_str(char *string) 
{
	int i;
	/* Check for every character in the string if it's a non-alphanumeric character. If it's a non-alphanumeric character, return FALSE. */
	for (i = 0; string[i]; i++) 
		if (!isalpha(string[i]) && !isdigit(string[i])) 
			return FALSE;
	
	return TRUE;
}

/* This function finds a directive in the table of directives.
 * If the given string is a directive name, it returns the
 * corresponding directive enum; otherwise, it returns NONE_DIRE.
*/
directive find_directive_by_name(char *name) 
{
	int i;
	/* Store all the directives in a 2D array of characters. */
	char *directives[] = {
        "data",
        "extern",
        "entry",
        "string"
    	};
	/* Check each element in the array of directives. If the given string is a directive name, return the corresponding directive enum. */
	for (i = 0;i < NUM_OF_DIRECTIVES; i++)
	{
		
		if (!strcmp(directives[i], name) ) /*found a directive match*/
			return i;/*return the directive enum*/
	}
	
	return NONE_DIRE;/*didnt found a directive in the table of the directives*/
}

/*

 * This function receives a string pointer
 * and returns the number of consecutive spaces and tabs
 * at the beginning of the string
*/
int skipSpacesAndTabs(char *s) 
{
	int n=0;
	while(isspace(s[n]))/*check for space and tabs*/
		n++;/*increment the number of consecutive spaces and tabs*/
	return n;
}



/*
 * This function receives a string pointer
 * and removes all the spaces, tabs and new line characters from it.
*/
void removeSpaces(char *str) 
{
	int i;
	/* To keep track of non-space character count */
	int count = 0;
    
	/* Traverse the given string. If current character 
	 * is not space, then place it at index 'count++' */
	for (i = 0; str[i]; i++) 
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			str[count++] = str[i]; /* here count is incremented */
	}
    
	str[count] = '\0'; /* finish the string */
}



/**
 * This function processes the first group of instructions.
 * It parses the source and target operands, checks their validity,
 * and creates the command and extra words accordingly.
 */
bool firstGroup(line_info line,int opcode, char* linePtr, short *ic,line_code* machineCommands,char *command) 
{
    	char sourceOp[MAX_LINE] = {'\0'}; /* The source operand */
	char targetOp[MAX_LINE] = {'\0'};/* The target operand */

	bool result = TRUE;/* Result of the validity check */
	
	int sourceValue=0;/* The value of the source operand */
	int targetValue=0;/* The value of the target operand */

	addressing_type sourceAddress=IMMEDIATE_ADDR;/* The addressing type of the source operand */
	addressing_type targetdAddress=IMMEDIATE_ADDR;/* The addressing type of the target operand */
	char *token;
	char *delim = " ,\t\n";
        int operand_count = 0;
	char temp_line[MAX_LINE];
	/* Copy the rest of the line (command content) to temp_line */
	strcpy(temp_line,linePtr);
        token = strtok(temp_line, delim);

        while (token != NULL) 
        {
            	operand_count++;
            	token = strtok(NULL, delim);
        }

        if (operand_count != 2) 
        {
        	printf_line_error(line,"Invalid - needed 2 operands that is seperated by a ',' for this command: %s", command);
        	return FALSE;
        } 
	
	removeSpaces(linePtr);/*remove the spaces for a check for validness*/
	/*deal with errors and print a proper message*/
	if(linePtr[0] == ',' || linePtr[strlen(linePtr)-1] == ',')
	{
		printf_line_error(line, "Unexpected comma after command, we got: (%s)",linePtr);
		return FALSE;
	}	
	if( linePtr[0] == '\0' || linePtr[0] == EOF)
	{/*got no operand for this command*/
		printf_line_error(line, "no operands for this command is Invalid: %s",command);
		return FALSE;
	}	
	if(!strchr(linePtr,',') )
	{/*there is no ',' after the command*/
		printf_line_error(line, "Invalid - needed 2 operands that is seperated by a ',' for this command: %s", command);
		return FALSE;
	}	
	if(strstr(linePtr, ",,"))
	{/*there is a ',,' after the command*/
		printf_line_error(line, "consequtive commas are invalid. we got: (%s)",linePtr);
		return FALSE;
	}	
	
	
	/* Getting the first and second operands */
    	if(sscanf(linePtr, "%[^,],%s",sourceOp,targetOp) == 2)/*we know now that there is 2 operands, seperated by ',' */
    	{
    		if(strchr(targetOp,',') )
    		{
      			printf_line_error(line, "Invalid - got more than two operands for this command: %s", command);
      			return FALSE;
      		}
      		
    	} 
    	
	
	if((sourceValue = get_register_by_name(sourceOp)) != NONE_REG)
	{
		if(opcode == LEA_OP)
		{
			printf_line_error(line, "This Command source cannot be register: %s", command);
			return FALSE;
		}
		sourceAddress = REGISTER_ADDR;
	}

	else
	{
		result = check_operand_validity(line, command, sourceOp, opcode, &sourceAddress, &sourceValue,FIRSTGROUPSOURCE);
		if (!result) 
		{
		    	return FALSE;
		}
	}	


	/** Checking Target
	 * Check if Operand is register */
	if((targetValue=get_register_by_name(targetOp)) != NONE_REG)
	{
		targetdAddress = REGISTER_ADDR;
	}
	else
	{
		result = check_operand_validity(line, command, targetOp, opcode, &targetdAddress, &targetValue,FIRSTGROUPTARGET);
		if (!result) 
		{
		    	return FALSE;
		}
		
	}

	/* This case is for jump with parameters */
	if(opcode == JMP_OP || opcode == BNE_OP || opcode == JSR_OP)
	{
		make_word(0,RELATIVE_ADDR,0,opcode,targetdAddress,sourceAddress,ic,machineCommands);
		(*ic)++; /*skipping label, already saved before*/
	}
	else
	{/* Command word of first group*/ 
		make_word(0,targetdAddress,sourceAddress,opcode,0,0,ic,machineCommands);
	}
	
	/* Making extra commands*/
	/*If we have 2 registers */
	if(sourceAddress == REGISTER_ADDR && targetdAddress == REGISTER_ADDR)
	{
		/* Putting both registers in the same line */
		machineCommands[(*ic)-IC_START_VALUE].code  |= (sourceValue<<8 | targetValue<<2);
		(*ic)++;
	}
	/*Making Source extra command*/
	else
	{
		if(sourceAddress == REGISTER_ADDR)
		{/* Register */
			machineCommands[(*ic)-IC_START_VALUE].code  |= sourceValue<<8;
			(*ic)++;
		}
		else if(sourceAddress == IMMEDIATE_ADDR)/* Number */
			make_word(0,sourceValue,0,0,0,0,ic,machineCommands);
		else 
			save_label(line, sourceOp,ic,machineCommands);/* Label skipping will be filled after stepTwo */

		/* Making Target extra command*/
		if(targetdAddress == REGISTER_ADDR || targetdAddress == IMMEDIATE_ADDR)/* Register or Number */
			make_word(0,targetValue,0,0,0,0,ic,machineCommands);
		else 
			save_label(line,targetOp,ic,machineCommands);/* Label skipping will be filled in stepTwo */

	}
	return TRUE;

}

/* This function processes the second group of instructions.
 * It parses the target operand, checks its validity,
 * and creates the command and extra words accordingly.
 */
bool secondGroup(line_info line,int opcode,char* linePtr, short *ic,line_code* machineCommands, char *command) 
{

	char endptr[MAX_LINE];/* A temporary buffer used by sscanf. */
	char targetOp[MAX_LINE];/* The target operand. */
	int j;/* The return value of sscanf. */
	bool result = TRUE; /* A boolean variable for storing the result of check_operand_validity function*/
	int targetValue = 0;  /* The value of the target operand. */
	addressing_type targetdAddress = IMMEDIATE_ADDR;/* The addressing type of the target operand, initialized to immediate addressing. */
	
	/* Skip spaces at the beginning */
	linePtr += skipSpacesAndTabs(linePtr);
	
	/* Check for errors and print a proper message */
	if( linePtr[0] == '\0' || linePtr[0] == EOF)
	{/*got no operand for this command*/
		printf_line_error(line, "no operands for this command is Invalid: %s",command);
		return FALSE;
	}	

	/* Getting the target operand */
    	if((j = sscanf(linePtr, "%s %s",targetOp,endptr)) == 2)
    	{
		if(!strchr(targetOp,'('))
		{/*havent found a try to define a function in the operand*/
			printf_line_error(line, "Invalid - got more than one operand for this command: %s", command);
			return FALSE;
		}
		/*there is an opening brackets, but 2 operand successfully red*/ 
		printf_line_error(line, "Invalid - there should be no space inside the brackets for this command: %s", command);
		return FALSE;
	}
	if((j == 1) && strchr(targetOp,',') && (!strchr(targetOp,'(')) )
	{/*there is an operand with ',' after the command*/
		printf_line_error(line, "Invalid - got more than one operand for this command: %s", command);
		return FALSE;
	}	

	/* Checking Target */
	/* Check if Operand is register */
	if(opcode == JMP_OP || opcode == BNE_OP || opcode == JSR_OP)
	{
		return check_if_jump_with_parameters(line,opcode,targetOp,ic,machineCommands);
	}
	
	if((targetValue=get_register_by_name(targetOp))!= NONE_REG)
	{
		targetdAddress = REGISTER_ADDR;
	}
		
	else
	{
		result = check_operand_validity(line, command, targetOp, opcode, &targetdAddress, &targetValue,SECONDGROUP);
		if (!result) 
		{
		    	return FALSE;
		}
	}
	/* Making Command for the second group*/ 
	make_word(0,targetdAddress,0,opcode,0,0,ic,machineCommands);
	/*Making extra command*/
	if(targetdAddress == REGISTER_ADDR || targetdAddress == IMMEDIATE_ADDR)/* Register or Number */
		make_word(0,targetValue,0,0,0,0,ic,machineCommands);
	else 
		save_label(line,targetOp,ic,machineCommands);/* Label skipping will be filled in stepTwo */

	return TRUE;
}
/**
 * Processes third group commands that do not have operands.
 * Checks that there are no operands, then puts the opcode in the array.
 * Returns TRUE if successful, FALSE otherwise.
 */
bool thirdGroup(line_info line,int opcode,char* linePtr, short *ic,line_code* machineCommands, char *command) 
{
	/* Skip any whitespace characters at the beginning of the line */
	linePtr+=skipSpacesAndTabs(linePtr);
	
	/* Check that the line has no operands */
	if(*linePtr != '\0')
	{
		printf_line_error(line, "Command cannot recive operands: %s", command);
      		return FALSE;
    	} 
	/* Putting the opcode in the array */ 
 	make_word(0,0,0,opcode,0,0,ic,machineCommands);
	return TRUE;
}

/**
 * Checks if the operand is a number (starts with '#').
 * If it is a valid number, sets the flag to 1 and the value to the number.
 * If it is not a valid number, sets the flag to -1 and returns.
 * If the operand does not start with '#', does nothing and returns.
 */
void check_if_number(line_info line,char* operand,int* flag,int* value)
{
  	short number;/*a short integer variable to hold the integer value of the operand, if it is a number.*/
  	char *endptr;/*  a pointer to a character, which is used by strtol() function
  			* to store the address of the first invalid character in the input string.*/
  	char *token;/* a pointer to a character, which points to the first character after the '#' symbol in the operand string.*/
  	
  	/* Check if the operand contains a '#' character */
  	if((token = strchr(operand,'#')) != NULL)
  	{/*found '#'*/
  		
		*flag = 1; 
		operand+=skipSpacesAndTabs(operand);/*skip white chars at the begginings*/
		/* Check if the # is at the beggining and afterwards a valid number*/
		if(operand[0] != '#' || (!isdigit(operand[1]) && operand[1] != '-' && operand[1] != '+'))
		{
			printf_line_error(line,"invalid - a number should start with '#'",endptr);
			*flag = -1;
			return;/*not a valid number*/
		}

		token++;
		/* Check if the token is an integer */
		number = strtol(token, &endptr, 10);
		endptr+=skipSpacesAndTabs(endptr);
		if (*endptr != '\0') {	
			printf_line_error(line,"(%s) not an integer\n",endptr);
			*flag = -1;
			return;
		}
		/* Check if the number is short  */
		if (number < SHRT_MIN_14_BITS || number > SHRT_MAX_14_BITS ) {
			printf_line_error(line,"%d value out of range\n",number);
			*flag = -1;
			return;
		}  
		
		/* Store the number in the value variable */
		*value = (int)number;
	}
}

/*
 * This function is used to create a single 14-bit word out of the given parameters.
 * The word is constructed according to the following format:
 * bits 0-1: A_R_E (addressing type)
 * bits 2-3: target address mode/address
 * bits 4-5: source address mode/address
 * bits 6-9: opcode
 * bits 10-11: target address mode/address in address mode 2
 * bits 12-13: source address mode/address in address mode 2
 
 * This function modifies the machineCommands array by creating a new word according to the provided parameters.
 * The new word is added to the end of the array and the instruction counter is incremented by 1.
 */
void make_word(int A_R_E,int target,int source,int opcode,int targetParm,int sourceParm,short *ic,line_code* machineCommands) 
{	
	/* bitwise OR the A_R_E, target, source, opcode, sourceParm, and targetParm fields to construct the word */
	machineCommands[(*ic)-IC_START_VALUE].code   |= A_R_E;
	machineCommands[(*ic)-IC_START_VALUE].code   |= target<<2;
	machineCommands[(*ic)-IC_START_VALUE].code   |= source<<4;
	machineCommands[(*ic)-IC_START_VALUE].code   |= opcode<<6;
	machineCommands[(*ic)-IC_START_VALUE].code   |= sourceParm<<12; 
	machineCommands[(*ic)-IC_START_VALUE].code   |= targetParm<<10; 
	/* increment the instruction counter */
	(*ic)++;
}

/* 
	This function saves a label and its corresponding location in memory.
	The label name and the location in memory are stored in the machineCommands
	array, which contains information about the assembled code.
*/
void save_label(line_info line, char* label, short *ic, line_code* machineCommands) 
{
	/* Calculate the index of the current instruction in the machineCommands array */
	short index = (*ic) - IC_START_VALUE;

	/* Save the label name and its location in memory */
	strcpy(machineCommands[index].code_info.label, label);

	/* Save the line_info struct for the current instruction in the machineCommands array */
	machineCommands[index].code_info.line = line;
    
	/* Initialize the code_info.code field to 0 */
  	machineCommands[index].code_info.code = 0;  

	/* Increment the instruction counter */
	(*ic)++;
}

/*
 * This function checks if a line that has an addressing mode 2 of a jump command has parameters.
 */
bool check_if_jump_with_parameters(line_info line,int opcode,char* linePtr,short *ic,line_code* machineCommands)
{
	/* The label variable will hold the label string extracted from the command line. */
	char *label;
	
	/* The endptr variable will hold a pointer to the first character in the input string that is not part of the number. */
	char *endptr;
	
	/* The ampersand variable will hold a pointer to the first occurrence of the '&' character in the command line. */
	char *ampersand;
	
	/* Extract the label from the command line. If there is an '&' character before the label, skip it. */
	label = strtok(linePtr,"(");
	if((ampersand = strchr(label, '&')))/*if there is a & before the label*/
	{
		ampersand += 1;
		label = ampersand;
	}
	
	/* Check if the label name is valid. If not, print an error message and return false. */
	if(!is_valid_label_name(label))
	{
		printf_line_error(line, "Invalid - should be a valid label name: %s ",label);
		return FALSE; /* Error occurd*/
	}

	/* If there are parameters after the label, extract them. */
	if((linePtr = strtok(NULL,")")) != NULL)
	{
		/* If there is extraneous text after the parameters, print an error message and return false. */
		if((endptr = strtok(NULL,"")) != NULL)
		{
			endptr+=skipSpacesAndTabs(endptr);
			if(!isspace(*endptr))
			{
				printf_line_error(line, "Invalid input extraneous text: got %s", endptr);
				return FALSE;
			}
		}
		/* Increment the instruction counter to skip the jump command, and save the label. */
		(*ic)++; 
		save_label(line,label,ic,machineCommands);/* Label skipping will be filled in stepTwo */
		
		/* Decrement the instruction counter to return to the jump command line, and process the parameters. */
		(*ic)-=2; 
		firstGroup(line,opcode,linePtr,ic,machineCommands,label);
	}
	else
	{
		/* If there are no parameters, create a new word with the opcode and addressing mode, and save the label. */
		make_word(0,DIRECT_ADDR,0,opcode,0,0,ic,machineCommands);
		save_label(line,label,ic,machineCommands);/* Label skipping will be filled in stepTwo */
	}
	return TRUE;
}


/*
 * This function converts binary code to dots and slashes and writes the result to a file.
 */
void binaryToDots(line_code* machineCommands,short* machineData,short *ic,short *dc, FILE *output) 
{
	int i,j,k;

	/* Print the header of the output file. */
	fprintf(output,"Base 10 address Base 2 code\n");
	fprintf(output, "       %d    %d\n",(*ic)-IC_START_VALUE,*dc);
	
	/* Print the binary code for the machine commands. */
	for(i=IC_START_VALUE;i < (*ic);i++) 
	{
		fprintf(output, "%d     ",i);
		for(j=13; j>=0; j--)
		{
			if (machineCommands[i-IC_START_VALUE].code_info.label[0] != '\0') 
			{/* The label is not null
			  * which means code is in struct code_info*/
				if((machineCommands[i-IC_START_VALUE].code_info.code) & 1<<j)
					fprintf(output, "/");
				else
					fprintf(output, ".");
			}
			else
			{
				/* If the label is null, the code is in the machineCommands array. */
				if((machineCommands[i-IC_START_VALUE].code) & 1<<j)
					fprintf(output, "/");
				else
					fprintf(output, ".");
			}
		}
		fprintf(output,"\n");
	}
	
	/* Print the binary code for the machine data. */
	for(k=0; k < *dc; k++,i++) 
	{
		fprintf(output, "%d     ",i);
		for(j=13;j>=0;j--)
		{
			if(machineData[k] & 1<<j)
				fprintf(output, "/");
			else
				fprintf(output, ".");
		}
		fprintf(output,"\n");
	}

}




/*
 * This function gets a register name and returns the corresponding register number if it's valid.
 */
reg get_register_by_name(char *name) 
{
	if (name[0] == 'r' && isdigit(name[1]) && (name[2]=='\0' || isspace(name[2]))) 
	{
		int digit = name[1] - '0'; /* convert digit ascii char to actual single digit */
		if (digit >= R0 && digit <= R7) /* Check if the digit is within the valid range for registers. */
			return digit;
	}
	return NONE_REG; /* No match */
}

/*
 * This function gets a command name and returns the corresponding opcode if it's valid.
 */
void get_opcode(char *cmd, opcode *opcode_out) 
{
	int i;
	/*all the commands in a 2d array of chars*/
	char *commands[] = {
        "mov",
        "cmp",
        "add",
        "sub",
        "not",
        "clr",
        "lea",
        "inc",
        "dec",
        "jmp",
        "bne",
        "red",
        "prn",
        "jsr",
        "rts",
        "stop"
    	};
	
	/* Search for the command name in the array of commands. */
	for (i = 0; i<NUM_OF_FUNCS ; i++) /*i is the index that is exactly like the enums of each command*/ 
	{
		if (!strcmp(commands[i], cmd) ) 
		{
			/* If the command name is found, set the opcode_out to the corresponding opcode. */
			*opcode_out = i;
			return ;
		}
	}
	*opcode_out = NONE_OP;/*didnt found a command in the table of the commands*/
}

/*
 * This function checks the validity of the operand of an assembly command, and updates the necessary data for it.
 */
bool check_operand_validity(line_info line, char* command, char* targetOp, int opcode, int* targetdAddress, int* targetValue, int whichGroup)
{
	int flag = 0;
	/*Flag:
				1 if operand is a number
				0 if operand is NOT a number
				-1 error */
				
	/* Check if the target operand is a number or not. */
	check_if_number(line, targetOp, &flag, targetValue);
	if (flag == -1)
		return FALSE; /* Error occurred */
	/* if operand not register and not number -> it's a label */
	if (flag == 0)
	{
		if (targetOp[0] == '&') /*if there is a & before the label*/
		{
			strcpy(targetOp, targetOp + 1); /*skip the & to check for validity*/
		}
		if (!is_valid_label_name(targetOp))
		{
			printf_line_error(line, "Invalid label name: %s", targetOp);
			return FALSE; /* Error occurred */
		}
		*targetdAddress = DIRECT_ADDR;
		return TRUE;
	}
	
	/* If the target operand is a number. */
	if(whichGroup == FIRSTGROUPSOURCE)
	{
		/* If the command is LEA, the source operand cannot be a number. */
		if(opcode == LEA_OP )
		{
			printf_line_error(line, "This command source cannot be number: %s", command);
			return FALSE;
		}
	}
	else if(whichGroup == FIRSTGROUPTARGET)
	{
		/* If the command is not one of the following, the target operand cannot be a number. */
		if (opcode != CMP_OP && opcode != JMP_OP && opcode != BNE_OP && opcode != JSR_OP)
		{ /*only on the first group the check, and not cmp*/
			printf_line_error(line, "This command target cannot be a number: %s", command);
			return FALSE;
		}
	}
	else if(whichGroup == SECONDGROUP)
	{
		/* If the command is not PRN, the target operand cannot be a number. */
		if(opcode != PRN_OP)
		{ 
			printf_line_error(line, "This command target cannot be number: %s", command);
			return FALSE;
		}
	}
	
	
	return TRUE;
}

