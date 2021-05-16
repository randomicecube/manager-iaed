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
	Dlist *rootDLL = initializeDLL();
	linkAVL rootAVL = initializeAVL();

	do{
		printf(PROMPT);
		state = commandHub(rootAVL, rootDLL);
	}while(state == CONTINUE);

	return 0;
}

/* TODO: set, print, find, list, search, delete */

/* Hub that redirects the command to its respective functions */
int commandHub(linkAVL tree, Dlist *dll){
	char *command = (char*)malloc(sizeof(char)*MAX_COMMAND_SIZE);
	scanf("%s", command);

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
	/* else if(strcmp(command, PRINT) == 0){
		print(tree, dll);
		free(command);
		return CONTINUE;
	} */

	getchar(); /* skips the whitespace */

	if(strcmp(command, SET) == 0) 
		set(tree, dll);
	else if(strcmp(command, FIND) == 0) 
		find(tree); /*
	else if(strcmp(command, LIST) == 0) 
		list();
	else if(strcmp(command, SEARCH) == 0) 
		search();
	else if(strcmp(command, DELETE) == 0) 
		del(); */
	
	free(command);
	return CONTINUE;
}

void readPath(char *s){
	int i = 0, currentMem = MEM_AMOUNT;
	char c;
	while((c = getchar()) != ' ' && c != '\t'){
		if(i == currentMem){
			currentMem = 2*currentMem;
			s = (char*)realloc(s, sizeof(char)*currentMem);
		}
		*(s + i++) = c;
	}
	*(s + i) = '\0';
	return;
}

void readValue(char *s){
	int i = 0, currentMem = MEM_AMOUNT;
	char c;
	while((c = getchar()) != EOF && c != '\n'){
		if(i == currentMem){
			currentMem = 2*currentMem;
			s = (char*)realloc(s, sizeof(char)*currentMem);
		}
		*(s + i++) = c;
	}
	*(s + i) = '\0';
	return;
}