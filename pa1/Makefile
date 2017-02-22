# Makefile to compile Umix Programming Assignment 1 (pa1) [updated: 1/7/14]

LIBDIR = $(UMIXPUBDIR)/lib

CC 	= cc 
FLAGS 	= -g -L$(LIBDIR) -lumix1

PA1 =	pa1a pa1b pa1c pa1d pa1e pa1f test1 test2 test3 test4

pa1:	$(PA1)

pa1a:	pa1a.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1a pa1a.c mykernel1.o

pa1b:	pa1b.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1b pa1b.c mykernel1.o

pa1c:	pa1c.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1c pa1c.c mykernel1.o

pa1d:	pa1d.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1d pa1d.c mykernel1.o

pa1e:	pa1e.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1e pa1e.c mykernel1.o

pa1f:	pa1f.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o pa1f pa1f.c mykernel1.o

test1: test1.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o test1 test1.c mykernel1.o

test2: test2.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o test2 test2.c mykernel1.o

test3: test3.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o test3 test3.c mykernel1.o

test4: test4.c aux.h umix.h mykernel1.o
	$(CC) $(FLAGS) -o test4 test4.c mykernel1.o

mykernel1.o:	mykernel1.c aux.h sys.h mykernel1.h
	$(CC) $(FLAGS) -c mykernel1.c

clean:
	rm -f *.o $(PA1)
