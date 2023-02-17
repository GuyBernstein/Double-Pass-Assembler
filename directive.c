#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>


#include "utils.h"



/* Returns the first directive from the specified index. if no such one, returns NONE */
directive find_directive_from_index(line_info line, int *index)
{
	char temp[MAX_LINE];
	
	int j;
	directive result;

	MOVE_TO_NOT_WHITE(line.content, *index) /* get index to first not white place */
	if (line.content[*index] != '.') 
		return NONE_DIRE;
	
	/* Let's allocate some memory to the string needed to be checked */
	for (j = 0; line.content[*index] && line.content[*index] != '\t' && line.content[*index] != ' '; (*index)++, j++) 
		temp[j] = line.content[*index];
	
	temp[j] = '\0'; /* End of string */
	
	/* if invalid instruction but starts with '.', return error */
	if ((result = find_directive_by_name(temp+1)) != NONE_DIRE) 
		return result;
		
	printf_line_error(line, "Invalid instruction name: %s", temp);
	return ERROR_DIRE; /* starts with '.' but not a valid zz! */
}


/* This function recieves an integer of the line number and a string
 * returns a string(or NULL if invalid string)*/
int checkValidString(line_info line, char *string,char *str)
{
	
	char *ptrString = string;/*pointer to the given string*/
	
	/* Check if the string is empty */
	if (string == NULL) 
	{
		printf_line_error(line,"(%s).string must recive input\n",ptrString);
		return 0;
	}
	ptrString += skipSpacesAndTabs(ptrString);/*skip the first spaces*/
	
	
	
	if(ptrString[0] != '"')/*check for quotation marks at the beggining of the string*/
	{
		printf_line_error(line,"(%s) need quotation marks at the beggining of the string\n",ptrString);
		return 0;
	}
	
	ptrString += 1;/*advance the pointer after the first quotation mark*/
	strcpy(str,ptrString);/*copy the string for output*/

	if ((ptrString = strchr(str,'"')) == NULL)/* search for another quotation mark 
							 * if cant find, print a message
							 ptrString points to the second quotation marks at str*/
	{
		printf_line_error(line,"(%s) need quotation marks at the ending of the string\n",ptrString);
		return 0;
	}
	ptrString[0]= '\0';/*change the second quotation mark to \0 */

	ptrString += 1;/*advance the pointer after the second quotation mark*/
  	ptrString += skipSpacesAndTabs(ptrString);/*skip spaces after quotation mark*/

	if(ptrString[0]=='\0'){/*found nothing's after the second quotation mark*/

		return 1;/*return the string*/
	}
	else/*found something after the second quotation mark*/
	{

		printf_line_error(line," extranious text after ending quotation marks of the string\n");
		return 0;
	}	

		
	
}


/* This function recieves an integer of the line number and a string
 * returns an array of integers(or NULL if invalid data)*/
int checkValidData(line_info line, char *data,short* numbers)
{

	
	char *token;/* a pointer the numbers in data*/
	char *endptr;/*a pointer to what comes after the numbers*/
	long number;/*the number*/
	int num_numbers = 0;/*index of the numbers in the data*/
	char *ptrData = data;/*pointer to the data string*/
	int dataLen;/*the length of the data*/
	
	/* Check if the data is empty */
	if (data == NULL) 
	{
		printf_line_error(line, ".data must recive input");
		return 0;
	}
	
	removeSpaces(ptrData);/*remove all spaces*/
	
	dataLen = strlen(ptrData);/*the length of the data string(without spaces)*/
	
	
	
	
	

	/* Check if the input string starts or ends with commas*/
	if (ptrData[0] == ',' || ptrData[dataLen-1] == ',') 
	{
		printf_line_error(line,"(%s) illegal comma.\n",ptrData);
		return 0;
	}
  
	/* Check if the data has consecutive commas*/
	if (strstr(data, ",,") != 0) 
	{
		printf_line_error(line,"(%s) consecutive commas.\n",ptrData);
		return 0;
	}

	/* Get the first number */
	token = strtok(ptrData, ",");
	while (token != 0)
	{
	
	
		/* Check if the token is an integer */
		number = strtol(token, &endptr, 10);
		if (*endptr != '\0') 
		{
			
			printf_line_error(line,"(%s) not an integer\n",endptr);
			return 0;
		}
		/* Check if the number is short  */
   		if (number < SHRT_MIN || number > SHRT_MAX ) 
   		{
			printf_line_error(line,"%ld value out of range\n",number);
     			return 0;
    		}
		/* Add the number to the array */
		numbers[num_numbers++] = (short)number;
		/* Get the next token */
		token = strtok(NULL, ",");
	}
	return 1;/*return the array*/
}

/* Adding an input short to the data array 
	also counts the amount of numbers and add to dc counter */
bool insertDataToArray(short* input, short* output,int* dc) {
	int i;
	for(i=0;input[i]!='\0';i++,(*dc)++){
		output[*dc] = input[i];
    printf("%d: %d\n",*dc,output[*dc]);	/* to be removed */
	} 
	return TRUE;
}

/* Adding an input String to the data array and converting it to short
	 also counts the chars and add to dc counter */
bool insertStringToArray(char* input, short* output,int* dc) {
	int i;
	for(i=0;input[i]!='\0';i++,(*dc)++){
		output[*dc] = (short)input[i];
    printf("%d: %d\n",*dc,output[*dc]);	/* to be removed */
	}
	output[*dc] = '\0';	/* add '\0' at the end */
	printf("%d: %d\n",*dc,output[*dc]); /* to be removed */	
	(*dc)++;
	return TRUE;	 
}
