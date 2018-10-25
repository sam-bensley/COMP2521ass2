
#ifndef READDATA_H
#define READDATA_H

#include "graph.h"
#include "BSTree.h"
#include "DLList.h"

#define TRUE 1
#define FALSE !TRUE

int isUrl(char *url);
void trim(char *str);
int removeCharFromEnd (char ch);
DLList getCollection();
DLList getCollectionOfUrl(char*file);
Graph getGraph(DLList list);
BSTree getTree(DLList list);
DLList getTermCountTable (char *url);

#endif