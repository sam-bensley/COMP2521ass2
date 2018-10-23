// DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"


// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = strdup(it);
	new->repeats = 0;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList newDLList()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// free up all space associated with list
void freeDLList(DLList L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev->value);
		free(prev);
	}
	free(L);
}

// trim off \n from strings (private function)
// this is needed for getDLList() because of fgets()
// alternatively, we could use the evil gets() function
/*
static char *trim(char *s)
{
	int end = strlen(s)-1;
	if (s[end] == '\n') s[end] = '\0';
	return s;
}
*/
// display list to file, one item per line
// assumes that the file is open for writing
void putDLList(FILE *out, DLList L)
{
	assert(out != NULL); assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next)
		fprintf(out,"%s with %d attempted repeats\n",curr->value, curr->repeats);
}

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList L, char *it)
{
	assert(L != NULL);

	//check for dups
	DLListNode *curr = L->first;
	while(curr != NULL){
		if(strcmp(curr->value, it) == 0) {curr->repeats++; return;}
		curr = curr->next;
	}

    DLListNode *new = newDLListNode(it);

	//CASE FOR IF LIST IS EMPTY
	if(L->nitems == 0){
	
	    L->first = new;
	    L->last = new;
		new->num = 0;
	    L->nitems++;
	    return;
	}
	   
	new->next = L->last->next;
	new->prev = L->last;
	new->num = L->nitems + 1; 

	L->last->next = new;

	L->last = new;    

	L->nitems++;
	
}

int GetIndexofItem(DLList list, char *item){
	DLListNode *curr = list->first;
	while(curr != NULL){

		if(strcmp(item, curr->value) == 0){
			return curr->num;
		}

		curr = curr->next;
	}
	return -1;
}

// return number of elements in a list
int DLListLength(DLList L)
{
	return (L->nitems);
}

// is the list empty?
int DLListIsEmpty(DLList L)
{
	return (L->nitems == 0);
}
