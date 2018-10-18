#include <stdlib.h>
#include <stdio.h>

#define MAXLENGTH 6
#define MAXNUMURLS 20

int main(int argc, char *argv[]){
    return 0;

}

char **getCollection(){
    FILE *collection = fopen("collection.txt", "r");
    char url[MAXLENGTH];
    
    char **ret = calloc(MAXNUMURLS, MAXLENGTH);
    int i = 0;
    while(fscanf(collection, "%s", url) == 1){
        strcpy(ret[i], url);
    }
    return ret;
}