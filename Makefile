CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=BSTree.o Queue.o Graph.o DLList.o
BINS=bst mkrand mkpref

pagerank : $(OBJS)
	$(CC) -o pagerank $(OBJS)

BSTree.o : BSTree.c BSTree.h Queue.h
Queue.o : Queue.c Queue.h Item.h
DLList.o: DLList.c DLList.h


tests : bst
	cd tests ; make

clean :
	rm -fr $(BINS) $(OBJS) core *.dSYM tests/*.observed
