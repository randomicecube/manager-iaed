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

int height(linkAVL node){
  if(node == NULL){
    return 0;
  }
  return node->height;
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

void updateHeight(linkAVL node){
  int hLeft = height(node->left), hRight = height(node->right);
  node->height = hLeft > hRight ? hLeft + 1; hRIght + 1;
  return;
}

int balanceNode(linkAVL node){
  if(node == NULL){
    return 0;
  }
  return height(node->left) - height(node->right);
}

linkAVL balanceAVL(linkAVL node){
  int balanceFactor, hLeft, hRight;
  if(h == NULL){
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

linkAVL insertAVL(linkAVL node, char*s, char*name){
  if(node == NULL){
    return createNodeAVL(s, name);
  }
  if(strcmp(name, node->dirName) < 0){
    node->left = insertAVL(node->left, s, name);
  }
  else{
    node->right = insertAVL(node->right, s, name);
  }
  node = balanceAVL(node);
  return node;
}

/* --- */
linkAVL deleteAVL

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

