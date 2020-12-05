# Harsh Rawat, harsh-rawat, hrawat2
# Sidharth Gurbani, gurbani, gurbani
#
# This is the makefile for Assignment 4 of CS537 in Fall 2020 offering
#
#

#FIFO_PROGNAME = 537pfsim-fifo
LRU_PROGNAME = 537pfsim-lru
CLOCK_PROGNAME = 537pfsim-clock
CC      = gcc
CFLAGS = -Wall -pedantic -Wextra
COMMON_OBJECTS = tsearch.o statistics.o queue.o doubly_linked_list.o heap.o error_handler.o input_parser.o process_options.o process.o page_table.o inverted_page_table.o
FIFO_OBJECTS = fifo_main.o fifo_page_replacement.o
LRU_OBJECTS = lru_main.o fifo_page_replacement.o
CLOCK_OBJECTS = clock_main.o clock_page_replacement.o

all: clean $(FIFO_PROGNAME) $(LRU_PROGNAME) $(CLOCK_PROGNAME)

$(FIFO_PROGNAME): $(FIFO_OBJECTS) $(COMMON_OBJECTS)
	$(CC) $(CFLAGS) -o $(FIFO_PROGNAME) $(COMMON_OBJECTS) $(FIFO_OBJECTS)

$(LRU_PROGNAME): $(LRU_OBJECTS) $(COMMON_OBJECTS)
	$(CC) $(CFLAGS) -o $(LRU_PROGNAME) $(COMMON_OBJECTS) $(LRU_OBJECTS)

$(CLOCK_PROGNAME): $(CLOCK_OBJECTS) $(COMMON_OBJECTS)
	$(CC) $(CFLAGS) -o $(CLOCK_PROGNAME) $(COMMON_OBJECTS) $(CLOCK_OBJECTS)

fifo_main.o: process.h process_options.h
	$(CC) $(CFLAGS) -DUSE_MODULE=FIFO -o fifo_main.o -c main.c
lru_main.o: process.h process_options.h
	$(CC) $(CFLAGS) -DUSE_MODULE=LRU -o lru_main.o -c main.c
clock_main.o: process.h process_options.h
	$(CC) $(CFLAGS) -DUSE_MODULE=CLOCK -o clock_main.o -c main.c
fifo_page_replacement.o: doubly_linked_list.h fifo_page_replacement.h fifo_page_replacement.c
	$(CC) $(CFLAGS) -c fifo_page_replacement.c
clock_page_replacement.o: doubly_linked_list.h clock_page_replacement.h clock_page_replacement.h
	$(CC) $(CFLAGS) -c clock_page_replacement.c

input_parser.o: error_handler.h input_parser.h input_parser.c
	$(CC) $(CFLAGS) -c input_parser.c
process_options.o: process_options.h process_options.c
	$(CC) $(CFLAGS) -c process_options.c
process.o: statistics.h tsearch.h input_parser.h page_table.h error_handler.h process.h process.c
	$(CC) $(CFLAGS) -c process.c
page_table.o: queue.h heap.h input_parser.h tsearch.h error_handler.h inverted_page_table.h tables.h process.h statistics.h page_table.c page_table.h
	$(CC) $(CFLAGS) -c page_table.c
inverted_page_table.o: tables.h inverted_page_table.c inverted_page_table.h
	$(CC) $(CFLAGS) -c inverted_page_table.c
tsearch.o: error_handler.h tsearch.c tsearch.h
	$(CC) $(CFLAGS) -c tsearch.c
statistics.o: statistics.c statistics.h
	$(CC) $(CFLAGS) -c statistics.c
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c
doubly_linked_list.o: doubly_linked_list.c doubly_linked_list.h
	$(CC) $(CFLAGS) -c doubly_linked_list.c
heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c
error_handler.o: error_handler.c error_handler.h
	$(CC) $(CFLAGS) -c error_handler.c

clean:
	rm -f $(COMMON_OBJECTS) $(FIFO_OBJECTS) $(LRU_OBJECTS) $(CLOCK_OBJECTS) $(FIFO_PROGNAME) $(LRU_PROGNAME) $(CLOCK_PROGNAME)
