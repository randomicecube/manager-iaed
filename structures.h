/*
 * File: dlinkedlist.h
 * Author: Diogo Gaspar, 99207
 * Description: File containing the doubly linked list's and AVL tree's 
 * structs, general abstractions, prototypes
 */

/* ---------------------------------STRUCTS--------------------------------- */

/* DLL node struct */
struct nodeDLL{
  char *value;
  struct nodeDLL *prev, *next;
};

typedef struct nodeDLL* link;

/* DLL struct */
typedef struct Dlist{
  link head, tail;
}Dlist;

/* AVL node struct */
struct nodeAVL{
  struct nodeAVL *left, *right;
  char *value, *dirName;
  int height;
  Dlist subDirectories; /* DLL with a node's subdirectories ordered by creation */
};

typedef struct nodeAVL* linkAVL;

/* --------------------------------PROTOTYPES------------------------------- */

/* general DLL-related function prototypes */
link createNodeDLL(char *s);
link insertTailDLL(link head, link tail, char *s);
link lookupDLL(link head, char *s);
link deleteNodeDLL(link head, char *s);
void printDLL(link head);
void freeNodeDLL(link x);
void freeDLL(link head);
link initializeDLL();

/* general AVL-tree-related function prototypes */