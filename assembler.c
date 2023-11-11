#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "stepOne.h"
#include "preAssembler.h" 
#include "utils.h"
#include "stepTwo.h"

/* 
 * Function: process_file
 * ----------------------
 * This function takes a filename as an argument and processes it. It returns 
 * a boolean indicating whether or not the processing was successful.
 */
static bool process_file(char *filename);

int main (int argc, char *argv[]) 
{

	
	int i;
	/* To break line if needed */
	bool succeeded = TRUE;
	/* checks if file name was given */
	if (argc == 1) 
	{
		/* 
		 * Error: no file was found. Print an error message and exit with status 1.
		 */
		printf("\nError: no file was found\n");
		exit(1);
	}
	/* Process each file by arguments */
	for (i = 1; i < argc; ++i) 
	{
		/* if last process failed and there's another file, break line: */
		if (!succeeded) 
			puts("");
		/* 
		 * Send the file name for full processing and update the `succeeded` variable
		 * based on whether or not the processing was successful.
		 */
		succeeded = process_file(argv[i]);
		
		/* Line break if failed */
	}
	return 0;
}

/* 
 * Function: process_file
 * ----------------------
 * This function takes a filename as an argument and processes it. It reads the
 * file line by line and performs two passes on the code. In the first pass, it
 * creates a symbol table and fills in the memory with data and machine commands.
 * In the second pass, it fills in the missing data in the machine commands and
 * creates the output files. The function returns a boolean indicating whether
 * or not the processing was successful.
 */
static bool process_file(char *fileName)
{
	/* variables declaration*/
	table symbol_table = NULL;
	
	
	short ic= IC_START_VALUE;
	short dc= 0;
	
	int temp_c;
	short i;
	line_code machineCommands[MEMORYSIZE];/* Array to storge the binary commands */
	short machineData[MEMORYSIZE];/* Array to storge the binary data */
	
	
	
	char *fileNameAS; /* input filename.as */
	char *fileNameAM;/* output filename.am */
	char *fileNameOB;/* output filename.ob */
	
	FILE *ipf; /* Current assembly file descriptor to process */
	FILE *opf; /*output file*/
	
	char temp_line[MAX_LINE + 2]; /* temporary string for storing line, read from file */
	
	bool is_success = TRUE; /* is succeeded so far */
	
	
	
	line_info curr_line_info;/* struct of the line info*/	
	
	/* add .as to file name */
	fileNameAS = strallocat(fileName, ".as");
	/* add .am to file name */
	fileNameAM = strallocat(fileName, ".am");
	/* add .ob to file name */
	fileNameOB = strallocat(fileName, ".ob");

	/* open  input file in read mode*/
	ipf = fopen(fileNameAS, "r");
	if(ipf == NULL)
	{
		/* if file couldn't be opened, write to stderr and return FALSE . */
		printf("Error: file %s is inaccessible for reading. skipping it.\n", fileNameAS);
		/* free the files */
		FREE_FILES(fileNameAS,fileNameAM,fileNameOB)
		return FALSE;
	}
	
	

	/* Pre Assembler changing macros and creating am file*/
	if( preAssembler(ipf,fileNameAM))
	{
		/* free the files */
		FREE_FILES(fileNameAS,fileNameAM,fileNameOB)
		return FALSE;
	}

	fclose(ipf);/*close the filename + ".as" */
	

	ipf = fopen(fileNameAM, "r");
	if(ipf == NULL)
	{
		/* if file couldn't be opened, write to stderr and return FALSE . */
		printf("Error: file %s is inaccessible for reading. skipping it.\n", fileNameAM);
		/* free the files */
		FREE_FILES(fileNameAS,fileNameAM,fileNameOB)
		return FALSE;
	}
	
	
	/* start step one: */
	curr_line_info.file_name = fileNameAM;
	curr_line_info.content = temp_line; 
	
	/* Read line - stop if read failed (when NULL returned) - usually when EOF. increase line counter for error printing. */
	for (curr_line_info.line_number = 1; fgets(temp_line, MAX_LINE + 2, ipf) != NULL; curr_line_info.line_number++) 
	{
		
		/* if line too long, the buffer doesn't include the '\n' char OR the file isn't on end. */
		if (strchr(temp_line, '\n') == NULL && !feof(ipf)) 
		{
			/* Print message and prevent further line processing, as well as second pass.  */
			printf_line_error(curr_line_info, "Line too long to process. Maximum line length should be %d.",
			                  MAX_LINE);
			is_success = FALSE;
			
			/* skip leftovers */
			do 
				temp_c = fgetc(ipf);
				
			while (temp_c != '\n' && temp_c != EOF);
		}
		
		/* Pass one: */
		if(!stepOne(curr_line_info, machineCommands, machineData, &ic, &dc, &symbol_table))
			is_success = FALSE;
		
	}
	/* if first pass didn't fail, start the second pass */
	if (is_success) 
	{
		/* Now let's add ic to each DC for each of the data symbols in table */
		add_value_to_type(symbol_table, ic, DATA_SYMBOL);
		
		/* First pass done right. start second pass: */
		rewind(ipf); /* Start from beginning of file again */
		for (curr_line_info.line_number = 1; !feof(ipf); curr_line_info.line_number++) 
		{
			i = 0;
			fgets(temp_line, MAX_LINE, ipf); /* Get line */
			MOVE_TO_NOT_WHITE(temp_line, i)
			
			is_success &= stepTwo(curr_line_info, &symbol_table);
		}
	}
	

	/* if second pass didn't fail, create last machine words and files for extern and entry(if needed) */
	if(is_success)
	{
		for(i =0;i<(ic-IC_START_VALUE);i++)
		{
			if (machineCommands[i].code_info.label[0] != '\0') 
			{/* The label is not null*/
				if(!process_spass_operand(machineCommands[i].code_info.line,i,&machineCommands[i],&symbol_table))
				{
					/* free the files and the table*/
					free_table(symbol_table);
					FREE_FILES(fileNameAS,fileNameAM,fileNameOB)
					return FALSE;
				}
			}
		}
	

		
   		/* Open file object file for output*/
   		opf = fopen(fileNameOB, "w");
    		if (opf == NULL) 
    		{
        		printf("Error: unable to open %s for writing.\n",fileNameOB);
        		/* free the files and the table*/
        		free_table(symbol_table);
        		FREE_FILES(fileNameAS,fileNameAM,fileNameOB)
        		return FALSE;
		}
		/* Convert machine code to binary and write to output file */
		binaryToDots(machineCommands,machineData,&ic,&dc, opf);
		
		/* Create extern and entry files (if needed) */
		if(!create_output_file(symbol_table, EXTERNAL_REFERENCE,fileName))
		{
			printf("Error: unable to open %s for writing.\n",fileName);
			is_success = FALSE;
		}
		if(!create_output_file(symbol_table, ENTRY_SYMBOL,fileName) && is_success)
		{
			printf("Error: unable to open %s for writing.\n",fileName);
			is_success = FALSE;
		}
	}
		
	
	
	fclose(ipf);/*close the filename + ".am" */
	/* free the files and the table*/
	FREE_FILES(fileNameAS,fileNameAM,fileNameOB)
	
	free_table(symbol_table);
	
	return is_success;
}

