#
# Makefile for Park program
#

CC=gcc
TARGET=autopark
CFLAGS= -Wall -ansi -O3
LIBS= -lm

SRCFILES= main.c cars.c graph.c heap.c LinkedList.c park_config.c restrictions.c spots.c tools.c
INCFILES= defs.h cars.h graph.h heap.h LinkedList.h park_config.h restrictions.h spots.h tools.h
OBJFILES= main.o cars.o graph.o heap.o LinkedList.o park_config.o restrictions.o spots.o tools.o

default: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(SRCFILES) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJFILES) core.* #*

main.o: main.c defs.h tools.h cars.h restrictions.h LinkedList.h park_config.h heap.h spots.h

cars.o: cars.c cars.h

graph.o: graph.c graph.h

heap.o: heap.c heap.h

LinkedList.o: LinkedList.c LinkedList.h

park_config.o: park_config.c park_config.h

restrictions.o: restrictions.c restrictions.h

spots.o: spots.c spots.h

tools.o: tools.c tools.h


