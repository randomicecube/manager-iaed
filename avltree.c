/*
 * File: dlinkedlist.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing the AVL tree's functions and definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

linkAVL createNodeAVL(char *s, char *name){
  linkAVL newNode = (linkAVL)malloc(sizeof(struct nodeAVL));
  Dlist auxList;
  newNode->value = (char*)malloc(sizeof(char)*(strlen(s)+1));
  newNode->dirName = (char*)malloc(sizeof(char)*(strlen(name)+1));
  strcpy(newNode->value, s);
  strcpy(newNode->dirName, name)
  newNode->height = 1;
  newNode->left = NULL;
  newNode->right = NULL;
  auxList = initializeDLL();
  newNode->subDirectories = auxList;
  return;
}

/* aux function to check the max value between 2 ints, used in rotations */
int maxAuxAVL(int h1, int h2){
  if(h1 >= h2){
    return h1;
  }
  return h2;
}

/* returns the height of the AVL tree with node as its root */
int heightNodeAVL(linkAVL node){
  if(node == NULL){
    return 0;
  }
  return node->height;
} 

/* returns the current balance of the AVL tree with node as its root */
int treeBalanceAVL(linkAVL node){
  if(node == NULL){
    return 0;
  }
  return height(node->left) - height(node->right);
}

/* performs a left-rotation to the AVL */
linkAVL rotlAVL(linkAVL node){ /* node is the current root */
  linkAVL auxRight = node->right;
  linkAVL auxLeft = auxRight->left;
  auxRight->left = node;
  node->right = auxLeft;
  auxRight->height = maxAuxAVL(height(auxRight->right), height(auxRight->left)) + 1;
  node->height = maxAuxAVL(height(node->right), height(node->left)) + 1;  
  return auxRight; /* auxRight is the new root of the tree*/
}

/* performs a right-rotation to the AVL */
linkAVL rotrAVL(linkAVL node){ /* node is the current root */
  linkAVL auxLeft = node->left;
  linkAVL auxRight = auxLeft->right;
  auxLeft->right = node;
  node->left = auxRight;
  auxLeft->height = maxAuxAVL(height(auxLeft->right), height(auxLeft->left)) + 1;
  node->height = maxAuxAVL(height(node->right), height(node->left)) + 1;  
  return auxLeft; /* auxLeft is the new root of the tree*/
}

/* inserts a node to an AVL tree, given its value and dirName */
linkAVL insertNodeAVL(linkAVL node, char* s, char* name){ /* node is the current root */
  int currBalance;
  if(node == NULL){
    return createNodeAVL(s, name);
  }
  if(strcmp(node->dirName, name) < 0){
    node->right = insertNodeAVL(node->right, s, name);
  }
  else if(strcmp(node->dirName, name) > 0){
    node->left = insertNodeAVL(node->left, s, name);
  }
  else{
    return node;
  }

  node->height = max(height(node->right), height(node->left));
  currBalance = treeBalanceAVL(node);

  if(currBalance > 1 && strcmp(node->left->dirName, name) > 0){
    return rotrAVL(node);
  }
  if(currBalance > 1 && strcmp(node->left->dirName, name) < 0){
    node->left = rotlAVL(node->left);
    return rotrAVL(node);
  }
  if(currBalance < -1 && strcmp(node->right->dirName, name) < 0){
    return rotlAVL(node);
  }
  if(currBalance < -1 && strcmp(node->right->dirName, name) > 0){
    node->right = rotrAVL(node->right);
    return rotlAVL(node);
  }
  return node;
}

void freeNodeAVL(link node){
  if(node == NULL){
    return;
  }
  freeNodeAVL(node->right);
  freeNodeAVL(node->left);
  free(node->value);
  free(node->dirName);
  freeDLL(subDirectories);
  return;
}

