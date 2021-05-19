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
		state = commandHub(rootAVL, rootDLL);
	}while(state == CONTINUE);

	return 0;
}

/* TODO: set, print, find, list, search, delete */

/* Hub that redirects the command to its respective functions */
int commandHub(linkAVL tree, Dlist *dll){
	char *command = (char*)malloc(sizeof(char)*MAX_COMMAND_SIZE), *auxStr;
	scanf("%s", command);

	if(strcmp(command, QUIT) == 0){
		freeAVL(tree);
		freeDLL(dll->head);
		free(tree);
		free(dll);
		free(command);
		return EXIT;
	}
	else if(strcmp(command, HELP) == 0){
		help();
	}
	else if(strcmp(command, PRINT) == 0){
		auxStr = (char *)malloc(sizeof(char)*MEM_AMOUNT);
		strcpy(auxStr, "");
		print(auxStr, tree, dll);
		free(auxStr);
	}
	else if(strcmp(command, SET) == 0) 
		set(tree, dll);
	else if(strcmp(command, FIND) == 0) 
		find(tree);
	else if(strcmp(command, LIST) == 0) 
		list(tree);
	else if(strcmp(command, SEARCH) == 0) 
		search(tree, dll);
	else if(strcmp(command, DELETE) == 0) 
		del(tree, dll);
	
	free(command);
	return CONTINUE;
}

void readValue(char *s){
	int i = 0;
	char c;
	for(c = getchar(); c != EOF && c != '\n'; *(s + i++) = c, c = getchar());
	*(s + i) = '\0';
	return;
}