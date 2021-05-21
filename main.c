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
	Dlist *rootDLL = initializeDLL();
	linkAVL rootAVL = initializeAVL();
	char *rootValue = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	strcpy(rootValue, "");

	do{
		rootAVL = commandHub(rootAVL, rootDLL, rootValue);
	}while(rootAVL != NULL);

	free(rootValue);
	return 0;
}

/* TODO: set, print, find, list, search, delete */

/* Hub that redirects the command to its respective functions */
linkAVL commandHub(linkAVL tree, Dlist *dll, char*s){
	char *command = (char*)malloc(sizeof(char)*MAX_COMMAND_SIZE), *auxStr;
	scanf("%s", command);

	if(strcmp(command, QUIT) == 0){
		tree = freeAVL(tree);
		free(tree);
		tree = NULL;
		free(dll);
		free(command);
		command = NULL;
		return NULL;
	}
	else if(strcmp(command, HELP) == 0){
		help();
	}
	else if(strcmp(command, PRINT) == 0){
		if(strcmp(s, "") != 0){
			printf("%s\n", s);
		}
		auxStr = (char *)malloc(sizeof(char)*MEM_AMOUNT);
		strcpy(auxStr, "");
		print(auxStr, tree, dll);
		free(auxStr);
	}
	else if(strcmp(command, SET) == 0) 
		tree = set(tree, dll, s);
	else if(strcmp(command, FIND) == 0) 
		find(tree, s);
	else if(strcmp(command, LIST) == 0)
		list(tree);
	else if(strcmp(command, SEARCH) == 0) 
		search(tree, dll, s);
	else if(strcmp(command, DELETE) == 0) 
		del(tree, dll);

	free(command);
	return tree;
}

void readValue(char *s){
	int i = 0;
	char c;
	for(c = getchar(); c != EOF && c != '\n'; *(s + i++) = c, c = getchar());
	*(s + i) = '\0';
	return;
}