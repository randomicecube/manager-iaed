/*
 * File: main.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing main and the command redirections
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* Main program function */
int main(){
	int state;

	do{
		printf(PROMPT);
		state = commandHub();
	}while(state == CONTINUE);

	return 0;
}

/* TODO: set, print, find, list, search, delete */

/* Hub that redirects the command to its respective functions */
int commandHub(){
	char *command = (char*)malloc(sizeof(char)*MAX_COMMAND_SIZE), *input;
	scanf("%s", command);
	
	if(strcmp(command, QUIT) == 0){
		/* missing here: freeing function(s) for the BST and such*/
		free(command);
		return EXIT;
	}
	else if(strcmp(command, HELP) == 0) 
		help();

	/* this amount of memory can be changed afterwards if needed */
	input = (char*)malloc(sizeof(char)*MEM_AMOUNT)
	readInput(input);

	/* else if(strcmp(command, SET) == 0) 
		 set(input);
	else if(strcmp(command, PRINT) == 0) 
		print(input);
	else if(strcmp(command, FIND) == 0) 
		find(input);
	else if(strcmp(command, LIST) == 0) 
		list(input);
	else if(strcmp(command, SEARCH) == 0) 
		search(input);
	else if(strcmp(command, DELETE) == 0) 
		del(input); */
	
	free(input);
	free(command);
	return CONTINUE;
}