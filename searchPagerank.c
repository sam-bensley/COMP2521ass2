#include <stdio.h>
#include <stdlib.h>
#include "DLList.h"
#include <string.h>

typedef struct UrlAndWord{
    char *word;
    DLList urls;
}UrlAndWord;

typedef struct urlRanks {
    char *url;
    float wPR;      // weighted page rank of url
} urlRanks;

typedef struct searchResults {
    char *url;
    float wPR;      // weighted page rank of url
    int repeats;
} searchResults;


int isUrl(char *url);
void sortDescendingRepeats(searchResults SReults[], int size);
void sortDescendingWPR(searchResults SReults[], int size);

int main(int argc, char *argv[]){

    //get args
    if(argc < 2){
        printf("Usage: ./searchPagerank [search1] [search2] ...\n");
        exit(1);
    }

    UrlAndWord urlWords[argc - 1];
    int size = 0;

    int i;
    for(i = 1; i < argc; i++){
        char *word = argv[i];   
        FILE *fp = fopen("invertedIndex.txt", "r");
        char singleWord[BUFSIZ];
        int found = 0;
        
        while(fscanf(fp, "%s", singleWord) == 1){
            if(found && isUrl(singleWord)){
                if(urlWords[i-1].urls != NULL){
                    DLListAfter(urlWords[i-1].urls, singleWord); 
                }
                else{
                    urlWords[i-1].urls = newDLList();
                    
                    DLListAfter(urlWords[i-1].urls, singleWord);
                }
            }
            else if(found && !isUrl(singleWord)){
                found = 0;
            }
            if(strcmp(word, singleWord) == 0){
                size++;
                found = 1;
                urlWords[i-1].word = strdup(singleWord);
                
            }
        }
    }
       
    urlRanks ranks[BUFSIZ]; // not sure how big this should be
    FILE *rankList = fopen("pagerankList.txt", "r");
    char url[BUFSIZ];
    int outgoing;
    float wPR; 
    i = 0;
    while(fscanf(rankList, "%s %d, %f", url, &outgoing, &wPR) == 3){
        urlRanks rank;
        //Remove the comma
        url[strlen(url)-1] = '\0';
        rank.url = strdup(url);
        rank.wPR = wPR;
        ranks[i] = rank;
        i++;
    }

    int urlRanksSize = i;

    // deal with repeats
    DLList listOfurls = newDLList();
    for(i = 0; i < size; i++){
        DLListNode *curr = urlWords[i].urls->first;
        while(curr != NULL){
            DLListAfter(listOfurls, curr->value);
            curr = curr->next;
        }
    }

    //putDLList(stdout, listOfurls);

    int finalSearchArraySize = listOfurls->nitems;

    //populate search results array
    searchResults SResults[listOfurls->nitems];

    i = 0;
    DLListNode *curr = listOfurls->first;
    while(curr != NULL){
        SResults[i].repeats = curr->repeats;
        SResults[i].url = curr->value;
        int j;
        for(j = 0; j < urlRanksSize; j++){
            if(strcmp(ranks[j].url, curr->value)==0){
                SResults[i].wPR = ranks[j].wPR;
                break;
            }
        }
        i++;
        curr = curr->next;
    }

    //Need to sort the Sresults array;
    sortDescendingRepeats(SResults, finalSearchArraySize);
    sortDescendingWPR(SResults, finalSearchArraySize);
    
    for(i = 0; i < finalSearchArraySize && i < 30; i++){
        printf("%s, %f, %d\n", SResults[i].url, SResults[i].wPR, SResults[i].repeats);
    }

    return 0;
}

// sorts *ranks[] in descending order using bubblesort algorithm
void sortDescendingRepeats(searchResults SReults[], int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        int swapped = 0;
        int j = 0;
        for (j = 0; j < size - 1; j++) {
            if (SReults[j].repeats < SReults[j + 1].repeats){
                searchResults temp = SReults[j];
                SReults[j] = SReults[j+1];
                SReults[j+1] =  temp;
                swapped = 1;
            }                                    
        }
        // if no elements were swapped, quick sort is complete
        if (swapped == 0) break;                            
    }

}

void sortDescendingWPR(searchResults SReults[], int size){

    int i = 0;
    for (i = 0; i < size; i++) {
        int swapped = 0;
        int j = 0;
        for (j = 0; j < size - 1; j++) {
            if (SReults[j].repeats == SReults[j + 1].repeats && SReults[j].wPR < SReults[j + 1].wPR){
                searchResults temp = SReults[j];
                SReults[j] = SReults[j+1];
                SReults[j+1] =  temp;
                swapped = 1;
            }                                    
        }
        // if no elements were swapped, quick sort is complete
        if (swapped == 0) break;                            
    }

}
// determines if string is of "urlXX" format
int isUrl(char *url){
    // if first 3 characters are "url"
    return (strncmp(url, "url", 3) == 0) ? 1 : 0;
}

