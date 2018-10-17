CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=BSTree.o Queue.o Graph.o
BINS=bst mkrand mkpref

all : $(BINS)

pagerank : $(OBJS)
	$(CC) -o pagerank $(OBJS)






BSTree.o : BSTree.c BSTree.h Queue.h
Queue.o : Queue.c Queue.h



tests : bst
	cd tests ; make

clean :
	rm -fr $(BINS) $(OBJS) core *.dSYM tests/*.observed
