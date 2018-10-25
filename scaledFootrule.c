// Part 3
// WE USE BRUTE FORCE METHOD
#include "DLList.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"


#define MAXURLS 100
#define MAXURLLEN 20

void permute(int *a, int l, int r, int*perms);
void swap(int *x, int *y);
float weightedScaledFootrule (DLList c, int *p, DLList t);
int factorial(int f);
int *permuations(int size);
DLList getUnion (char *files[], int numFiles);
void populatePArray(int p[], int *perms, int index, int sizeOfPerms);
void cpyarray(int dest[], int src[], int size);

int permsIndex = 0;

int main(int argc, char *argv[]){


    //get args
    if(argc == 1){
        printf("Usage: ./scaledFootrule [file].txt [file].txt ...\n");
        exit(1);
    }

    DLList theUnion = getUnion(argv, argc - 1);

    int size = theUnion->nitems;

    DLList allLists[argc-1]; 

    // retrieves urls from files and populates array of originalRanks for each file
    int i;
    for(i = 1; i < argc; i++){
        DLList list = getCollectionOfUrl(argv[i]);
        allLists[i-1] = list;

    }

    // create an array of all the possible permutations
    // can only do up to size = 11 because so inefficient

    float min = 10000;

    int bestP[size];

    int *perms = permuations(size);
   
    int possiblePerms = factorial(size);
    
    for(i = 0; i < possiblePerms; i++){
        int j;
        float scaledFootRule = 0;

        
        int p[size];

        for(j = 0; j < argc-1; j++){

            populatePArray(p, perms, i, size);
            scaledFootRule += weightedScaledFootrule(theUnion, p, allLists[j]);    
          
        }
        
        if(scaledFootRule < min){
            min = scaledFootRule;
            cpyarray(bestP, p, size);

        }
        
        //printf("%f\n", scaledFootRule);

    }   

    printf("\nMin is %f\n", min);
    printf("with order:\n");
    for(i = 0; i < size; i++){
        
        DLListNode *curr = theUnion->first;
        while(curr != NULL){
            if(curr->num-1 == bestP[i]){
                printf("%s\n", curr->value);
            }
            curr = curr->next;
        } 

    }
    putchar('\n');


    return 0;
}

void cpyarray(int dest[], int src[], int size){
    int i;
    for(i =0; i < size; i++){
        dest[i] = src[i]; 
    }

}


void populatePArray(int p[], int *perms, int index, int sizeOfPerms){
    int i;
    for(i = 0; i < sizeOfPerms; i++){
        //int temp = perms[index*sizeOfPerms + i];
        p[i] = perms[index*sizeOfPerms + i];
    }
}



float weightedScaledFootrule (DLList c, int *p, DLList t)
{
    // C is in order: url1, url2, url3...

    float weight = 0;
    DLListNode *curr = c->first;
    while(curr != NULL){
        
        int tc = -1;
        
        //printf("%s\n", curr->value);

        DLListNode *newCurr = t->first;

        while(newCurr != NULL){
            //printf("P%sP and P%sP\n", curr->value, newCurr->value);

            if(strcmp(curr->value, newCurr->value) == 0){
                
                tc = newCurr->num;
                break;
            }

            newCurr = newCurr->next;
        }
        float numeratorOne = (float)tc;      
        float denomanatorOne = (float)t->nitems;
        float numeratorTwo = (float)p[curr->num-1] +1;
        float denomanatorTwo = (float)c->nitems;
        //printf("%.7f/%.7f - %.7f/%.7f\n", numeratorOne, denomanatorOne, numeratorTwo, denomanatorTwo);

        if(tc != -1){
            weight += fabsf((numeratorOne / denomanatorOne) - (numeratorTwo / denomanatorTwo));
        }
        //weight += fabsf((((float)tc)/((float)t->nitems)) - (((float)p[curr->num-1])/((float)c->nitems)));

        curr = curr->next;
    }

    return weight;

}


// have to represent as a singular array
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

DLList getUnion (char *files[], int numFiles) {

    // DLList to hold urls in the files (this does not add repeats)
    // so is really useful for determining the union
    DLList unionList = newDLList();

    // open files and read urls
    int i;
    for (i = 1; i < numFiles; i++) {       
        FILE *fp = fopen(files[i], "r");
        char url[BUFSIZ];              
        while(fscanf(fp, "%s", url) == 1){
            DLListAfter(unionList, url);
        }    
    }
    //int unionSize = unionList->nitems; 
    //freeDLList(unionList);

    return unionList;
}



