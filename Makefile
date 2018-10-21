CC=gcc
CFLAGS=-Wall -Werror -g
PGERANKOBJS = BSTree.o graph.o DLList.o pagerank.o
BINS=bst mkrand mkpref

pagerank : $(PGERANKOBJS)
	$(CC) $(CFLAGS) -o pagerank $(PGERANKOBJS)


graph.o: graph.c graph.h
BSTree.o : BSTree.c BSTree.h
DLList.o : DLList.c DLList.h
pagerank.o: pagerank.c graph.c graph.h readData.c DLList.c DLList.h


clean :
	rm -fr $(BINS) $(PGERANKOBJS) core 