CC=gcc
CFLAGS=-Wall -Werror -g
PGERANKOBJS = graph.o DLList.o pagerank.o BSTree.o readData.o
INVERTEDOBJS = BSTree.o DLList.o graph.o readData.o inverted.o 
SEARCHOBJS = DLList.o searchPagerank.o readData.o BSTree.o graph.o
TFIDFOBJS = DLList.o searchTfIdf.o BSTree.o graph.o readData.o
SCALEDFOOTOBJS = DLList.o scaledFootRule.o BSTree.o graph.o readData.o

all : inverted pagerank searchPagerank searchTfIdf scaledFootRule

inverted : $(INVERTEDOBJS)
	$(CC) $(CFLAGS) -o inverted $(INVERTEDOBJS)

pagerank : $(PGERANKOBJS)
	$(CC) $(CFLAGS) -o pagerank $(PGERANKOBJS)

searchPagerank : $(SEARCHOBJS)
	$(CC) $(CFLAGS) -o searchPagerank $(SEARCHOBJS)

searchTfIdf : $(TFIDFOBJS)
	$(CC) $(CFLAGS) -o searchTfIdf $(TFIDFOBJS)

scaledFootRule : $(SCALEDFOOTOBJS)
	$(CC) $(CFLAGS) -o scaledFootRule $(SCALEDFOOTOBJS)

graph.o: graph.c graph.h
BSTree.o : BSTree.c BSTree.h
DLList.o : DLList.c DLList.h
readData.o: readData.c readData.h
pagerank.o: pagerank.c 
inverted.o: inverted.c
searchPagerank.o: searchPagerank.c
searchTfIdf.o: searchTfIdf.c
scaledFootRule.o: scaledFootRule.c


clean :
	rm -fr $(PGERANKOBJS) $(INVERTEDOBJS) $(SEARCHOBJS) $(TFIDFOBJS) $(SCALEDFOOTOBJS) core 
	clear