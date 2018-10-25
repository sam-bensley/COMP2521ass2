// Part 1-B
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "BSTree.h"
#include "DLList.h"
#include "readData.h"


int main(int argc, char*argv[]){

    // read web pages from collection.txt
    DLList collection = getCollection();  
    BSTree tree = getTree(collection);
    
    // open file and write tree
    FILE *fp = fopen("invertedIndex.txt", "w");
    BSTreeInfix(tree, fp);

    return 0;
}

