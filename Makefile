#
# Makefile for Park program
#

CC=gcc
TARGET=autopark
CFLAGS= -Wall -ansi -O3

SRCFILES= main.c cars.c graph.c heap.c LinkedList.c park_config.c restrictions.c spots.c tools.c
INCFILES= defs.h includes.h cars.h graph.h heap.h LinkedList.h park_config.h restrictions.h spots.h tools.h
OBJFILES= main.o cars.o graph.o heap.o LinkedList.o park_config.o restrictions.o spots.o tools.o

default: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(SRCFILES) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJFILES) core.* #*

main.o: main.c includes.h

cars.o: cars.c includes.h

graph.o: graph.c includes.h

heap.o: heap.c includes.h

LinkedList.o: LinkedList.c includes.h

park_config.o: park_config.c includes.h

restrictions.o: restrictions.c includes.h

spots.o: spots.c includes.h

tools.o: tools.c includes.h


