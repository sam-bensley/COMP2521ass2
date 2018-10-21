#include <stdio.h>
#include <math.h>
#include "readData.c"
#include "DLList.h"
#include "graph.h"

int main(){

        // read web pages from collection.txt
    DLList collection = getCollection();
    Graph graph = getGraph(collection);
    showGraph(graph, 0);

    printf("Outgoing Links: for url23 %d\n", outgoingLinks(graph, "url23"));
    printf("Incoming Links: for url23 %d\n", ingoingLinks(graph, "url23"));

}