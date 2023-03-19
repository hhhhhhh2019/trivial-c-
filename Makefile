CC = g++ -I ./include -c -Wno-builtin-declaration-mismatch
LD = g++


SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


%.o: %.cpp
	$(CC) $< -o $@

all: $(OBJECTS)
	$(LD) $^ -o main


clean:
	rm *.o main -rf
