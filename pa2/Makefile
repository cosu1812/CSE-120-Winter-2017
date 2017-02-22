# Makefile to compile Umix Programming Assignment 2 (pa2) [updated: 1/11/10]

LIBDIR = $(UMIXPUBDIR)/lib
# LIBDIR = $(UMIXROOTDIR)/sys

CC 	= cc 
FLAGS 	= -g -L$(LIBDIR) -lumix2

PA2 =	pa2a pa2b pa2c pa2d lifo fifo iof rereq

pa2:	$(PA2)

pa2a:	pa2a.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2a pa2a.c mykernel2.o

pa2b:	pa2b.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2b pa2b.c mykernel2.o

pa2c:	pa2c.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2c pa2c.c mykernel2.o

pa2d:	pa2d.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o pa2d pa2d.c mykernel2.o

lifo:	lifo.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o lifo lifo.c mykernel2.o

fifo:	fifo.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o fifo fifo.c mykernel2.o

iof:	iof.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o iof iof.c mykernel2.o

rereq:	rereq.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o rereq rereq.c mykernel2.o

nomercy:	nomercy.c aux.h umix.h mykernel2.o
	$(CC) $(FLAGS) -o nomercy nomercy.c mykernel2.o

mykernel2.o:	mykernel2.c aux.h sys.h mykernel2.h
	$(CC) $(FLAGS) -c mykernel2.c

clean:
	rm -f *.o $(PA2)
