CC=g++
STD=-std=c++0x

all: Minesweeper
	$(CC) $(STD) main.cpp minesweeper.o -lncurses -o minesweeper

Minesweeper:
	$(CC) $(STD) -c minesweeper.cpp

clean:
	rm *.o minesweeper
