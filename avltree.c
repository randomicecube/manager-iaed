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
  newNode->value = (char*)malloc(sizeof(char)*(strlen(s)+1));
  newNode->dirName = (char*)malloc(sizeof(char)*(strlen(name)+1));
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
  return height(x->left->node) - height(x->right->node);
}

linkAVL balanceAVL(linkAVL node){
  int balanceFactor;
  if(node == NULL){
    return node;
  }
  balanceFactor = balanceNode(node);
  if(balanceFactor > 1){
    if(balanceNode(node->left) >= 0){
      node = rotR(node);
    }
    else{
      node = rotLR(node);
    }
  }
  else if(balanceFactor < -1){
    if(balanceNode(node->right) <= 0){
      node = rotL(node);
    }
    else{
      node = rotRL(node);
    }
  }
  else{
    updateHeight(node);
  }
  return node;
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