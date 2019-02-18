CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -pthread
LFLAGS = 
LIBS = -lm
SOURCES = sudoku.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = sudoku
.PHONY: clean help

sudoku: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and binary files"
