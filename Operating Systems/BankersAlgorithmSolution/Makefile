CC = clang
CFLAGS = -Wall -Wextra -std=gnu99
LFLAGS = 
LIBS = -lpthread
SOURCES = banker.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = banker
.PHONY: clean help

.PHONY: debug
debug: CFLAGS += -O0 -g3
debug: $(EXE)

banker : banker.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  all:    generates all binary files"
	@echo "  debug:  generates debug binary files"
	@echo "  clean:  removes .o and .exe files"
