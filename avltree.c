/*
 * File: dlinkedlist.c
 * Author: Diogo Gaspar, 99207
 * Description: File containing the AVL tree's functions and definitions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* initalizes a "fresh" AVL tree */
linkAVL initializeAVL(){
  linkAVL newTree = (linkAVL)malloc(sizeof(struct treeAVL));
  newTree->left = NULL;
  newTree->right = NULL;
  newTree->node = createNodeAVL("", "");
  return newTree;
}

/* initializes a "fresh" AVL tree node */ 
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

/* returns the height of a given node of an AVL tree */
int height(struct nodeAVL *x){
  if(x == NULL){
    return 0;
  }
  return x->height;
}

/* returns the "max" element from a given AVL tree */
linkAVL max(linkAVL tree){
  linkAVL x;
  for(x = tree; x->right != NULL; x = x->right);
  return x;
}

/* left rotation to the AVL tree */
linkAVL rotL(linkAVL node){
  linkAVL x = node->right;
  node->right = x->left;
  x->left = node;
  node = updateHeight(node);
  x = updateHeight(x);
  return x; 
}

/* right rotation to the AVL tree */
linkAVL rotR(linkAVL node){
  linkAVL x = node->left;
  node->left = x->right;
  x->right = node;
  node = updateHeight(node);
  x = updateHeight(x);
  return x; 
}

/* left-right rotation to the AVL tree */
linkAVL rotLR(linkAVL node){
  if(node == NULL){
    return node;
  }
  node->left = rotL(node->left);
  return rotR(node);
}

/* right-left rotation to the AVL tree */
linkAVL rotRL(linkAVL node){
  if(node == NULL){
    return node;
  }
  node->right = rotR(node->right);
  return rotL(node);
}

/* updates the height associated to the node of an AVL tree */
linkAVL updateHeight(linkAVL x){
  int hLeft, hRight;
  if(x->left != NULL) hLeft = height(x->left->node);
  else hLeft = 0;
  if(x->right != NULL) hRight = height(x->right->node);
  else hRight = 0;
  x->node->height = hLeft > hRight ? hLeft + 1: hRight + 1;
  return x;
}

/* returns the balance of a given AVL tree's "head" */
int balanceNode(linkAVL x){
  if(x == NULL || (x->left == NULL && x->right == NULL)) return 0;
  else if(x->left != NULL && x->right != NULL) return height(x->left->node) - height(x->right->node);
  else if (x->left == NULL && x->right != NULL) return height(x->right->node);
  else return height(x->left->node);
}

/* aux function to the AVL tree, balances it */
linkAVL balanceAVL(linkAVL x){
  int balanceFactor;
  if(x == NULL) return x;
  balanceFactor = balanceNode(x);
  if(balanceFactor > 1 && x->left != NULL){
    if(balanceNode(x->left) >= 0) x = rotR(x);
    else x = rotLR(x);
  }
  else if(balanceFactor < -1 && x->right != NULL){
    if(balanceNode(x->right) <= 0) x = rotL(x);
    else x = rotRL(x);
  }
  else{
    x = updateHeight(x);
  }
  return x;
}

/* inserts a node into an AVL tree */
linkAVL insertAVL(linkAVL x, struct nodeAVL *newNode){
  if(x->node == NULL || x->node->dirName == NULL || strcmp("", x->node->dirName) == 0){
    freeNodeAVL(x);
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

/* traverses through an AVL tree, looking for a directory;
if it isn't found AND func is FIND_ERROR, it prints NOT_FOUND */
struct nodeAVL* traverse(int func, char *dir, linkAVL x){
	int comp;
	if(x == NULL || x->node == NULL){
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

/* frees a tree (and the node it points to) */
linkAVL freeAVL(linkAVL tree){
  if(tree != NULL){
    if(tree->node != NULL){
      tree = freeNodeAVL(tree);
    }
    if(tree->left != NULL){
      tree->left = freeAVL(tree->left);
      free(tree->left);
      tree->left = NULL;
    }
    if(tree->right != NULL){
      tree->right = freeAVL(tree->right);
      free(tree->right);
      tree->right = NULL;
    }
  }
  return tree;
}

/* frees a node (and the tree it points to) */
linkAVL freeNodeAVL(linkAVL x){
  if(x->node != NULL){
    if(x->node->tree != NULL){
      x->node->tree = freeAVL(x->node->tree);
      free(x->node->tree);
      x->node->tree = NULL;
    }
    if(x->node->subDirectories != NULL){
      free(x->node->subDirectories);
      x->node->subDirectories = NULL;
    }
    if(x->node->value != NULL){
      free(x->node->value);
      x->node->value = NULL;
    }
    if(x->node->dirName != NULL){
      free(x->node->dirName);
      x->node->dirName = NULL;
    }
    free(x->node);
    x->node = NULL;
  }
  return x;
}

/* deletes a node from the AVL tree */
linkAVL deleteNodeAVL(struct nodeAVL *toDelete, linkAVL tree){
  linkAVL auxTree;
  struct nodeAVL *auxNode;
  if(tree == NULL) return tree;
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
      if(tree->left == NULL && tree->right == NULL) tree = NULL;
      else if(tree->left == NULL) tree = tree->right;
      else tree = tree->left;
      freeAVL(auxTree);
      free(auxTree);
    }
  }
  tree = balanceAVL(tree);
  return tree;
}