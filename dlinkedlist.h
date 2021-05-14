/*
 * File: dlinkedlist.h
 * Author: Diogo Gaspar, 99207
 * Description: File containing the doubly linked list's struct, general
 * abstractions, prototypes
 */

/* node struct */
struct Node{
  char *value;
  struct node *prev, *next;
}

typedef struct Node *link;

/* DLL struct */
typedef struct Dlist{
  link head, tail;
}Dlist;

/* general DLL-related function prototypes */
link createNode(char *s);
link insertHead(link head, char *s);
link insertTail(link head, char *s);
link lookupDLL(link head, char *s);
link deleteNode(link head, char *s);
void printDLL(link head);
void freeNode(link x);