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
void insertTailDLL(Dlist *dll, struct nodeAVL *nodeDir){
  nodeDir->next = NULL;
  nodeDir->prev = dll->tail;
  if(dll->head == NULL){
    dll->head = nodeDir;
  }
  if(dll->tail != NULL){
    dll->tail->next = nodeDir;
  }
  dll->tail = nodeDir;
  return;
}

/* looks up the node containing a certain value (s) on the DLL */
struct nodeAVL *lookupDLL(struct nodeAVL *head, char *s){
  struct nodeAVL *aux;
  for(aux = head; aux != NULL; aux = aux->next){
    if(strcmp(s, aux->value)==0){
      return aux;
    }
  }
  return NULL;
}

/* deletes a node from the DLL */
struct nodeAVL *deleteNodeDLL(struct nodeAVL *head, char *s){
  struct nodeAVL *x, *prev;
  int found = 0;
  for(x = head, prev = NULL; x != NULL && !found; prev = x, x = x->next){
    if(strcmp(x->value, s)==0){
      if(x==head){
        head = x->next;
      }
      else{
        prev->next = x->next;
      }
      freeNodeDLL(x);
      found++;
    }
  }
  return head;
}

/* prints the values of each node, by their order in the DLL */
void printDLL(struct nodeAVL *head){
  struct nodeAVL *aux;
  for(aux = head; aux != NULL; aux = aux->next){
    printf("%s\n", aux->value);
  }
  return;
}

/* frees a node */
void freeNodeDLL(struct nodeAVL *x){
  if(x->next != NULL){
    x->next->prev = x->prev;
  }
  if(x->prev != NULL){
    x->prev->next = x->next;
  }
  free(x->value);
  free(x);
  return;
}

/* frees the DLL */

void freeDLL(struct nodeAVL *head){
  struct nodeAVL *x;
  if(head == NULL){
    return;
  }
  for(x = head; x != NULL; x = x->next){
    freeNodeDLL(x);
  }
  return;
}

Dlist* initializeDLL(){
  Dlist *newList = (Dlist *)malloc(sizeof(Dlist));
  newList->head = NULL;
  newList->tail = NULL;
  return newList;
}
