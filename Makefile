CC=gcc
CFLAGS=-Wall -Werror -g
PGERANKOBJS = graph.o DLList.o pagerank.o BSTree.o
INVERTEDOBJS = BSTree.o DLList.o inverted.o graph.o

all: inverted pagerank

inverted: $(INVERTEDOBJS)
	$(CC) $(CFLAGS) -o inverted $(INVERTEDOBJS)

pagerank : $(PGERANKOBJS)
	$(CC) $(CFLAGS) -o pagerank $(PGERANKOBJS)

graph.o: graph.c graph.h
BSTree.o : BSTree.c BSTree.h
DLList.o : DLList.c DLList.h
pagerank.o: pagerank.c graph.c graph.h readData.c DLList.c DLList.h
inverted.o: inverted.c readData.c DLList.c DLList.h BSTree.c BSTree.h

clean :
	rm -fr $(PGERANKOBJS) $(INVERTEDOBJS) core 