CC=g++
CFLAGS=-W -Wall -ansi -pedantic -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXEC=main

all: $(EXEC)

$(EXEC): main.o game.o paddle.o home.o missile.o alien.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
