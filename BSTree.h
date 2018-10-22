// BSTree.h ... interface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

#include "DLList.h"

typedef struct BSTNode {
	DLList urlList;
	char *value;
	struct BSTNode *left, *right;
} BSTNode;

typedef struct BSTNode *BSTLink;

typedef struct BSTNode *BSTree;





// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);
// display a BSTree
void showBSTree(BSTree);
// display BSTree root node
void showBSTreeNode(BSTree);

// print values in infix order
void BSTreeInfix(BSTree, FILE*);
// print values in prefix order
void BSTreePrefix(BSTree);
// print values in postfix order
void BSTreePostfix(BSTree);
// print values in level-order
void BSTreeLevelOrder(BSTree);

// count #nodes in BSTree
int BSTreeNumNodes(BSTree);
// count #leaves in BSTree
int BSTreeNumLeaves(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, char *val, char *url);
// check whether a value is in a BSTree
BSTree BSTreeFind(BSTree, char*);
// delete a value from a BSTree
BSTree BSTreeDelete(BSTree, char*);

// checks if str1 is lower than str2 in alphabetic rank
int isLowerAlphabeticalOrder(char*, char*);

#endif