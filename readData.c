#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DLList.h"
#include "graph.h"
#include "BSTree.h"
#include <ctype.h>

#define TRUE 1
#define FALSE !TRUE

int isUrl(char *url);
void trim(char *str);
int removeCharFromEnd (char ch);

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

// opens "collection.txt" and puts urls into DLList
DLList getCollectionOfUrl(char*file){
    FILE *collection = fopen(file, "r");
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

BSTree getTree(DLList list)
{
    BSTree tree = newBSTree();
    // loop through DLList
    DLListNode *curr = list->first;
    while(curr != NULL){
        // temp to hold url text file        
        char temp[BUFSIZ];
        strcpy(temp, curr->value);
        strcat(temp, ".txt");                
        FILE *urlFile = fopen(temp, "r");
        // loop to scan in text body of url
        char body[BUFSIZ];
        int section2Flag = FALSE;
        while(fscanf(urlFile, "%s", body) == 1){
            // do not scan in "Section-2"
            if (strcmp(body, "Section-2") == 0) { ;section2Flag = TRUE; continue; } 
            // only add if in Section-2
            if(section2Flag == TRUE){
                if (strcmp(body, "#end") == 0) break;
                trim(body);
                tree = BSTreeInsert(tree, body, curr->value);           
            } 
        }
        curr = curr->next;
    }

    return tree;
}

// Retrieves body of url and puts into termCountTable
DLList getTermCountTable (char *url)
{
    // loop to create term count tables
    DLList termCountTable = newDLList();
    // temp to hold url text file        
    char temp[BUFSIZ];
    strcpy(temp, url);
    strcat(temp, ".txt");                
    FILE *urlFile = fopen(temp, "r");
    // loop to scan in text body of url
    char body[BUFSIZ];
    int section2Flag = FALSE;
    while(fscanf(urlFile, "%s", body) == 1){
        // do not scan in "Section-2"
        if (strcmp(body, "Section-2") == 0) { ;section2Flag = TRUE; continue; } 
        // only add if in Section-2
        if(section2Flag == TRUE){
            if (strcmp(body, "#end") == 0) break;
            trim(body);
            DLListAfter (termCountTable, body);         
        } 
    }
    return termCountTable;
}


// remove leading/trailing spaces from a string as
// well as punctuation marks and turns to lower case
void trim(char *str)
{
   int first, last;
   first = 0;
   // only remove from start if a space
   while (isspace(str[first])) first++;
   last  = strlen(str)-1;
   while (removeCharFromEnd(str[last])) last--;
   int i, j = 0;
   for (i = first; i <= last; i++) str[j++] = tolower(str[i]);
   str[j] = '\0';
}
// recognises appropriate characters
// to remove from end of the word
int removeCharFromEnd (char ch)
{
    if (isspace(ch)) return TRUE;    
    if (ch == '.' || ch == ',' || ch == ';' || ch == '?' || ch == '\n') return TRUE;

    return FALSE;    
}