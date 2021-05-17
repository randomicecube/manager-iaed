/*
 * File: dlinkedlist.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing the AVL tree's functions and definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

struct nodeAVL* createNodeAVL(char *s, char *name){
  struct nodeAVL* newNode = (struct nodeAVL *)malloc(sizeof(struct nodeAVL));
  Dlist *auxList;
  if(strcmp("", s) != 0){
    newNode->value = (char*)malloc(sizeof(char)*(strlen(s)+1));
  }
  else{
    newNode->value = (char*)malloc(sizeof(char)*(MEM_AMOUNT));
  }
  if(strcmp("", name) != 0){
    newNode->dirName = (char*)malloc(sizeof(char)*(strlen(name)+1));
  }
  else{
    newNode->dirName = (char*)malloc(sizeof(char)*(MEM_AMOUNT));
  }
  strcpy(newNode->value, s);
  strcpy(newNode->dirName, name);
  newNode->height = 1;
  auxList = initializeDLL();
  newNode->subDirectories = auxList;
  return newNode;
}

int height(struct nodeAVL *x){
  if(x == NULL){
    return 0;
  }
  return x->height;
}

linkAVL rotL(linkAVL node){
  linkAVL x = node->right;
  node->right = x->left;
  x->left = node;
  updateHeight(node);
  updateHeight(x);
  return x; 
}

linkAVL rotR(linkAVL node){
  linkAVL x = node->left;
  node->left = x->right;
  x->right = node;
  updateHeight(node);
  updateHeight(x);
  return x; 
}

linkAVL rotLR(linkAVL node){
  if(node == NULL){
    return node;
  }
  node->left = rotL(node->left);
  return rotR(node);
}

linkAVL rotRL(linkAVL node){
  if(node == NULL){
    return node;
  }
  node->right = rotR(node->right);
  return rotL(node);
}

void updateHeight(linkAVL x){
  int hLeft = height(x->left->node), hRight = height(x->right->node);
  x->node->height = hLeft > hRight ? hLeft + 1: hRight + 1;
  return;
}

int balanceNode(linkAVL x){
  if(x == NULL){
    return 0;
  }
  if(x->left->node == NULL && x->right->node != NULL){
    return height(x->right->node);
  }
  if(x->left->node != NULL && x->right->node == NULL){
    return height(x->left->node);
  }
  else if(x->left->node == NULL && x->right->node == NULL){
    return 0;
  }
  return height(x->left->node) - height(x->right->node);
}

linkAVL balanceAVL(linkAVL x){
  int balanceFactor;
  if(x == NULL){
    return x;
  }
  balanceFactor = balanceNode(x);
  if(balanceFactor > 1){
    if(balanceNode(x->left) >= 0){
      x = rotR(x);
    }
    else{
      x = rotLR(x);
    }
  }
  else if(balanceFactor < -1){
    if(balanceNode(x->right) <= 0){
      x = rotL(x);
    }
    else{
      x = rotRL(x);
    }
  }
  else{
    updateHeight(x);
  }
  return x;
}


linkAVL insertAVL(linkAVL x, struct nodeAVL *newNode){
  /*if(x == NULL){
    x = initializeAVL();
  }
  if(x->node == NULL){
    x->node = createNodeAVL("", "");
    x->node->tree = initializeAVL();
  }*/
  if(strcmp("", x->node->dirName) == 0 || strcmp(newNode->dirName, x->node->dirName) == 0){
    x->node = newNode;
    return x;
  }
  if(strcmp(x->node->dirName, newNode->dirName) > 0){
    x->left = insertAVL(x->left, newNode);
  }
  else{
    x->right = insertAVL(x->right, newNode);
  }
  x = balanceAVL(x);
  return x;
}

/*
void freeAVL(linkAVL node){
  if(node->left != NULL){
  freeAVL(node->left);
  freeAVL(node->right);
  freeNodeAVL(node);
}

void freeNodeAVL(struct nodeAVL *node){
  if(node == NULL){
    return;
  }
  freeNodeAVL(node->right);
  freeNodeAVL(node->left);
  free(node->value);
  free(node->dirName);
  freeDLL(subDirectories);
  return;
} */

linkAVL initializeAVL(){
  linkAVL newTree = (linkAVL)malloc(sizeof(struct treeAVL));
  struct nodeAVL *newNode = createNodeAVL("", "");
  newTree->left = NULL;
  newTree->right = NULL;
  newTree->node = newNode;
  return newTree;
}