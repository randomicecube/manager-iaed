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
  newNode->subDirectories = initializeDLL();
  newNode->prev = NULL;
  newNode->next = NULL;
  newNode->tree = NULL;
  return newNode;
}

int height(struct nodeAVL *x){
  if(x == NULL){
    return 0;
  }
  return x->height;
}

linkAVL max(linkAVL tree){
  for(; tree != NULL && tree->right != NULL; tree = tree->right);
  return tree;
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

linkAVL updateHeight(linkAVL x){
  int hLeft, hRight;
  hLeft = height(x->left->node);
  hRight = height(x->right->node);
  x->node->height = hLeft > hRight ? hLeft + 1: hRight + 1;
  return x;
}

int balanceNode(linkAVL x){
  if(x == NULL || (x->left == NULL && x->right == NULL)) return 0;
  else if(x->left != NULL && x->right != NULL) return height(x->left->node) - height(x->right->node);
  else if (x->left == NULL && x->right != NULL) return height(x->right->node);
  else return height(x->left->node);
}

linkAVL balanceAVL(linkAVL x){
  int balanceFactor;
  if(x == NULL) return x;
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
    x = updateHeight(x);
  }
  return x;
}


linkAVL insertAVL(linkAVL x, struct nodeAVL *newNode){
  if(strcmp("", x->node->dirName) == 0){
    x->node = newNode;
    x->left = initializeAVL();
    x->right = initializeAVL();
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


struct nodeAVL* traverse(int func, char *dir, linkAVL x){
	int comp;
	if(x == NULL){
    if(func == FIND_ERROR){
		  printf(NOT_FOUND);
    }
		return NULL;
	}
	comp = strcmp(x->node->dirName, dir);
	if(comp == 0){
		return x->node;
	}
	else if(comp < 0){
		return traverse(func, dir, x->right);
	}
	else{
		return traverse(func, dir, x->left);
	}
}

linkAVL freeAVL(linkAVL tree){
  if(tree != NULL){
    if(tree->node != NULL) tree = freeNodeAVL(tree);
    if(tree->left != NULL) tree->left = freeAVL(tree->left);
    if(tree->right != NULL) tree->right = freeAVL(tree->right);
    free(tree->left);
    tree->left = NULL;
    free(tree->right);
    tree->right = NULL;
  }
  return tree;
}

linkAVL freeNodeAVL(linkAVL x){
  if(x->node != NULL){
    free(x->node->subDirectories);
    x->node->subDirectories = NULL;
    free(x->node->value);
    x->node->value = NULL;
    free(x->node->dirName);
    x->node->dirName = NULL;
    if(x->node->tree != NULL) freeAVL(x->node->tree);
    free(x->node->tree);
    x->node->tree = NULL;
  }
  return x;
}

linkAVL deleteNodeAVL(struct nodeAVL *toDelete, linkAVL tree){
  linkAVL auxTree;
  struct nodeAVL* auxNode;
  if(tree == NULL){
    return tree;
  }
  else if(strcmp(toDelete->dirName, tree->node->dirName) < 0){
    tree->left = deleteNodeAVL(toDelete, tree->left);
  }
  else if (strcmp(toDelete->dirName, tree->node->dirName) > 0){
    tree->right = deleteNodeAVL(toDelete, tree->right);
  }
  else{
    if(tree->left != NULL && tree->right != NULL){
      auxTree = max(tree->left);
      auxNode = tree->node;
      tree->node = auxTree->node;
      auxTree->node = auxNode;
      tree->left = deleteNodeAVL(auxTree->node, tree->left);
    }
    else{
      auxTree = tree;
      if(tree->left == NULL && tree->right == NULL){
        tree = NULL;
      }
      else if(tree->left == NULL){
        tree = tree->right;
      }
      else{
        tree = tree->left;
      }
      freeNodeAVL(auxTree);
      free(auxTree);
    }
  }
  puts("a");
  tree = balanceAVL(tree);
  return tree;
}

linkAVL initializeAVL(){
  linkAVL newTree = (linkAVL)malloc(sizeof(struct treeAVL));
  struct nodeAVL *newNode = createNodeAVL("", "");
  newTree->left = NULL;
  newTree->right = NULL;
  newTree->node = newNode;
  return newTree;
}