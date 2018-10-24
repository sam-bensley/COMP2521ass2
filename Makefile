CC=gcc
CFLAGS=-Wall -Werror -g
PGERANKOBJS = graph.o DLList.o pagerank.o BSTree.o
INVERTEDOBJS = BSTree.o DLList.o inverted.o graph.o
SEARCHOBJS = DLList.o searchPagerank.o
TFIDFOBJS = DLList.o searchTfIdf.o BSTree.o graph.o
SCALEDFOOTOBJS = DLList.o scaledFootRule.o BSTree.o graph.o

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
pagerank.o: pagerank.c graph.c graph.h readData.c DLList.c DLList.h
inverted.o: inverted.c readData.c DLList.c DLList.h BSTree.c BSTree.h
searchPagerank.o: searchPagerank.c DLList.c DLList.h
searchTfIdf.o: searchTfIdf.c readData.c searchPagerank.c DLList.c DLList.h
scaledFootRule.o: scaledFootRule.c readData.c

clean :
	rm -fr $(PGERANKOBJS) $(INVERTEDOBJS) $(SEARCHOBJS) $(TFIDFOBJS) $(SCALEDFOOTOBJS) core 
	clear