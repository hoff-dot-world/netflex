CFLAGS= -Wall -pedantic -std=gnu99 -g

all: libflex flextest

libflex: libflex.c
	gcc -c $(CFLAGS) ./libflex.c -o libflex.o

flextest: flextest.c
	gcc $(CFLAGS) -pthread flextest.c libflex.o -o flextest

