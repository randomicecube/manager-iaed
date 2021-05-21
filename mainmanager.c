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
linkAVL set(linkAVL x, Dlist *dll, char *s){
	char *path, *val, *dir;
	linkAVL auxTree = x;
	struct nodeAVL *auxDir = x->node, *auxTraverse;
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
		auxTraverse = traverse(NOT_FIND_ERROR, dir, auxTree);
		if(auxTree == x && auxTraverse == NULL) x = insertAVL(x, auxDir);
		else if(auxTraverse == NULL) auxTree = insertAVL(auxTree, auxDir);
		dirDLL = auxDir->subDirectories;
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	if(auxTree == x){
		strcpy(s, val);
	}
	else{
		strcpy(auxDir->value, val);
	}
	free(dir);
	free(path);
	free(val);
	return x;
}

struct nodeAVL *setAux(char*dir, linkAVL x, Dlist *dll){
	struct nodeAVL *newNodeAVL = traverse(NOT_FIND_ERROR, dir, x);
	if(newNodeAVL==NULL){
		newNodeAVL = createNodeAVL("", dir);
		newNodeAVL->tree = initializeAVL();
		newNodeAVL->subDirectories = initializeDLL();
		dll = insertTailDLL(dll, newNodeAVL);
	}
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
	if(auxTree != NULL && auxTree->node != NULL){
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
void find(linkAVL x, char *s){
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
	if(auxTree == x){
		printf("%s\n", s);
		return;
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
	else skip = 1;
	
	while(skip == 0 && dir != NULL){
		/* perhaps change FIND_ERROR to another name */
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(auxDir == NULL){
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
	if(strcmp(x->node->dirName, "") != 0) printf("%s\n", x->node->dirName);
	traverseListSubPath(x->right);
	return;
}

/* search command - searches the path with a given value */ 
void search(linkAVL x, Dlist *dll, char *s){
	char *value = (char *)malloc(sizeof(char)*MEM_AMOUNT);
	char *rightPath = (char *)malloc(sizeof(char)*MEM_AMOUNT);
	rightPath[0] = '\0';
	getchar();
	readValue(value);
	if(strcmp(value, s) == 0){
		return;
	}
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

/* WARNING ----------------------------------- */
/* this function needs a thorough cleansing */
/* WARNING ----------------------------------- */
int searchAux(char *path, char *s, linkAVL x, Dlist *dll){
	struct nodeAVL *auxNode;
	char *auxStr;
	linkAVL auxTree = x;
	if(auxTree->node != NULL){
		for(auxNode = dll->head; auxNode != NULL; auxNode = auxNode->next){
			if(strcmp(auxNode->value, s) == 0 || searchAux(path, s, auxNode->tree, auxNode->subDirectories) == SUCCESS){
				auxStr = (char*)malloc(sizeof(char)*(strlen(path)+strlen(s)+strlen(auxNode->dirName)+1));
				strcpy(auxStr, "/");
				strcat(auxStr, auxNode->dirName);
				strcat(auxStr, path);
				strcpy(path, auxStr);
				free(auxStr);
				return SUCCESS;
			}
		}
	}
	return FAIL;
}

/* delete - deletes a path and all its subpaths */
void del(linkAVL x, Dlist *dll){
	char c, *dir, *path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	linkAVL auxTree = x, prevTree = x;
	Dlist *auxDLL = dll;
	struct nodeAVL *auxDir = x->node;

	if((c = getchar()) != '\n' &&  c != EOF){
		scanf("%s", path);
	}
	else{
		x = freeAVL(x);
		free(x->node);
		free(x);
		free(dll);
		free(path);
		return;
	}
	dir = strtok(path, "/");
	while(dir != NULL){
		if(auxTree != x) auxDLL = auxDir->subDirectories;
		prevTree = auxTree;
		/* change FIND_ERROR to something else */
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(auxDir == NULL){
			return;
		}
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	puts("equipa");
	auxDLL = deleteNodeDLL(auxDLL, auxDir->dirName);
	puts("coatres");
	prevTree = deleteNodeAVL(auxDir, prevTree);
	puts("bryan ruiz");
	free(dir);
	free(path);
	return;
}