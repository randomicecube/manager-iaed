/*
 * File: dlinkedlist.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing the doubly linked list's functions and definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* for simplicity's sake, I'll refer to a doubly-linked list as a DLL */

/* initializes a "fresh" DLL */
Dlist* initializeDLL(){
  Dlist *newList = (Dlist *)malloc(sizeof(Dlist));
  newList->head = NULL;
  newList->tail = NULL;
  return newList;
}

/* inserts the node as the new tail of the DLL */
struct nodeAVL *insertTailDLL(Dlist *dll, struct nodeAVL *nodeDir){
  nodeDir->next = NULL;
  nodeDir->prev = dll->tail;
  
  if(dll->head == NULL) dll->head = nodeDir;
  else dll->tail->next = nodeDir;

  dll->tail = nodeDir;
  return dll->head;
}

/* deletes a node from the DLL */
Dlist* deleteNodeDLL(Dlist *dll, char *s){
  struct nodeAVL *currNode;
  int found = 0;
  for(
      currNode = dll->head;
      !found && currNode != NULL && currNode->dirName != NULL;
      currNode = currNode->next
    ){
    if(strcmp(currNode->dirName, s) == 0){
      if(currNode == dll->head) dll->head = currNode->next;
      else{
        if(currNode->prev != NULL) currNode->prev->next = currNode->next;
        if(currNode->next != NULL) currNode->next->prev = currNode->prev;
      }
      /* I don't free the node itself here, it happens afterwards */
      found++;
    }
  }
  return dll;
}