#include <stdlib.h>
#include <stdio.h>
#include "DLList.h"
#include "Graph.h"


int main(int argc, char *argv[]){
    return 0;

}

DLList getCollection(){
    FILE *collection = fopen("collection.txt", "r");
    char url[BUFSIZ];
    DLList newList = newDLList();
    while(fscanf(collection, "%s", url) == 1){
        DLListAfter(newList, url);
    }
    return newList;
}

Graph getGraph(DLList list){
    Graph g = newGraph(DLListLength(list));
    DLListNode *curr = list->first;
    while(curr != NULL){
        //insert edgese here!

    }
    return newGraph;

}