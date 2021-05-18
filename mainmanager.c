/*
 * File: mainmanager.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing the 6 "major" command functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* help command - print available commands and their information */
void help(){
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

/* set command - adds or modifies the to-be-stored value */
void set(linkAVL x, Dlist *dll){
	char *path, *val, *dir;
	linkAVL auxTree = x;
	struct nodeAVL *auxDir = x->node;
	Dlist *dirDLL = dll;
	path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	val = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	getchar();
	scanf("%s", path);
	getchar();
	readValue(val);
	dir = strtok(path, "/");
	while(dir != NULL){
		auxDir = setAux(dir, auxTree, dirDLL);
		dirDLL = auxDir->subDirectories;
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	strcpy(auxDir->value, val);
	free(path);
	free(val);
	return;
}

struct nodeAVL* setAux(char*dir, linkAVL x, Dlist *dll){
	struct nodeAVL *newNodeAVL = traverse(NOT_FIND_ERROR, dir, x);
	if(newNodeAVL==NULL){
		newNodeAVL = createNodeAVL("", dir);
		newNodeAVL->tree = initializeAVL();
		newNodeAVL->subDirectories = initializeDLL();
		insertTailDLL(dll, newNodeAVL);
	}
	x = insertAVL(x, newNodeAVL);
	return newNodeAVL;
}

/* print command - prints all paths and values */
/* WARNING ----------------------------------- */
/* this function needs a thorough cleansing */
/* WARNING ----------------------------------- */
void print(char *s, linkAVL x, Dlist *dll){
	struct nodeAVL *auxNode;
	char *auxStr, *tempS = (char*)malloc(sizeof(char)*(strlen(s)+1));
	linkAVL auxTree = x;
	strcpy(tempS, s);
	if(auxTree->node != NULL){
		for(auxNode = dll->head; auxNode != NULL; auxNode = auxNode->next){
			auxStr = (char*)malloc(sizeof(char)*(strlen(auxNode->dirName)+2));
			auxStr[0] = '\0';
			strcat(auxStr, "/");
			strcat(auxStr, auxNode->dirName);
			strcat(s, auxStr);
			free(auxStr);
			if(strcmp(auxNode->value, "") != 0){
				printf("%s %s\n", s, auxNode->value);
			}
			print(s, auxNode->tree, auxNode->subDirectories);
			strcpy(s, tempS);
		}
	}
	free(tempS);
	return;
}

/* find command - prints the value stored within a path */
void find(linkAVL x){
	char c, *path, *dir;
	linkAVL auxTree = x;
	struct nodeAVL *auxDir = x->node;
	int skip = 0;
	path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	if((c = getchar()) == '\n' || c == EOF){
		skip = 1;
	}
	else{
		readValue(path); /* need to change the name */
		dir = strtok(path, "/");
	}
	while(skip == 0 && dir != NULL){
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(auxDir == NULL){
			return;
		}
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	if(strcmp("", auxDir->value) == 0){
		printf(NO_DATA);
	}
	else{
		printf("%s\n", auxDir->value);
	}
	free(path);
	return;
}

/* list command - lists all the elements within a given subpath */
void list(linkAVL x){
	char c, *dir, *path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	struct nodeAVL* auxDir;
	linkAVL auxTree = x;
	int skip = 0;
	if((c = getchar()) != '\n' && c != EOF){
		scanf("%s", path);
		dir = strtok(path, "/");
	}
	else{
		skip = 1;
		strcpy(path, "");
	}
	while(skip == 0 && dir != NULL){
		auxDir = traverse(NOT_FIND_ERROR, dir, auxTree);
		if(strcmp(auxDir->dirName, "") == 0){
			return;
		}
		dir = strtok(NULL, "/");
		auxTree = auxDir->tree;
	}
	traverseListSubPath(auxTree);
	free(path);
	return;
}

void traverseListSubPath(linkAVL x){
	if(x == NULL){
		return;
	}
	traverseListSubPath(x->left);
	if(strcmp(x->node->dirName, "") != 0){
		printf("%s\n", x->node->dirName);
	}
	traverseListSubPath(x->right);
	return;
}

/* search command - searches the path with a given value */ 
void search(linkAVL x, Dlist *dll){
	char *value = (char *)malloc(sizeof(char)*MEM_AMOUNT);
	char *rightPath = (char *)malloc(sizeof(char)*MEM_AMOUNT);
	rightPath[0] = '\0';
	getchar();
	readValue(value);
	if(searchAux(rightPath, value, x, dll) == FAIL){
		printf(NOT_FOUND);
	}
	else{
		printf("%s\n", rightPath);
	}
	free(rightPath);
	free(value);
	return;
}


int searchAux(char *bleh, char *s, linkAVL x, Dlist *dll){
	struct nodeAVL *auxNode;
	char *auxStr;
	linkAVL auxTree = x;
	if(auxTree->node != NULL){
		for(auxNode = dll->head; auxNode != NULL; auxNode = auxNode->next){
			if(strcmp(auxNode->value, s) == 0 || searchAux(bleh, s, auxNode->tree, auxNode->subDirectories) == SUCCESS){
				auxStr = (char*)malloc(sizeof(char)*(strlen(s)+strlen(auxNode->dirName)+1));
				strcpy(auxStr, "/");
				strcat(auxStr, auxNode->dirName);
				strcat(auxStr, bleh);
				strcpy(bleh, auxStr);
				return SUCCESS;
			}
		}
	}
	return FAIL;
}