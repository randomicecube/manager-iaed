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
	readPath(path);
	readValue(val);
	dir = strtok(path, "/");
	while(dir != NULL){
		auxDir = traverseDir(dir, auxTree, dirDLL);
		dirDLL = auxDir->subDirectories;
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	strcpy(auxDir->value, val);
	return;
}

struct nodeAVL* traverseDir(char *dir, linkAVL x, Dlist *dll){
	int comp;
	linkAVL newTree;
	struct nodeAVL *newNodeAVL;
	Dlist *newDll;
	if(x == NULL || strcmp(x->node->dirName, "") == 0){
		insertTailDLL(dll->head, dll->tail, dir);
		newNodeAVL = createNodeAVL("", dir);
		newTree = initializeAVL();
		newDll = initializeDLL();
		newNodeAVL->tree = newTree;
		newNodeAVL->subDirectories = newDll;
		return newNodeAVL;
	}
	comp = strcmp(x->node->dirName, dir);
	if(comp == 0){
		return x->node;
	}
	else if(comp < 0){
		traverseDir(dir, x->right, dll);
	}
	else{
		traverseDir(dir, x->left, dll);
	}
	return NULL;
}

void find(linkAVL x){
	
}


/* -------------------- */
/* missing print() here */
/* -------------------- */
/*
void find(){
	char *path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	char *value, *dir;
	readPath(path);
	dir = strtok(path, )

} */