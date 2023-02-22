#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "stepOne.h"
#include "preAssembler.h" 
#include "utils.h"



static bool process_file(char *filename);

int main (int argc, char *argv[]) 
{

	
	int i;
	/* To break line if needed */
	bool succeeded = TRUE;
	/* checks if file name was given */
	if (argc == 1) 
	{
		printf("\nError: no file was found\n");
		exit(1);
	}
	/* Process each file by arguments */
	for (i = 1; i < argc; ++i) 
	{
		/* if last process failed and there's another file, break line: */
		if (!succeeded) 
			puts("");
		/* foreach argument (file name), send it for full processing. */
		succeeded = process_file(argv[i]);
		
		/* Line break if failed */
	}
	return 0;
}
static bool process_file(char *fileName)
{
	/* variables declaration*/
	table symbol_table = NULL;
	long ic= 0;
	long dc= 0;
	/* return value  if needed */
	
	int temp_c;
	
	short machineCommands[MemorySize];/* Array to storge the binary commands */
	short machineData[MemorySize];/* Array to storge the binary data */
	
	
	
	char *fileNameAS; /* input filename.as */
	char *fileNameAM;/* output filename.am */
	
	FILE *ipf; /* Current assembly file descriptor to process */
	
	char temp_line[MAX_LINE + 2]; /* temporary string for storing line, read from file */
	
	bool is_success = TRUE; /* is succeeded so far */
	
	
	
	line_info curr_line_info;/* struct of the line info*/	
	
	/* add .as to file name */
	fileNameAS = strallocat(fileName, ".as");
	/* add .am to file name */
	fileNameAM = strallocat(fileName, ".am");

	/* open  input file in read mode*/
	ipf = fopen(fileNameAS, "r");
	if(ipf == NULL)
	{
		/* if file couldn't be opened, write to stderr. */
		printf("Error: file %s is inaccessible for reading. skipping it.\n", fileNameAS);
		/* The only allocated space is for the full file name */
		free(fileNameAS); 
		free(fileNameAM);
		return FALSE;
	}
	
	

	/* Pre Assembler changing macros and creating am file*/
	is_success = preAssembler(ipf,fileNameAM);
			

	fclose(ipf);/*close the filename + ".as" */
	free(fileNameAS);

	ipf = fopen(fileNameAM, "r");
	if(ipf == NULL)
	{
		/* if file couldn't be opened, write to stderr. */
		printf("Error: file %s is inaccessible for reading. skipping it.\n", fileNameAM);
		free(fileNameAM); /* The only allocated space is for the full file name */
		return FALSE;
	}
	
	
	/* start step one: */
	curr_line_info.file_name = fileNameAM;
	curr_line_info.content = temp_line; /* We use temp_line to read from the file, but it stays at same location. */
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
		else 
		{
		
		if(!stepOne(curr_line_info, machineCommands, machineData, &ic, &dc, &symbol_table))
			if (is_success) 
			{
				
				
				is_success = FALSE;
			}
		}
	}
	fclose(ipf);
	free(fileNameAM);
	
	return is_success;
}
