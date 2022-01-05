CC = gcc
CFLAGS = -Wall
TARGET = main.o graph.o graph.h

all: graph

graph: graph.o main.o
	gcc -g -Wall -o graph graph.o main.o

graph.o: graph.c graph.h
	gcc -c -g -Wall graph.c graph.h

main.o: main.c graph.h
	gcc -c -g -Wall main.c graph.h

PHONY: clean all

clean:
	rm -f *.o graph 
