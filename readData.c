#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DLList.h"
#include "graph.h"

#define TRUE 1
#define FALSE !TRUE

int isUrl(char *url);

// opens "collection.txt" and puts urls into DLList
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

// determines if string is of "urlXX" format
int isUrl(char *url){
    // if first 3 characters are "url"
    return (strncmp(url, "url", 3) == 0) ? TRUE : FALSE;
}

// receives a DLList of URLS and converts into graph ADT  
Graph getGraph(DLList list){
    Graph g = newGraph(DLListLength(list));
    DLListNode *curr = list->first;
    while(curr != NULL){
        // temp to hold url text file
        char temp[BUFSIZ];
        strcpy(temp, curr->value);
        strcat(temp, ".txt");                
        FILE *urlFile = fopen(temp, "r");
        // loop to scan in urls from urlXX.txt and add to graph
        char url[BUFSIZ];
        while(fscanf(urlFile, "%s", url) == 1){
            // check for url format and parallel edge            
            if(isUrl(url) && strcmp(curr->value, url) != 0){
                addEdge(g, curr->value, url); 
            // break once the section end has been reached           
            } else if (strcmp(url, "#end") == 0){
                break;
            }
        }
        curr = curr->next;
    }
    return g;
}