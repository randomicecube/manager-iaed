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

/* creates a new, to-be-inserted, node */
link createNodeDLL(char *s){
  link newNode = (link)malloc(sizeof(struct nodeDLL));
  newNode->value = (char*)malloc(sizeof(char)*(strlen(s) + 1));
  strcpy(newNode->value, s);
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;  
}

/* inserts the node as the new tail of the DLL */
void insertTailDLL(link head, link tail, char *s){
  link newNode = createNodeDLL(s);
  if(head == NULL){
    head = newNode;
  }
  if(tail != NULL){
    tail->next = newNode;
  }
  newNode->next = NULL;
  newNode->prev = tail;
  tail = newNode;
  return;
}

/* looks up the node containing a certain value (s) on the DLL */
link lookupDLL(link head, char *s){
  link aux;
  for(aux = head; aux != NULL; aux = aux->next){
    if(strcmp(s, aux->value)==0){
      return aux;
    }
  }
  return NULL;
}

/* deletes a node from the DLL */
link deleteNodeDLL(link head, char *s){
  link x, prev;
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
void printDLL(link head){
  link aux;
  for(aux = head; aux != NULL; aux = aux->next){
    printf("%s\n", aux->value);
  }
  return;
}

/* frees a node */
void freeNodeDLL(link x){
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

void freeDLL(link head){
  link x;
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
