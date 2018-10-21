// Part A

#include <stdio.h>
#include <math.h>
#include "readData.c"
#include "DLList.h"
#include "graph.h"


#define PAGERANKARGS 4

typedef struct urlRanks {
    char *url;
    int outgoing;   // number of outgoing urls
    float wPR;      // weighted page rank of url
} urlRanks;

void PageRankW(Graph g, urlRanks *ranks[], int urlRanksSize, float d, float diffPR, int maxIterations);
float pageRankRec (Graph g, urlRanks *ranks[], int urlRanksSize, float d, int iteration, urlRanks *curr);

float Wout(Graph graph, int N, char *v, char *u);
float Win(Graph graph, int N, char *u, char *p);

void sortDescending(urlRanks *ranks[], int urlRanksSize);

int main(int argc, char *args[]){

    // check the arguments
    if(argc != PAGERANKARGS){
        printf("Incorrect args:\n");
        printf("USAGE: ./pageRank d diffPR maxIterations\n");
        exit(1);
    }
    
    // read web pages from collection.txt
    DLList collection = getCollection();
    Graph graph = getGraph(collection);

    //create array of urls and ranks
    urlRanks* ranks[collection->nitems];
    
    DLListNode *curr = collection->first;
    int i = 0;        
    while(curr  != NULL){
        urlRanks *rank = malloc(sizeof(urlRanks));        
        rank->url = strdup(curr->value);
        //DETERMINE OUTGOING LINKS FUNCTION
        rank->outgoing = outgoingLinks(graph, curr->value);
        rank->wPR = 0;
        ranks[i] = rank;

        i++;                                                        
        curr = curr->next;                                            
    } 

    // extract parameters from stdin and feed into PageRankW
    float d;
    sscanf(args[1], "%f", &d);
    float diffPR;
    sscanf(args[2], "%f", &diffPR);
    int maxIterations;
    sscanf(args[3], "%d", &maxIterations);      
    PageRankW(graph, ranks, collection->nitems, d, diffPR, maxIterations);
    
    //sort in decending order
    sortDescending(ranks, collection->nitems);
    
    for (i = 0; i < collection->nitems; i++) {
        
        //PRINT OUT TO THE THING
        
        printf("%.7f     %d\n", ranks[i]->wPR, ranks[i]->outgoing);
    }
    

    return 0;
}

// sorts *ranks[] in descending order using quicksort algorithm
void sortDescending(urlRanks *ranks[], int urlRanksSize)
{
    int i = 0;
    for (i = 0; i < urlRanksSize; i++) {
        int swapped = FALSE;
        int j = 0;
        for (j = 0; j < urlRanksSize - 1; j++) {
            if (ranks[j]->wPR < ranks[j + 1]->wPR){
                urlRanks *temp = ranks[j];
                ranks[j] = ranks[j+1];
                ranks[j+1] =  temp;
                swapped = TRUE;
            }                                    
        }
        // if no elements were swapped, quick sort is complete
        if (swapped == FALSE) break;                            
    }

}

void PageRankW(Graph g, urlRanks *ranks[], int urlRanksSize, float d, float diffPR, int maxIterations)
{
    // loop through all url ranks for this current iteration
    int rankIndex = 0;
    for (rankIndex = 0; rankIndex < urlRanksSize; rankIndex++) {       
        // printf("ranks[rankIndex] = %f\n", ranks[rankIndex]->wPR);
        
        // loop to iterate and calculate wPR 
        int iteration = 0;  
        float diff = diffPR;
        while (iteration < maxIterations && diff >= diffPR){
        
            ranks[rankIndex]->wPR = pageRankRec (g, ranks, urlRanksSize, d, iteration + 1, ranks[rankIndex]);
            
            // --------------------------THIS CAUSE WEIGHTED TO BE SLIGHTLY OFF ---------------------------
            // recalculate diff
            int i;
            for (i = 0; i < urlRanksSize; i++){
                diff = fabsf((pageRankRec(g, ranks, urlRanksSize, d, iteration + 1, ranks[i])) - 
                        (pageRankRec(g, ranks, urlRanksSize, d, iteration, ranks[i])));            
            }   
            // ---------------------------------------------------------------------------------------------

            iteration++;              
        }
    }    
}

// recursion calc for pagerank
float pageRankRec (Graph g, urlRanks *ranks[], int urlRanksSize, float d, int iteration, urlRanks *curr)
{
    // base case
    if (iteration == 0) return (float)((float)1 / (float)urlRanksSize);
    
    // first sum of algorithm
    float sum1 = (((float)1 - d)) / ((float)(urlRanksSize));
    
    // second sum of algorith
    //
    // p(i) = curr->url
    // p(j) = ranks[i]->url (if isConnected)
    float sum2 = 0;
    int i = 0;
    for (i = 0; i < urlRanksSize; i++) {      
          
        if (isConnected(g, ranks[i]->url, curr->url)){
            // printf("ranks[i] url is: %s\n", ranks[i]->url); 
            sum2 += pageRankRec(g, ranks, urlRanksSize, d, iteration - 1, ranks[i]) *
                    Win(g, urlRanksSize, ranks[i]->url, curr->url) *
                    Wout (g, urlRanksSize, ranks[i]->url, curr->url);
        }
    }           
    return sum1 + d * sum2;
}


float Wout(Graph graph, int N, char *v, char *u){
    float outlinksU = outgoingLinks(graph, u);
    if(outlinksU == 0) outlinksU = 0.5;
    int Vindex = vertexID(v, graph->vertex, N);
    float totalOut = 0.0;

    int i;
    for(i = 0; i < N; i++){
        if(graph->edges[Vindex][i] == 1){
            float og = outgoingLinksInt(graph, i);
            if (og == 0) og = 0.5;
            totalOut += og;

		}
    }  

    return (float)(outlinksU/totalOut);
}

float Win(Graph graph, int N, char *v, char *u){
    int inlinksU = ingoingLinks(graph, u);
    int Vindex = vertexID(v, graph->vertex, N);
    int totalIn = 0;        
    int i;
    for(i = 0; i < N; i++){
        if(graph->edges[Vindex][i] == 1){
            totalIn += ingoingLinksInt(graph, i);            
		}
    }

    return (float)((float)inlinksU/(float)totalIn);
}



