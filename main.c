/*
 * File: main.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing main, input reading and command redirections
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* Main program function */
int main(){
	int state;

	/* initialize data structures here */

	do{
		printf(PROMPT);
		state = commandHub();
	}while(state == CONTINUE);

	return 0;
}

/* TODO: set, print, find, list, search, delete */

/* Hub that redirects the command to its respective functions */
int commandHub(){
	char *command = (char*)malloc(sizeof(char)*MAX_COMMAND_SIZE);
	char *input;
	scanf("%s", command);

	getchar(); /* skips the whitespace */
	/* the allocated amount of memory can be changed afterwards if needed */
	input = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	readAfterCommand(input);

	if(strcmp(command, QUIT) == 0){
		/* missing here: freeing function(s) for the data strutures*/
		free(command);
		return EXIT;
	}
	else if(strcmp(command, HELP) == 0){
		help();
		free(command);
		return CONTINUE;
	}
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

void readAfterCommand(char *s){
	int i = 0, currentMem = MEM_AMOUNT;
	char c;
	while((c = getchar()) != EOF && c != '\n'){
		if(i == currentMem){
			currentMem = 2*currentMem;
			s = (char*)realloc(s, sizeof(char)*currentMem);
		}
		*(s+i) = c;
		i++;
	}
	*(s+i) = '\0';
	return;
}