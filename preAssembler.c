#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "preAssembler.h"
#include "declarations.h"

int skipSpacesAndTabs1(char *s) 
{
	int n;
	for (n = 0; s[n] != 0 && (s[n] == ' ' || s[n] == '\t'); n++)
		{} /* Count how many spaces there are at the beginning */
	return n;
}

bool preAssembler(FILE *ipf, char* fileName) 
{
	FILE *opf;
	char line[MAX_LINE]={'\0'};
	int curr_macro = 0;
	int i,replaced;

    char word[MAX_LINE];
    struct macro *macros;
    int lineCount =1;

	int countMcr = 0;
	int inMcr = 0;
	int errFlag = 0;
	char *mcrPtr;    

	/* Reading line by line from input file */
    	while (fgets(line, MAX_LINE, ipf) != NULL) 
    		  if (strstr(line, "mcr") != NULL)/*count every time we find macros*/
    		  	countMcr++;
    		  	
    	
    	
       	rewind(ipf);
    	       	
    	
    	/* Creating an array of macros */
    	macros = (struct macro*)(malloc(sizeof(struct macro)*(countMcr)));
    	if(macros == NULL)
        {
       		free(macros);
        	printf("Error: not enough space in memory\n");
        	exit(0);
        }

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
        	
        	if ( strstr(line, "mcr") != NULL)/*found macro*/
        	{	
				inMcr = 1;
            	/* Extract the name of the macro */
            	if(sscanf(line, "mcr %s %s", macros[curr_macro].name,line)==2){
					/* Check for extranious context after mcr name */
					if(line != '\0'){
						printf("Error in line %d: extranious context after mcr name\n",lineCount);
						errFlag = 1;
					}
				}	
   	
      			
            	/* Read the content of the macro into a buffer */
            	while (inMcr==1) 
            	{
                	fgets(line, MAX_LINE, ipf);	
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
                		if(mcrPtr[0] != '\0'){
							printf("Error in line %d: extranious context after endmcr\n",lineCount);
							errFlag = 1;
						}
                	}
                	/*macro too long*/
                	if(strlen(macros[curr_macro].content) + strlen(line) > sizeof(macros[curr_macro].content) -1)
                	{
                     	printf("Error in line %d: macro %s content exceed max size\n",lineCount,macros[curr_macro].name);
						errFlag = 1;
                     	continue;
                    }
                    		
                	strcat(macros[curr_macro].content, line);
                	}

            		curr_macro++;
        	}
        	else
        	{
            		if(sscanf(line,"%s", word)==1)/*if able to read a word*/
            		{
                		replaced = 0;
                		for(i = 0; i <= curr_macro; i++) 
                		{
                    			if(!strcmp(word,macros[i].name))/*the word is a macro*/
                    			{
                        			replaced = 1;
                        			fprintf(opf, "%s\n", macros[i].content);/*print the macro content*/
                        
                        			break;
                    			}
		                }
		        }
                	if(!replaced)
                		fprintf(opf,"%s",line);
        	}
	
    	}

    	free(macros);
    	fclose(opf);
		if(errFlag == 1)
			exit(0);
    	return 0;
}

