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
link createNode(char *s){
  link newNode = (link)malloc(sizeof(Node));
  newNode->value = (char*)malloc(sizeof(char)*(strlen(s) + 1));
  strcpy(newNode->value, s);
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;  
}

/* inserts the node as the new head of the DLL */
link insertHead(link head, link tail, char *s){
  link newNode = createNode(s);
  newNode->next = head;
  return newNode; /* nodeInserted is returned since it is the head */
}

/* inserts the node as the new tail of the DLL */
link insertTail(link head, char *s){
  link newNode, aux;
  if(head == NULL){
    return createNode(s); /* if there's no head, this is the "new" head */ 
  }
  newNode = createNode(s);
  for(aux = head; aux->next != NULL; aux = aux->next);
  aux->next = newNode;
  newNode->prev = aux;
  return head;
}

/* looksup the node containing a certain value (s) on the DLL */
link lookupDLL(link head, char *s){
  link aux;
  for(aux = head; aux != NULL; aux = aux->next){
    if(strcmp(s, aux->text)==0){
      return aux;
    }
  }
  return NULL;
}

/* deletes a node from the DLL */
link deleteNode(link head, char *s){
  link x, prev;
  int found = 0;
  for(x = head, prev = NULL; x != NULL && !found; prev = x, x = x->next){
    if(strcmp(x->text, s)==0){
      if(x==head){
        head = t->next;
      }
      else{
        prev->next = x-> next;
      }
      freeNode(x);
      found++;
    }
  }
  return head;
}

/* prints the values of each node, by their order in the DLL */
void printDLL(link head){
  link aux;
  for(aux = head; aux != NULL; aux = aux->next){
    printf("%s\n", aux->text);
  }
  return;
}

/* frees a node */
void freeNode(link x){
  free(x->text);
  free(x);
  return;
}