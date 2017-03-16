# Makefile to compile Umix Programming Assignment 4 (pa4) [updated: 1/11/10]

LIBDIR = $(UMIXPUBDIR)/lib
# LIBDIR = $(UMIXROOTDIR)/sys

CC 	= cc 
FLAGS 	= -g -L$(LIBDIR) -lumix4

PA4 =	pa4a pa4b pa4c test1 test2 test3 test4 test5 test6

pa4:	$(PA4)

pa4a:	pa4a.c aux.h umix.h
	$(CC) $(FLAGS) -o pa4a pa4a.c

pa4b:	pa4b.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o pa4b pa4b.c mythreads.o

pa4c:	pa4c.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o pa4c pa4c.c mythreads.o

test1:	test1.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o test1 test1.c mythreads.o

test2:	test2.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o test2 test2.c mythreads.o

test3:	test3.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o test3 test3.c mythreads.o

test4:	test4.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o test4 test4.c mythreads.o

test5:	test5.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o test5 test5.c mythreads.o

test6:	test6.c aux.h umix.h mythreads.h mythreads.o
	$(CC) $(FLAGS) -o test6 test6.c mythreads.o

mythreads.o:	mythreads.c aux.h umix.h mythreads.h
	$(CC) $(FLAGS) -c mythreads.c

clean:
	rm -f *.o $(PA4)
