// Part 2

#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "DLList.h"
#include "readData.h"

#define MAXURLSTOPRINT 30

typedef struct urlAndTFIF {
    char *url;
    float tfidf;
} urlAndTFIF; 

void sortDescending(urlAndTFIF *urlAndTFIFArray, int size);
DLList ListWithURLSThatContainStrings(char **strings, int size);
float termFrequency (DLList termCountTable, char *word);
float iDocumentFrequency (DLList termCountTable, char *word, int totalUrls);
int totalWords (DLList termCountTable);

int main (int argc, char *argv[])
{
    //determine total number of URLS
    FILE *collection = fopen("collection.txt", "r");
    int totalUrls = 0;
    char urlTemp[BUFSIZ];
    while(fscanf(collection, "%s", urlTemp) == 1){
        totalUrls++;
    }
    fclose(collection);

    // Make list of urls where there is at least one term
    DLList hitUrls = ListWithURLSThatContainStrings(argv, argc);  
    int numHitUrls = hitUrls->nitems;

    urlAndTFIF urlAndTFIFArray[hitUrls->nitems];
    int urlAndTFIFIndex = 0;

    //looop through this list and add to urlAndTFIF array
    DLListNode *curr = hitUrls->first;
    while (curr != NULL)
    {
        // create term count table (termCountTalbe->repeats)
        DLList termCountTable = getTermCountTable(curr->value);
        //float totaltfidf = 0;
        float totaltfidf = 0;        
        int i;
        for(i = 1; i < argc; i++){
            float tf = termFrequency(termCountTable, argv[i]); 
            // if url in 'hitUrls' is from a different argv[], skip this url
            if (tf == 0.0) continue;  
            float idf = iDocumentFrequency(termCountTable, argv[i], totalUrls);
            totaltfidf += tf * idf;                                                                        
        }
        //add to the urlAndTFIF array
        urlAndTFIFArray[urlAndTFIFIndex].url = strdup(curr->value);
        urlAndTFIFArray[urlAndTFIFIndex].tfidf = totaltfidf;
        urlAndTFIFIndex++;                       
        freeDLList(termCountTable);
        curr = curr->next;
    }
    // sort urlAndTFIF array
    sortDescending(urlAndTFIFArray, numHitUrls);

    // print to stdout
    int i;
    for (i = 0; i < hitUrls->nitems && i < MAXURLSTOPRINT; i++)
        printf("%s %.6f\n", urlAndTFIFArray[i].url,  urlAndTFIFArray[i].tfidf);               

    // free strdups
    freeDLList(hitUrls);
    return 0;
}

// sorts *ranks[] in descending order using quicksort algorithm
void sortDescending(urlAndTFIF *urlAndTFIFArray, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        int swapped = FALSE;
        int j = 0;
        for (j = 0; j < size - 1; j++) {
            if (urlAndTFIFArray[j].tfidf < urlAndTFIFArray[j + 1].tfidf){
                urlAndTFIF temp = urlAndTFIFArray[j];
                urlAndTFIFArray[j] = urlAndTFIFArray[j+1];
                urlAndTFIFArray[j+1] =  temp;
                swapped = TRUE;
            }                                    
        }
        // if no elements were swapped, quick sort is complete
        if (swapped == FALSE) break;                            
    }

}


// calculates term fequency
float termFrequency (DLList termCountTable, char *word)
{   
    float tf = 0;
    int totalNumWords = totalWords(termCountTable);  
    // search for word in termCountTable
    DLListNode *curr = termCountTable->first;            
    while (curr != NULL) 
    {   
        if (strcmp(curr->value, word) == 0) break;
        curr = curr->next;
    }
    // curr will now be the DLListNode containing "word"
    if(curr == NULL) return 0.0;

    tf = (float)(curr->repeats + 1) / (float)totalNumWords; 
    return tf;
}

// calculates inverse document frequency
float iDocumentFrequency (DLList termCountTable, char *word, int totalUrls)
{
    float idf = 0.0;
    int numUrls = 0;    // #urls word is in

    // find #urls word is contained in (using invertedIndex.txt)
    FILE *fp = fopen("invertedIndex.txt", "r");
    // loop text file until word is found
    char singleWord[BUFSIZ];
    while (fscanf (fp, "%s", singleWord) == 1){
        if (strcmp(singleWord, word) == 0){
            // loop along line and count the urls
            char url[BUFSIZ];
            while (fscanf(fp, "%s", url) == 1) {
                if (isUrl(url)) {
                    numUrls++; 
                } else {                     
                    break;
                }
            }
            break;
        } 
    }
    fclose(fp);    
    // printf("num Urls is: %d\n", numUrls);

    idf = log10f(((float)(totalUrls)) / (float)((float)(numUrls)));
    
    return idf;
}

// calculates total words in DLList
int totalWords (DLList termCountTable)
{
    int total = 0;
    DLListNode *curr = termCountTable->first;
    while (curr != NULL)
    {
        total += (curr->repeats + 1);
        curr = curr->next;
    }
    return total;
}


DLList ListWithURLSThatContainStrings(char **strings, int size){

    DLList list = newDLList();

    int i;
    for(i = 1; i < size; i++){
        char *word = strings[i];   
        FILE *fp = fopen("invertedIndex.txt", "r");
        char singleWord[BUFSIZ];
        int found = 0;
        while(fscanf(fp, "%s", singleWord) == 1){
            if(found && isUrl(singleWord)){
                DLListAfter(list, singleWord); 
            }
            else if(found && !isUrl(singleWord)){
                found = 0;
            }
            if(strcmp(word, singleWord) == 0){
                found = 1;
            }
        }
    }

    return list;

    
}

