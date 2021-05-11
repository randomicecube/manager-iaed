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

	char *input = (char*)malloc(sizeof(char)*BUFFERSIZE);
	int state;

	do{
		printf(PROMPT);
		fgets(input, BUFFERSIZE, stdin);
		state = commandHub(input);
		input[0] = '\0';
	}while(state);

	free(input);
	return 0;
}

/* TODO: set, print, find, list, search, delete */

/* Hub that redirects the command to its respective functions */
int commandHub(char *input){

	char *command = (char*)malloc(sizeof(char)*MAX_COMMAND_SIZE);
	sscanf(input, "%s", command);
	
	if(strcmp(command, HELP) == 0) 
		helpHub();
	/* else if(strcmp(command, SET) == 0) 
		 setHub(input);
	else if(strcmp(command, PRINT) == 0) 
		printHub(input);
	else if(strcmp(command, FIND) == 0) 
		findHub(input);
	else if(strcmp(command, LIST) == 0) 
		listHub(input);
	else if(strcmp(command, SEARCH) == 0) 
		searchHub(input);
	else if(strcmp(command, DELETE) == 0) 
		deleteHub(input); */
	else{
		/* missing here: freeing function(s) for the BST and such*/
		free(command);
		return QUIT;
	}

	free(command);
	return CONTINUE;
}

/* help command - print available commands and their information */
void helpHub(){
	printf(HELP_INFO);
	printf(QUIT_INFO);
	printf(SET_INFO);
	printf(PRINT_INFO);
	printf(FIND_INFO);
	printf(LIST_INFO);
	printf(SEARCH_INFO);
	printf(DELETE_INFO);
	return;
}