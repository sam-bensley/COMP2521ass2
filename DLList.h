// DLList.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, August 2014

#ifndef DLLIST_H
#define DLLIST_H

#include <stdio.h>
#include "DLList.h"

typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	int num;
	int repeats;
	struct DLListNode *prev;
	               // pointer previous node in list
	struct DLListNode *next;
	               // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
	int  nitems;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLListRep;


// External view of DLList
// Implementation given in DLList.c
// Implements a DLList of strings (i.e. items are strings)

typedef struct DLListRep *DLList;

// create a new empty DLList
DLList newDLList();

// free up all space associated with list
void freeDLList(DLList);

// display list to file, one item per line
// assumes that the file is open for writing
void putDLList(FILE *, DLList);

int GetIndexofItem(DLList list, char *item);

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList, char *);

// return number of elements in a list
int DLListLength(DLList);

// is the list empty?
int DLListIsEmpty(DLList);

#endif