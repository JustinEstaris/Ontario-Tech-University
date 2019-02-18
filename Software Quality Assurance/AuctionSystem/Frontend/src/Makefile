CC = g++
CFLAGS = --std=c++11 -fmax-errors=1
LDFLAGS =
HEADERS = ./*.h
SOURCES = main.cpp AuctionSystem.cpp User.cpp FileController.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = auction_system
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)
run:
	./$(EXECUTABLE)
%.o: %.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) $<
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)