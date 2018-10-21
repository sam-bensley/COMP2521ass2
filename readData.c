#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    fclose(collection);
    return newList;
}

Graph getGraph(DLList list){
    Graph g = newGraph(DLListLength(list));
    DLListNode *curr = list->first;

    while(curr != NULL){
        //insert edgese here!
        FILE *urlFile = fopen(curr->value, "r");
        char url[BUFSIZ];
        int primIndex = GetIndexofItem(list, curr->value);
        while(fscanf(urlFile, "%s", url) == 1){
            int num;
            if(strcmp(url, "#end") != 0 && sscanf(url, "url%d", num)){
                insertEdge(g, primIndex, GetIndexofItem(list, url), 1);                
            }
            else{
                break;
            }

        }
        curr = curr->next;
    }
    return g;

}