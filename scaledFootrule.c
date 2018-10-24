// Part 3
// WE USE BRUTE FORCE METHOD
#include "DLList.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "readData.c"


typedef struct originalRank {
    char *originalUrl;
    int originalRank;
} originalRank;

void permute(int *a, int l, int r, int*perms);
void swap(int *x, int *y);
float weightedScaledFootrule (originalRank ranks[], int totalNumUrls, int setNumUrls);
void populateOriginalRank (originalRank ranks[], DLList originalList, int totalNumUrls, int setNumUrls);
void iterateOriginalRank (originalRank ranks[], int numUrls);
int factorial(int f);
int *permuations(int size);


int permsIndex = 0;

int main(int argc, char *argv[]){

    // PLAN
    // we need to know number of rank lists (from argc)
    // the union of T1, T2, T3... 
    // The cardinality of the union
    // perform algorthm on one permuation
    // save this result and performa again on next permutation
    // save the minimum WPC and return the permutation

    //get args
    if(argc == 1){
        printf("Usage: ./scaledFootrule [file].txt [file].txt ...\n");
        exit(1);
    }

    int size = 0;

    int i;
    for(i = 1; i < argc; i++){
        DLList list = getCollectionOfUrl(argv[i]);
        size += list->nitems;
    }

    originalRank ranksAndUrls[size][argc-1];
    
    for(i = 1; i < argc; i++){
        DLList list = getCollectionOfUrl(argv[i]);
        populateOriginalRank(ranksAndUrls[i-1], list, size, list->nitems);
    }
    
    // int *perms = permuations(size);


    // int biggersize = factorial(size) * size;
    // for(i = 0; i < biggersize; i++){
    //      if(i%size == 0) putchar('\n');
    //      printf("%d", perms[i]); 
    // }
    // putchar('\n');
    // fucntion that returns the scaled-footrule distance for a particular
    // list with a particular possible permuation. 

    // originalRank temp = ranksAndUrls[2][1];
    // ranksAndUrls[2][1] = ranksAndUrls[2][4];
    // ranksAndUrls[2][4] = temp;


    printf("%f\n", weightedScaledFootrule(ranksAndUrls[1], size, 4) + weightedScaledFootrule(ranksAndUrls[0], size, 5));



    return 0;
}
// original ranking of urls (list)
// current permuations ie {1,4,2,6,5,3}
// size of rankings (eg size of T1)
// size of union 
float weightedScaledFootrule (originalRank ranks[], int totalNumUrls, int setNumUrls)
{
    // C is in order: url1, url2, url3...
    float weight = 0;

    int i;
    for (i = 0; i < setNumUrls; i++) {
        //printf("%f", weight);
        if (ranks[i].originalRank == -1) continue;
        weight += fabsf(((float)ranks[i].originalRank/(float)setNumUrls) - ((float)(i+1)/(float)totalNumUrls));
        
    }
    
    return weight;   
}

void populateOriginalRank (originalRank ranks[], DLList originalList, int totalNumUrls, int setNumUrls)
{
    // populate ranks[] with urls and their original rankings
    DLListNode *curr = originalList->first;
    while (curr != NULL) {
        ranks[curr->num].originalRank = curr->num + 1;
        ranks[curr->num].originalUrl = strdup(curr->value);
        curr=curr->next;
    }

    // populate remaining array with NULLS and -1
    if (setNumUrls < totalNumUrls){
        int i;
        for (i = setNumUrls; i < totalNumUrls; i++) {
            ranks[i].originalRank = -1;
            ranks[i].originalUrl = NULL;
        }
    }
}

void iterateOriginalRank (originalRank ranks[], int numUrls)
{




}

int *permuations(int size){

    int possiblePerms = factorial(size);
    int *perms = malloc(sizeof(int) * possiblePerms * size);

    int str[size];
    int i;
    for(i = 0; i < size; i++){
        str[i] = i;
    }
    int n = size; 
    
    permute(str, 0, n-1, perms); 
    
    

    return perms;
}

int factorial(int f)
{
    if ( f == 0 ) 
        return 1;
    return(f * factorial(f - 1));
}

void swap(int *x, int *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
/* Function to print permutations of string 
   This function takes three parameters: 
   1. String 
   2. Starting index of the string 
   3. Ending index of the string. */
void permute(int *a, int l, int r, int*perms) 
{ 
   int i; 
   if (l == r){
    //  int j;
    //  for(j = 0; j <= r; j++){
    //      printf("%d", a[j]);
    //  }
    //  putchar('\n');
    //printf("HEY %d\n", permsIndex);
        int j ;
      for(j = 0; j <= r; j++){
          perms[permsIndex] = a[j];
          permsIndex++;
      }
        
    }
   else
   { 
       for (i = l; i <= r; i++) 
       { 
          swap((a+l), (a+i)); 
          permute(a, l+1, r, perms); 
          swap((a+l), (a+i)); //backtrack 
       } 
   } 
} 
  







