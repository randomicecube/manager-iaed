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
	char *path, *val;
	path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	val = (char*)malloc(sizeof(char)*MEM_AMOUNT);

	getchar();
	scanf("%s", path);
	getchar();
	readValue(val);
	
	x = set_r(x, dll, path, val);
	if(x == NULL){
		strcpy(s, val);
	}

	free(path);
	free(val);
	return x;
}

/* recursive "section" of set, goes through the path */
linkAVL set_r(linkAVL x, Dlist *dll, char* path, char* value){
	char* dir;
	struct nodeAVL *auxTraverse;
	linkAVL auxTree;

	dir = strtok(path, "/");
	if(dir == NULL) return NULL;

	auxTraverse = traverse(NOT_FIND_ERROR, dir, x);
	if(auxTraverse == NULL){
		auxTraverse = setAux(dir, x, dll);
		x = insertAVL(x, auxTraverse);
	}

	auxTree = set_r(auxTraverse->tree, auxTraverse->subDirectories, NULL, value);
	if(auxTree == NULL){
		/* reached the last dir, set the value */
		if(auxTraverse->value != NULL) free(auxTraverse->value);
		auxTraverse->value = (char*)malloc(sizeof(char)*(strlen(value)+1));
		strcpy(auxTraverse->value, value);
	}
	else {
		auxTraverse->tree = auxTree;
	}

	return x;
}

/* aux function to set, checks if a given dir is in the tree; if not, adds it */ 
struct nodeAVL *setAux(char*dir, linkAVL x, Dlist *dll){
	struct nodeAVL *newNodeAVL;

	if(x != NULL && x->node != NULL && x->node->dirName != NULL){
		newNodeAVL = traverse(NOT_FIND_ERROR, dir, x);
	}
	else newNodeAVL = NULL;

	if(newNodeAVL==NULL){
		newNodeAVL = createNodeAVL("", dir);
		insertTailDLL(dll, newNodeAVL);
	}
	return newNodeAVL;
}

/* print command - prints all paths and values */
void print(char *s, linkAVL x, Dlist *dll){
	struct nodeAVL *auxNode;
	char *auxStr, *tempS = (char*)malloc(sizeof(char)*(strlen(s)+1));

	/* the "base" for this level's path */
	strcpy(tempS, s);
	if(x != NULL && x->node != NULL && dll != NULL){
		for(auxNode = dll->head; auxNode != NULL; auxNode = auxNode->next){
			if(auxNode->dirName != NULL){
				auxStr = (char*)malloc(sizeof(char)*(strlen(auxNode->dirName)+strlen(s)+2));
				auxStr[0] = '\0';
				/* building the path */
				strcat(auxStr, "/");
				strcat(auxStr, auxNode->dirName);
				strcat(s, auxStr);
				free(auxStr);
				/* if it's not an "empty" node, print the path (and its value) */
				if(auxNode->value != NULL){
					printf("%s %s\n", s, auxNode->value);
				}
				print(s, auxNode->tree, auxNode->subDirectories);
				strcpy(s, tempS);
			}
		}
	}
	free(tempS);
	return;
}

/* find command - prints the value stored within a path */
void find(linkAVL x, char *s){
	char c, *dir, *path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	linkAVL auxTree = x;
	struct nodeAVL *auxDir;
	int skip = 0;

	if((c = getchar()) == '\n' || c == EOF) skip = 1;
	else{
		scanf("%s", path);
		dir = strtok(path, "/");
	}

	while(skip == 0 && dir != NULL){
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(auxDir == NULL){
			free(path);
			return;
		}
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	if(auxTree == x){
		printf("%s\n", s);
		free(path);
		return;
	}

	if(auxDir->value == NULL) printf(NO_DATA);
	else printf("%s\n", auxDir->value);

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
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(auxDir == NULL){
			free(path);
			return;
		}
		dir = strtok(NULL, "/");
		auxTree = auxDir->tree;
	}
	traverseListSubPath(auxTree);
	free(path);
	return;
}

/* aux function to list - traverses the tree, prints its directory names */
void traverseListSubPath(linkAVL x){
	if(x == NULL) return;

	traverseListSubPath(x->left);
	if(x->node != NULL && x->node->dirName != NULL){
		printf("%s\n", x->node->dirName);
	}
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
		free(value);
		free(rightPath);
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

/* aux function to search - "builds" the to-be-printed path */
int searchAux(char *path, char *s, linkAVL x, Dlist *dll){
	struct nodeAVL *auxNode;
	char *auxStr;
	int length;
	linkAVL auxTree = x;

	if(auxTree != NULL){
		for(auxNode = dll->head; auxNode != NULL; auxNode = auxNode->next){
			if(
				(auxNode->value != NULL && strcmp(auxNode->value, s) == 0) ||
				searchAux(path, s, auxNode->tree, auxNode->subDirectories) == SUCCESS
				){
				length = strlen(path)+strlen(s)+strlen(auxNode->dirName)+1;
				auxStr = (char*)malloc(sizeof(char)*length);
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
linkAVL del(linkAVL x, Dlist *dll){
	char c, *dir, *path = (char*)malloc(sizeof(char)*MEM_AMOUNT);
	linkAVL auxTree = x, prevTree = x;
	Dlist *auxDLL = dll;
	struct nodeAVL *auxDir, *prevDir = NULL;

	if((c = getchar()) != '\n' &&  c != EOF){
		scanf("%s", path);
	}
	else{
		x = freeAVL(x);
		free(x);
		x = NULL;
		free(path);
		return x;
	}

	dir = strtok(path, "/");
	while(dir != NULL){
		if(auxTree != x){
			auxDLL = auxDir->subDirectories;
			prevDir = auxDir;
		}
		
		auxDir = traverse(FIND_ERROR, dir, auxTree);
		if(auxDir == NULL){
			free(path);
			return x;
		}
		prevTree = auxTree;
		auxTree = auxDir->tree;
		dir = strtok(NULL, "/");
	}
	deleteNodeDLL(auxDLL, auxDir->dirName);
	auxTree = deleteNodeAVL(auxDir, prevTree);
	free(path);
	if(prevDir == NULL) x = auxTree;
	else prevDir->tree = auxTree;
	return x;
}