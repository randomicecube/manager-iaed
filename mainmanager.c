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

void set(linkAVL x, Dlist *dll){
	char *path, *val, *dir;
	struct nodeAVL *auxDir;
	linkAVL auxTree = x;
	Dlist *dirDLL = dll;
	path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	val = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	getchar();
	readPath(path);
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

struct nodeAVL* setAux(char *dir, linkAVL x, Dlist *dll){
	struct nodeAVL *newNodeAVL = traverse(NOT_FIND_ERROR, dir, x);
	insertTailDLL(dll->head, dll->tail, dir);
	if(newNodeAVL == NULL){
		newNodeAVL = createNodeAVL("", dir);
		newNodeAVL->tree = initializeAVL();
		newNodeAVL->subDirectories = initializeDLL();
	}
	x = insertAVL(x, newNodeAVL);
	return newNodeAVL;
}

void find(linkAVL x){
	char *path, *dir;
	struct nodeAVL *auxDir;
	linkAVL auxTree = x;
	path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	getchar();
	scanf("%s", path);
	dir = strtok(path, "/");
	while(dir != NULL){
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(strcmp(auxDir->dirName, "") == 0){
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