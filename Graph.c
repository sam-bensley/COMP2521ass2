// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

#define FALSE 0
#define TRUE !FALSE

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);
	  	
	// Initialise array to hold if a city has been visited
	int visited[g->nV]; // should be 30 in length
	int i; for (i = 0; i < g->nV; i++) visited[i] = -1;
	
	// set src to be seen
	visited[src] = src;
	
	// Variable to represent once dest has been found
	int destFound = FALSE;

	Queue q = newQueue();
    QueueJoin(q, src);
    while (!QueueIsEmpty(q) && !destFound)
    {
        // Grab next in queue
        Vertex curr = QueueLeave(q);
        
        // Check this isn't the dest
        if (curr == dest){ destFound = TRUE; break;}
        
        // Breadth search the graph 
        Vertex i;
        for (i = 0; i < g->nV; i++)
        {
            // Check this can join to curr
            if (!g->edges[curr][i]) continue;
            // Check this has not been visited
            if (visited[i] != -1) continue;
            // Check the edge weight is less than max
            if (g->edges[curr][i] > max) continue;
            
            // If execution reaches here, we can add this to path
            visited[i] = curr;
            
            // Add this to the Queue, mark as seen
            QueueJoin(q, i);            
        }                                         
    }
    
    dropQueue(q);
    
    //printf("RUN\n\n\n");
    // If dest has been found, update path array
    if (!destFound) return 0;
    
	int numVertices = 0;
	i = dest;	
    while (i != src)    
    {
        path[numVertices] = i;    
        numVertices++;
        
        i = visited[i];
    }
    
    path[numVertices] = src;
    numVertices++;
    
    // Reverse array
    reverse(path, 0, numVertices - 1);
       	
	return numVertices; 
}

void reverse(int arr[], int start, int end) 
{ 
    while (start < end) 
    { 
        int temp = arr[start];  
        arr[start] = arr[end]; 
        arr[end] = temp; 
        start++; 
        end--; 
    }  
}

/*
void reverse(int arr[], int length)
{
    int temp;
    int i;
    for (i = 0; i < length; i++)
    {
        temp = arr[i];
        arr[i] = arr[length - i];
        arr[length - i] = temp;        
    }
}
*/
