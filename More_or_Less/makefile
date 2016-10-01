CC=g++
CFLAGS=-W -Wall -ansi -pedantic -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXEC=main

all: $(EXEC)

$(EXEC): main.o
	$(CC) -o $(EXEC) main.o $(LDFLAGS)

main.o: main.cpp
	$(CC) -o main.o -c main.cpp $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper
	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)