/*
 * File: dlinkedlist.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing the doubly linked list's functions and definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* for simplicity's sake, I'll refer to a doubly linked list as a DLL */

/* inserts the node as the new tail of the DLL */
Dlist *insertTailDLL(Dlist *dll, struct nodeAVL *nodeDir){
  nodeDir->next = NULL;
  nodeDir->prev = dll->tail;
  if(dll->head == NULL){
    dll->head = nodeDir;
  }
  if(dll->tail != NULL){
    dll->tail->next = nodeDir;
  }
  dll->tail = nodeDir;
  return dll;
}

/* deletes a node from the DLL */
Dlist* deleteNodeDLL(Dlist *dll, char *s){
  struct nodeAVL *currNode, *prevNode;
  if(dll->head == NULL)
  for(currNode = dll->head, prevNode = NULL; currNode != NULL; prevNode = currNode, currNode = currNode->next){
    if(currNode->dirName != NULL)
    if(strcmp(currNode->dirName, s) == 0){
      if(currNode == dll->head){
        if(currNode->next != NULL){
          dll->head = currNode->next;
          dll->head->prev = NULL;
        }
        else dll->head = NULL;
      }
      else{
        if(prevNode->next != NULL) prevNode->next = currNode->next;
        if(currNode->next != NULL) currNode->next->prev = prevNode;
      }
      /* the node itself will be freed afterwards, in freeNodeAVL */
      return dll;
    }
  }
  return dll;
}

Dlist* initializeDLL(){
  Dlist *newList = (Dlist *)malloc(sizeof(Dlist));
  newList->head = NULL;
  newList->tail = NULL;
  return newList;
}