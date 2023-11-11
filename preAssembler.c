#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "preAssembler.h"
#include "declarations.h"


/*
 * This function pre-assembles a given input file that contains macro definitions and macro expansions.
 * It stores any macro found in the input file into an array of struct macro,
 * and replaces the macro with its content in the output file.
 * It does some error checking and frees the memory used by the array of struct macro.
 */
bool preAssembler(FILE *ipf, char* fileName) 
{
	FILE *opf;
	char line[MAX_LINE]={'\0'};/* buffer to hold a line read from the input file*/
	int curr_macro = 0;/* index of the current macro being processed */
	int i,replaced;/* temporary variables used in the processing of macros */

    	char word[MAX_LINE];/* buffer to hold a word read from the input file */
    	macro *macros;/* array of struct macro to hold all the macros found in the input file */
    	int lineCount =0;/* counter for the current line number in the input file */

	int countMcr = 0;/* counter for the total number of macros found in the input file */
	int inMcr = 0;/* flag to indicate if the current line is inside a macro definition or not */
	char *mcrPtr;    /* pointer to point to the current position of the macro in the current line */

	/* Counting the total number of macros in the input file */
    	while (fgets(line, MAX_LINE, ipf) != NULL) 
    		  if (strstr(line, "mcr") != NULL)
    		  	countMcr++;
    		  	
    	
    	/* Rewind the input file pointer to the beginning of the file */
       	rewind(ipf);
    	       	
    	
    	/* Allocating memory for the array of macros */
    	macros = (macro*)(malloc_with_check(sizeof(macro)*(countMcr)));
    	
   	/* Open file {filename.am} for output */
    	opf = fopen(fileName, "w");
    	if (opf == NULL) 
    	{
        	printf("Error: unable to open %s.am for writing.\n",fileName);
        	exit(0);
	}

    	/* Reading line by line from input file */
    	while (fgets(line, MAX_LINE, ipf)) 
    	{
        	lineCount++;

		/* If the current line contains the keyword "mcr", it is a macro definition */
        	if ((mcrPtr = strstr(line, "mcr")) != NULL)
        	{	
			inMcr = 1;
          	  	/* Extract the name of the macro */
            		if(sscanf(mcrPtr, " mcr %s %s", macros[curr_macro].name,line)==2)
            		{
				/* Check for extranious context after mcr name */
				if(line != '\0')
				{
					printf("Error in line %d: extranious context after mcr name\n",lineCount);
				}
			}	
			/* Check for extranious context before mcr name */
			for(--mcrPtr;mcrPtr>=line;mcrPtr--)
			{
				if(!isspace(*mcrPtr) && *mcrPtr!='\0')
				{
					printf("Error in line %d: extranious context befor mcr name\n",lineCount);
					break;
				}
			}
			/* Check if the macro name is a reserved word */
   			printf("in line %d:mcr name:%s\n",lineCount, macros[curr_macro].name);
      			if(is_reserved_word( macros[curr_macro].name))
      			{
				printf("Error in line %d: mcr %s is reserved word and cannot be mcr name\n",lineCount,macros[curr_macro].name);
			}
            		/* Read the content of the macro into a buffer */
            		while (inMcr==1)
            		{
				if(fgets(line, MAX_LINE, ipf) == NULL)
				{
					printf("Error in line %d: reach EOF befor endmcr\n",lineCount);
					return 0;
				}	
				lineCount++;

				if( (mcrPtr = strstr(line,"endmcr")) != NULL) /*found endmcr*/
                		{
					inMcr=0;
                			i = (int)(mcrPtr - line);/*get the index of endmcr*/
                			line[i] = '\0';/*get rid of endmcr*/
                			
                			/*print what comes after endmcr*/
                			mcrPtr += MCR_END_SIZE;
                    			mcrPtr += skipSpacesAndTabs(mcrPtr);
                  
					/* Check for extranious context after endmcr */
                			if(mcrPtr[0] != '\0')
                			{
						printf("Error in line %d: extranious context after endmcr\n",lineCount);
					}
                		}
                		/* Check if the macro content exceeds the maximum size */
                		if(strlen(macros[curr_macro].content) + strlen(line) > sizeof(macros[curr_macro].content) -1)
                		{
                    	 		printf("Error in line %d: macro %s content exceed max size\n",lineCount,macros[curr_macro].name);
                    		}
                    		
                		strcat(macros[curr_macro].content, line);
                	}

            		curr_macro++;
        	}
        	else /* Current line is not a macro definition */
        	{
            		if(sscanf(line,"%s", word)==1)/*if able to read a word*/
            		{
                		replaced = 0;
                		for(i = 0; i <= curr_macro; i++) 
                		{
                    			if(!strcmp(word,macros[i].name))/*the word is a macro*/
                    			{
                        			replaced = 1;
                        			fprintf(opf, "%s", macros[i].content);/*print the macro content*/
                        
                        			break;
                    			}
		                }
		        }
                	if(!replaced)
                		fprintf(opf,"%s",line);
        	}
	
    	}
	/* Free the memory used by the array of macros */
    	free(macros);
    	
    	/* Close the output file */
    	fclose(opf);
    	
    	return 0;
}


